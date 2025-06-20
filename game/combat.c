#include <stdio.h>    // Para printf, scanf, fgets
#include <stdlib.h>   // Para atoi, system
#include <string.h>   // Para strlen, strcspn
#include <stdbool.h>  // Para bool

#include "combat.h"     // Declaraciones de las funciones de combate
#include "data_types.h" // Definiciones de las estructuras Player, Enemy, Item
#include "player.h"     // Funciones del jugador (initializePlayer, player_add_item_to_inventory, etc.)
#include "ui.h" // Para waitForKeyPress y otros helpers visuales

// --- FUNCIONES AUXILIARES DEL MÓDULO COMBATE ---
int calculate_damage(int attack, int defense) {
    // Fórmula no lineal: la defensa reduce el daño con rendimientos decrecientes
    // Daño = ataque * (100 / (100 + defensa))
    float reduction = 100.0f / (100.0f + (float)defense);
    int damage_dealt = (int)(attack * reduction + 0.5f); // Redondeo
    if (damage_dealt < 1) damage_dealt = 1; // Daño mínimo siempre 1
    return damage_dealt;
}

void display_combat_status(Player* player, Enemy* enemy) {
    if (player == NULL || enemy == NULL) return;

    printf("\x1b[36m╔═══════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║           \x1b[1m--- ESTADO DE COMBATE ---\x1b[0m           \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╠═══════════════════════════════════════════════╣\x1b[0m\n");
    printf("  %s HP: \x1b[32m%d\x1b[0m/\x1b[32m%d\x1b[0m  (Atk: \x1b[31m%d\x1b[0m, Def: \x1b[34m%d\x1b[0m)\n",
        player->name, player->currentHP, player->maxHP,
        player->attack + player->tempAttackBoost,
        player->defense + player->tempDefenseBoost);
    printf("  %s HP: \x1b[32m%d\x1b[0m\n", enemy->name, enemy->currentHP);
    printf("\x1b[36m╚═══════════════════════════════════════════════╝\x1b[0m\n");
}

/**
 * @brief Permite al jugador elegir una acción durante su turno.
 * Muestra las opciones y valida la entrada del usuario.
 * @param player Puntero a la estructura del Jugador.
 * @return Un entero que representa la acción elegida (1 para Atacar, 2 para Usar Ítem, etc.).
 */
int player_choose_action() {
    int choice;
    char input[10];

    printf("\x1b[36m⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨\x1b[0m\n");
    printf("\x1b[36m⇨  ¡Tu turno!\x1b[0m\n");
    printf("\x1b[36m⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨\x1b[0m\n");
    printf("  \x1b[32m[1] Atacar\x1b[0m\n");
    printf("  \x1b[34m[2] Usar Ítem (Inventario)\x1b[0m\n");
    printf("\x1b[36m──────────────────────────────────────────────────────────────\x1b[0m\n");
    printf("Tu elección: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1; // Error de lectura
    }
    choice = atoi(input); // Convierte la cadena a entero

    // Validación básica de la elección
    if (choice < 1 || choice > 2) {
        return -1; // Indicar elección inválida
    }
    return choice;
}


void apply_damage(int* current_hp, int damage_dealt) {
    if (current_hp == NULL) return;

    *current_hp -= damage_dealt;
    if (*current_hp < 0) {
        *current_hp = 0; // La vida no puede ser negativa
    }
}

// --- FUNCIÓN PRINCIPAL DE COMBATE 
bool combat_manage_turn(Player* player, Enemy* enemy) {
    if (player == NULL || enemy == NULL) {
        printf("Error: Jugador o enemigo nulo para el combate.\n");
        return false; // Error en la batalla
    }

    display_combat_banner(player->name, enemy->name);
    Sleep(1000);

    while (player->currentHP > 0 && enemy->currentHP > 0) {
        display_combat_status(player, enemy);

        // --- TURNO DEL JUGADOR ---
        int action_choice = player_choose_action();

        if (action_choice == 1) { // Atacar
            // Calcular el daño que el jugador inflige
            int player_effective_attack = player->attack + player->tempAttackBoost;
            int damage_to_enemy = calculate_damage(player_effective_attack, enemy->defense);

            apply_damage(&enemy->currentHP, damage_to_enemy);
            printf("\x1b[36m» %s ataca a %s y le inflige %d de daño. «\x1b[0m\n", player->name, enemy->name, damage_to_enemy);
            printf("\x1b[90m──────────────────────────────────────────────────────────────\x1b[0m\n");
            Sleep(500);

        } else if (action_choice == 2) { 
            printf("--- Inventario de %s ---\n", player->name);
            if (player->inventoryCount == 0) {
                printf("Tu inventario esta vacio.\n");
            } else {
                for (int i = 0; i < player->inventoryCount; i++) {
                    Item currentItem = player->inventory[i];
                    printf("%d. %s (Curacion: %d, Daño Boost: %d, Def Boost: %d, Duracion: %d)\n",
                           i + 1, currentItem.name, currentItem.heal,
                           currentItem.damage, currentItem.defense, currentItem.effectDuration);
                }
                printf("Elige un item a usar (0 para cancelar): ");
                char item_input[10];
                if (fgets(item_input, sizeof(item_input), stdin) == NULL) {
                    printf("Error de lectura de item.\n");
                    continue;
                }
                int item_choice = atoi(item_input);

                if (item_choice > 0 && item_choice <= player->inventoryCount) {
                    player_use_consumable(player, item_choice - 1);
                    waitForKeyPress(); // Pausa para leer el resultado del ítem
                } else {
                    printf("Cancelando uso de item.\n");
                    waitForKeyPress();
                }
            }
        } else {
            printf("Accion invalida. Pierdes tu turno.\n");
            Sleep(500);
        }

        // --- Verificar si el enemigo fue derrotado después del turno del jugador ---
        if (enemy->currentHP <= 0) {
            player->enemiesDefeated++;
            Sleep(500);
            return true; // Jugador gana
        }


        player_update_temporary_boosts(player); 

        // --- TURNO DEL ENEMIGO ---
        printf("\x1b[31m⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦\x1b[0m\n");
        printf("\x1b[31m⇦  Es el turno de %s!\x1b[0m\n", enemy->name);
        printf("\x1b[31m⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦\x1b[0m\n");
        int enemy_damage_to_player = calculate_damage(enemy->attack, player->defense + player->tempDefenseBoost); // Usar defensa efectiva
        apply_damage(&player->currentHP, enemy_damage_to_player);
        printf("\x1b[31m« %s ataca a %s y le inflige %d de daño. »\x1b[0m\n", enemy->name, player->name, enemy_damage_to_player);
        printf("\x1b[90m──────────────────────────────────────────────────────────────\x1b[0m\n");

        if (player->currentHP <= 0) {
            Sleep(500);
            return false; // Jugador pierde
        } else {
            waitForKeyPress();
        }
    }

    return false; 
}