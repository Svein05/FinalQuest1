#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "combat.h"
#include "data_types.h"
#include "player.h"
#include "ui.h"

// --- FUNCIONES AUXILIARES DEL MÓDULO COMBATE ---

/**
 * @brief Calcula el daño efectivo considerando ataque 
 * y defensa en base a una funcion lineal.
 * Siempre retorna al menos 1 de daño.
 * @param attack Valor de ataque del atacante.
 * @param defense Valor de defensa del defensor.
 * @return Daño efectivo a aplicar.
 */
int calculate_damage(int attack, int defense) {
    float reduction = 100.0f / (100.0f + (float)defense);
    int damage_dealt = (int)(attack * reduction + 0.5f); // Redondeo
    if (damage_dealt < 1) damage_dealt = 1; // Daño mínimo siempre 1
    return damage_dealt;
}

/**
 * @brief Permite al jugador elegir una acción durante su turno de combate.
 * Devuelve 1 para atacar, 2 para usar ítem, -1 si la entrada es inválida.
 * @return Acción elegida por el jugador.
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

/**
 * @brief Muestra el estado actual de vida, ataque y defensa de ambos combatientes.
 * @param player Puntero al jugador.
 * @param enemy Puntero al enemigo.
 */
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
 * @brief Aplica daño a un puntero de vida, asegurando que no sea menor que 0.
 * @param current_hp Puntero a la vida actual a modificar.
 * @param damage_dealt Daño a aplicar.
 */
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

    ui_combat_banner(player->name, enemy->name);
    Sleep(1000);

    // Bucle de la batalla
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

        } else if (action_choice == 2) { // Usar Item
            display_inventory(player, true, true);
            if (player->inventoryCount == 0) {
                waitForKeyPress();
            } else {
                char item_input[10];
                if (fgets(item_input, sizeof(item_input), stdin) == NULL) {
                    printf("Error de lectura de item.\n");
                } else {
                    int item_choice = atoi(item_input);
                    if (item_choice > 0 && item_choice <= player->inventoryCount) {
                        player_use_consumable(player, item_choice - 1);
                        waitForKeyPress();
                    } else {
                        printf("Cancelando uso de item.\n");
                        waitForKeyPress();
                    }
                }
            }
        } else {
            ui_msg_error("Accion invalida. Pierdes tu turno.\n");
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
        printf("\x1b[31m⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇦⇦⇦⇦⇦⇦⇦⇦\x1b[0m\n");
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

// === COMBATE ESPECIAL DEL BOSS FINAL ===

bool combat_final_boss(Player* player, Enemy* boss) {
    if (player == NULL || boss == NULL) {
        printf("Error: Parámetros inválidos para combate del boss final.\n");
        return false;
    }
    
    // El boss final tiene HP completo al inicio
    boss->currentHP = boss->HP;
    
    // Variables especiales para el boss final
    int boss_phase = 1; // Fase 1, 2, 3
    int boss_rage_turns = 0; // Turnos en modo furia
    bool boss_enraged = false;
    bool boss_buffed_phase2 = false;
    bool boss_buffed_phase1 = false;

    while (player->currentHP > 0 && boss->currentHP > 0) {
        clearScreen();
        
        // Determinar fase del boss basada en HP
        int hp_percentage = (boss->currentHP * 100) / boss->HP;
        if (hp_percentage > 66) {
            boss_phase = 1;
        } else if (hp_percentage > 33) {
            boss_phase = 2;
            if (!boss_buffed_phase2) {
                boss_buffed_phase2 = true;
                boss->attack += 10;

                ui_boss_phase2();
            }
        } else {
            boss_phase = 3;
            if (!boss_enraged) {
                boss_enraged = true;
                boss->attack += 20; // Aumenta ataque en fase final

                ui_boss_phase3();
            }
        }

        // Mostrar estado con información especial del boss
        printf("\x1b[91m╔═══════════════════════════════════════════════╗\x1b[0m\n");
        printf("\x1b[91m║           COMBATE FINAL - FASE %d              ║\x1b[0m\n", boss_phase);
        printf("\x1b[91m╠═══════════════════════════════════════════════╣\x1b[0m\n");
        printf("  %s HP: \x1b[32m%d\x1b[0m/\x1b[32m%d\x1b[0m  (Atk: \x1b[31m%d\x1b[0m, Def: \x1b[34m%d\x1b[0m)\n",
            player->name, player->currentHP, player->maxHP,
            player->attack + player->tempAttackBoost,
            player->defense + player->tempDefenseBoost);
        printf("  \x1b[91m%s HP: \x1b[31m%d\x1b[0m/%d \n", boss->name, boss->currentHP, boss->HP);
        printf("\x1b[91m╚═══════════════════════════════════════════════╝\x1b[0m\n");

        // --- TURNO DEL JUGADOR ---
        int action = player_choose_action();
        
        if (action == 1) { // Atacar
            int player_damage_to_boss = calculate_damage(player->attack + player->tempAttackBoost, boss->defense);
            apply_damage(&boss->currentHP, player_damage_to_boss);
            printf("\x1b[32m» %s ataca al %s y le inflige %d de daño. «\x1b[0m\n", 
                   player->name, boss->name, player_damage_to_boss);
        } else if (action == 2) { // Usar ítem
            // --- Inventario de uso de ítem (igual que combate normal) ---
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
                } else {
                    int item_choice = atoi(item_input);
                    if (item_choice > 0 && item_choice <= player->inventoryCount) {
                        player_use_consumable(player, item_choice - 1);
                        waitForKeyPress();
                    } else {
                        printf("Cancelando uso de item.\n");
                        waitForKeyPress();
                    }
                }
            }
        }

        if (boss->currentHP <= 0) {
            printf("\x1b[93m¡Has derrotado al %s!\x1b[0m\n", boss->name);
            return true; // Jugador gana
        }

        // Actualizar efectos temporales del jugador
        player_update_temporary_boosts(player);

        // --- TURNO DEL BOSS FINAL (con ataques especiales) ---
        printf("\x1b[91m⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦\x1b[0m\n");
        printf("\x1b[91m⇦  ¡%s contraataca con poder abismal!\x1b[0m\n", boss->name);
        printf("\x1b[91m⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦\x1b[0m\n");

        // Ataques especiales según la fase
        int boss_damage = 0;
        int special_attack_chance = (boss_phase - 1) * 20 + (boss_enraged ? 30 : 0); // 0%, 20%, 40% + 30% si está en furia
        
        if (rand() % 100 < special_attack_chance) {
            // Ataque especial
            switch (boss_phase) {
                case 1:
                    printf("\x1b[95m¡%s usa 'Golpe Devastador'!\x1b[0m\n", boss->name);
                    boss_damage = calculate_damage(boss->attack * 1.3f, player->defense + player->tempDefenseBoost);
                    break;
                case 2:
                    printf("\x1b[96m¡%s canaliza 'Tormenta de Sombras'!\x1b[0m\n", boss->name);
                    boss_damage = calculate_damage(boss->attack * 1.5f, player->defense + player->tempDefenseBoost);
                    printf("\x1b[90m¡La oscuridad debilita tu defensa temporalmente!\x1b[0m\n");
                    player->tempDefenseBoost -= 5; // Debuff temporal
                    break;
                case 3:
                    printf("\x1b[91m¡%s desata 'ANIQUILACIÓN FINAL'!\x1b[0m\n", boss->name);
                    boss_damage = calculate_damage(boss->attack * 1.8f, player->defense + player->tempDefenseBoost);
                    printf("\x1b[91m¡El poder del vacío consume todo a su paso!\x1b[0m\n");
                    break;
            }
        } else {
            // Ataque normal
            printf("\x1b[91m%s ataca con sus garras del vacío.\x1b[0m\n", boss->name);
            boss_damage = calculate_damage(boss->attack, player->defense + player->tempDefenseBoost);
        }
        
        apply_damage(&player->currentHP, boss_damage);
        printf("\x1b[31m« %s inflige %d de daño devastador. »\x1b[0m\n", boss->name, boss_damage);
        printf("\x1b[90m──────────────────────────────────────────────────────────────\x1b[0m\n");

        if (player->currentHP <= 0) {
            printf("\x1b[91m¡%s ha caído ante el poder del %s!\x1b[0m\n", player->name, boss->name);
            return false; // Jugador pierde
        } else {
            waitForKeyPress();
        }

        // Incrementar contadores especiales
        if (boss_enraged) boss_rage_turns++;
    }

    return false; // No debería llegar aquí, pero por seguridad
}