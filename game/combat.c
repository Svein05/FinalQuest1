#include <stdio.h>    // Para printf, scanf, fgets
#include <stdlib.h>   // Para atoi, system
#include <string.h>   // Para strlen, strcspn
#include <stdbool.h>  // Para bool

#include "combat.h"     // Declaraciones de las funciones de combate
#include "data_types.h" // Definiciones de las estructuras Player, Enemy, Item
#include "player.h"     // Funciones del jugador (initializePlayer, player_add_item_to_inventory, etc.)

// --- FUNCIONES AUXILIARES DEL MÓDULO COMBATE ---

/**
 * @brief Calcula el daño real que se inflige, teniendo en cuenta el ataque del atacante
 * y la defensa del defensor. El daño mínimo siempre es 1.
 * @param attack Puntos de ataque del atacante.
 * @param defense Puntos de defensa del defensor.
 * @return El daño final que se debe aplicar.
 */
int calculate_damage(int attack, int defense) {
    // Calcular el daño base.
    int damage_dealt = attack - defense;

    // Asegurar que el daño mínimo siempre sea 1, incluso si la defensa es muy alta.
    if (damage_dealt < 1) {
        damage_dealt = 1;
    }
    return damage_dealt;
}

/**
 * @brief Muestra el estado actual del combate, incluyendo la vida del jugador y del enemigo.
 * También muestra los boosts temporales activos del jugador.
 * @param player Puntero a la estructura del Jugador.
 * @param enemy Puntero a la estructura del Enemigo.
 */
void display_combat_status(Player* player, Enemy* enemy) {
    if (player == NULL || enemy == NULL) return;

    printf("\n--- ESTADO DE COMBATE ---\n");
    printf("%s HP: %d/%d (Atk: %d, Def: %d)\n",
           player->name, player->currentHP, player->maxHP,
           player->attack + player->tempAttackBoost, // Mostrar ataque efectivo
           player->defense + player->tempDefenseBoost); // Mostrar defensa efectiva

    // Mostrar boosts temporales si están activos
    if (player->tempAttackBoost > 0) {
        printf("  - Boost Atk: +%d (%d turnos restantes)\n", player->tempAttackBoost, player->attackBoostTurns);
    }
    if (player->tempDefenseBoost > 0) {
        printf("  - Boost Def: +%d (%d turnos restantes)\n", player->tempDefenseBoost, player->defenseBoostTurns);
    }

    printf("%s HP: %d\n", enemy->name, enemy->currentHP);
    printf("------------------------\n");
}

/**
 * @brief Permite al jugador elegir una acción durante su turno.
 * Muestra las opciones y valida la entrada del usuario.
 * @param player Puntero a la estructura del Jugador.
 * @return Un entero que representa la acción elegida (1 para Atacar, 2 para Usar Ítem, etc.).
 */
int player_choose_action(Player* player) {
    int choice;
    char input[10];

    printf("\nEs tu turno, %s!\n", player->name);
    printf("1. Atacar\n");
    printf("2. Usar Ítem (Inventario)\n"); // Añadida opción para usar ítem
    printf("Tu eleccion: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1; // Error de lectura
    }
    choice = atoi(input); // Convierte la cadena a entero

    // Validación básica de la elección
    if (choice < 1 || choice > 2) {
        printf("Opcion invalida. Por favor, elige una opcion valida.\n");
        return -1; // Indicar elección inválida
    }
    return choice;
}

/**
 * @brief Aplica una cantidad de daño a la vida actual de una entidad.
 * Asegura que la vida no baje de 0.
 * @param current_hp Puntero a la vida actual de la entidad que recibe el daño.
 * @param damage_dealt La cantidad de daño a aplicar.
 */
void apply_damage(int* current_hp, int damage_dealt) {
    if (current_hp == NULL) return;

    *current_hp -= damage_dealt;
    if (*current_hp < 0) {
        *current_hp = 0; // La vida no puede ser negativa
    }
}

// --- FUNCIÓN PRINCIPAL DE COMBATE ---

/**
 * @brief Gestiona el bucle de combate por turnos entre el jugador y un enemigo.
 * @param player Puntero a la estructura del Jugador actual.
 * @param enemy Puntero a la estructura del Enemigo actual al que se enfrenta.
 * @return true si el jugador gana el combate, false si el jugador es derrotado.
 */
bool combat_manage_turn(Player* player, Enemy* enemy) {
    if (player == NULL || enemy == NULL) {
        printf("Error: Jugador o enemigo nulo para el combate.\n");
        return false; // Error en la batalla
    }

    printf("\n--- ¡COMBATE INICIADO! %s vs %s ---\n", player->name, enemy->name);

    // Bucle principal de combate: se ejecuta mientras ambos estén vivos
    while (player->currentHP > 0 && enemy->currentHP > 0) {
        display_combat_status(player, enemy);

        // --- TURNO DEL JUGADOR ---
        int action_choice = player_choose_action(player);

        if (action_choice == 1) { // Atacar
            // Calcular el daño que el jugador inflige
            int player_effective_attack = player->attack + player->tempAttackBoost;
            int damage_to_enemy = calculate_damage(player_effective_attack, enemy->defense);

            apply_damage(&enemy->currentHP, damage_to_enemy);
            printf("%s ataca a %s y le inflige %d de daño.\n",
                   player->name, enemy->name, damage_to_enemy);

        } else if (action_choice == 2) { // Usar Ítem
            // Lógica para mostrar inventario y permitir al jugador seleccionar un ítem.
            // Esta parte requerirá la función player_use_consumable del módulo player.
            // NOTA: Para este esqueleto, solo es un placeholder. La implementación completa
            // de player_use_consumable y el menú de selección de inventario iría aquí.
            printf("--- Inventario de %s ---\n", player->name);
            if (player->inventoryCount == 0) {
                printf("Tu inventario esta vacio.\n");
            } else {
                for (int i = 0; i < player->inventoryCount; i++) {
                    Item currentItem = player->inventory[i];
                    printf("%d. %s (Tipo: %d, Cura: %d, Daño Boost: %d, Def Boost: %d, Duracion: %d)\n",
                           i + 1, currentItem.name, currentItem.type, currentItem.heal,
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
                    // Llama a la función de usar consumible del módulo player.
                    // ¡Asegúrate de que player_use_consumable esté implementada en player.c
                    // y declarada en player.h (probablemente descomentando la línea)!
                    // player_use_consumable(player, item_choice - 1);
                    printf("Usando item del inventario (Lógica player_use_consumable pendiente).\n"); // Placeholder
                } else {
                    printf("Cancelando uso de item.\n");
                }
            }
        } else {
            printf("Accion invalida. Pierdes tu turno.\n");
            // Si la acción es inválida, simplemente se salta el turno del jugador.
        }

        // --- Verificar si el enemigo fue derrotado después del turno del jugador ---
        if (enemy->currentHP <= 0) {
            printf("%s ha sido derrotado!\n", enemy->name);
            return true; // Jugador gana
        }

        // --- Actualizar efectos temporales del jugador (al final de su turno) ---
        // ¡Asegúrate de que player_update_temporary_boosts esté implementada en player.c
        // y declarada en player.h (probablemente descomentando la línea)!
        // player_update_temporary_boosts(player);
        printf("Actualizando efectos temporales del jugador (Lógica player_update_temporary_boosts pendiente).\n"); // Placeholder

        // --- TURNO DEL ENEMIGO ---
        printf("\nEs el turno de %s!\n", enemy->name);
        int enemy_damage_to_player = calculate_damage(enemy->attack, player->defense + player->tempDefenseBoost); // Usar defensa efectiva
        apply_damage(&player->currentHP, enemy_damage_to_player);
        printf("%s ataca a %s y le inflige %d de daño.\n",
               enemy->name, player->name, enemy_damage_to_player);

        // --- Verificar si el jugador fue derrotado después del turno del enemigo ---
        if (player->currentHP <= 0) {
            printf("%s ha sido derrotado por %s!\n", player->name, enemy->name);
            return false; // Jugador pierde
        }
        // Puedes añadir una pausa o esperar una tecla para continuar al siguiente turno aquí.
        // system("pause"); // Solo en Windows
        // getchar(); // Espera un Enter
    }

    // Esto debería ser inalcanzable si el bucle funciona correctamente,
    // pero es un fallback.
    return false; // Por defecto, si sale del bucle por alguna razón no intencionada
}
