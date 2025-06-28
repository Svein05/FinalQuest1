#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "combat.h"
#include "data_types.h"
#include "player.h"
#include "ui.h"


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
 
bool combat_manage_turn(Player* player, Enemy* enemy) {
    // Validar que los parámetros no sean nulos
    if (player == NULL || enemy == NULL) {
        printf("Error: Jugador o enemigo nulo para el combate.\n");
        return false; // Error en la batalla
    }

    // Mostrar banner inicial del combate y pausa dramática
    ui_combat_banner(player->name, enemy->name);
    Sleep(1000);

    // Bucle principal de combate - continúa mientras ambos estén vivos
    while (player->currentHP > 0 && enemy->currentHP > 0) {
        // Mostrar estado actual de ambos combatientes
        display_combat_status(player, enemy);

        // --- TURNO DEL JUGADOR ---
        int action_choice = player_choose_action();

        if (action_choice == 1) { // Opción: Atacar
            // Calcular ataque efectivo incluyendo boosts temporales
            int player_effective_attack = player->attack + player->tempAttackBoost;
            int damage_to_enemy = calculate_damage(player_effective_attack, enemy->defense);

            // Aplicar daño al enemigo y mostrar resultado
            apply_damage(&enemy->currentHP, damage_to_enemy);
            printf("\x1b[36m» %s ataca a %s y le inflige %d de daño. «\x1b[0m\n", player->name, enemy->name, damage_to_enemy);
            printf("\x1b[90m──────────────────────────────────────────────────────────────\x1b[0m\n");
            Sleep(500);

        } else if (action_choice == 2) { // Opción: Usar ítem
            // Mostrar inventario con opciones de uso
            display_inventory(player, true, true);
            // Procesar selección de ítem del jugador
            char item_input[10];
            if (fgets(item_input, sizeof(item_input), stdin) == NULL) {
                printf("Error de lectura de item.\n");
            } else {
                int item_choice = atoi(item_input);
                // Validar que la selección esté en rango válido
                if (item_choice > 0 && item_choice <= player->inventoryCount) {
                    player_use_consumable(player, item_choice - 1);
                    waitForKeyPress();
                } else {
                    // Selección inválida o cancelación
                    printf("Cancelando uso de item.\n");
                    waitForKeyPress();
                }
            }
        } else {
            // Acción inválida - jugador pierde el turno
            ui_msg_error("Accion invalida. Pierdes tu turno.\n");
            Sleep(500);
        }

        // Verificar victoria del jugador tras su turno
        if (enemy->currentHP <= 0) {
            player->enemiesDefeated++;  // Incrementar contador de enemigos derrotados
            Sleep(500);
            return true; // Jugador gana la batalla
        }

        // Actualizar efectos temporales del jugador (boosts que expiran)
        player_update_temporary_boosts(player); 

        // --- TURNO DEL ENEMIGO ---
        printf("\x1b[31m⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦\x1b[0m\n");
        printf("\x1b[31m⇦  Es el turno de %s!\x1b[0m\n", enemy->name);
        printf("\x1b[31m⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇨⇦⇦⇦⇦⇦⇦⇦⇦\x1b[0m\n");
        
        // Calcular daño del enemigo considerando defensa efectiva del jugador
        int enemy_damage_to_player = calculate_damage(enemy->attack, player->defense + player->tempDefenseBoost);
        apply_damage(&player->currentHP, enemy_damage_to_player);
        printf("\x1b[31m« %s ataca a %s y le inflige %d de daño. »\x1b[0m\n", enemy->name, player->name, enemy_damage_to_player);
        printf("\x1b[90m──────────────────────────────────────────────────────────────\x1b[0m\n");

        // Verificar derrota del jugador tras turno del enemigo
        if (player->currentHP <= 0) {
            Sleep(500);
            return false; // Jugador pierde la batalla
        } else {
            // Continuar combate, esperar confirmación para siguiente turno
            waitForKeyPress();
        }
    }

    return false;
}

// === COMBATE ESPECIAL DEL BOSS FINAL ===

bool combat_final_boss(Player* player, Enemy* boss) {
    // Validar parámetros de entrada para el combate especial
    if (player == NULL || boss == NULL) {
        printf("Error: Parámetros inválidos para combate del boss final.\n");
        return false;
    }
    
    // Restaurar HP completo del boss para el combate final
    boss->currentHP = boss->HP;
    
    // Inicializar variables de estado especiales del boss final
    int boss_phase = 1; // Fase actual del boss (1, 2, 3)
    int boss_rage_turns = 0; 
    bool boss_enraged = false;
    bool boss_buffed_phase2 = false;
    bool boss_buffed_phase1 = false;

    // Bucle principal del combate final
    while (player->currentHP > 0 && boss->currentHP > 0) {
        clearScreen(); // Limpiar pantalla para efecto dramático
        
        // Calcular porcentaje de HP del boss para determinar fase
        int hp_percentage = (boss->currentHP * 100) / boss->HP;
        
        // Determinar fase del boss y aplicar buffs correspondientes
        if (hp_percentage > 66) {
            boss_phase = 1; // Fase inicial (>66% HP)
        } else if (hp_percentage > 33) {
            boss_phase = 2; // Fase intermedia (33-66% HP)
            if (!boss_buffed_phase2) {
                boss_buffed_phase2 = true;
                boss->attack += 10; // Incrementar ataque en fase 2
                ui_boss_phase2(); // Mostrar transición a fase 2
            }
        } else {
            boss_phase = 3; // Fase final (<33% HP)
            if (!boss_enraged) {
                boss_enraged = true;
                boss->attack += 20; // Gran incremento de ataque en fase final
                ui_boss_phase3(); // Mostrar transición a fase 3
            }
        }

        // Mostrar interfaz especial del combate final con información de fase
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
        
        if (action == 1) { // Opción: Atacar al boss
            // Calcular daño del jugador considerando boosts temporales
            int player_damage_to_boss = calculate_damage(player->attack + player->tempAttackBoost, boss->defense);
            apply_damage(&boss->currentHP, player_damage_to_boss);
            printf("\x1b[32m» %s ataca al %s y le inflige %d de daño. «\x1b[0m\n", 
                   player->name, boss->name, player_damage_to_boss);
        } else if (action == 2) { // Opción: Usar ítem
            // Manejo de inventario (igual que combate normal)
            display_inventory(player, true, true);
            char item_input[10];
            if (fgets(item_input, sizeof(item_input), stdin) == NULL) {
                printf("Error de lectura de item.\n");
            } else {
                int item_choice = atoi(item_input);
                // Validar selección de ítem
                if (item_choice > 0 && item_choice <= player->inventoryCount) {
                    player_use_consumable(player, item_choice - 1);
                    waitForKeyPress();
                } else {
                    printf("Cancelando uso de item.\n");
                    waitForKeyPress();
                }
            }
        }

        // Verificar victoria del jugador
        if (boss->currentHP <= 0) {
            printf("\x1b[93m¡Has derrotado al %s!\x1b[0m\n", boss->name);
            return true; // Jugador gana el combate final
        }

        // Actualizar efectos temporales del jugador antes del turno del boss
        player_update_temporary_boosts(player);

        // --- TURNO DEL BOSS FINAL (con mecánicas especiales) ---
        printf("\x1b[91m⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦\x1b[0m\n");
        printf("\x1b[91m⇦  ¡%s contraataca con poder abismal!\x1b[0m\n", boss->name);
        printf("\x1b[91m⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦⇦\x1b[0m\n");

        // Calcular probabilidad de ataque especial según la fase
        int boss_damage = 0;
        int special_attack_chance = (boss_phase - 1) * 20 + (boss_enraged ? 30 : 0); 
        // 0%, 20%, 40% + 30% si está en furia
        
        // Determinar si el boss usa ataque especial o normal
        if (rand() % 100 < special_attack_chance) {
            // Ejecutar ataque especial según la fase actual
            switch (boss_phase) {
                case 1:
                    printf("\x1b[95m¡%s usa 'Golpe Devastador'!\x1b[0m\n", boss->name);
                    boss_damage = calculate_damage(boss->attack * 1.3f, player->defense + player->tempDefenseBoost);
                    break;
                case 2:
                    printf("\x1b[96m¡%s canaliza 'Tormenta de Sombras'!\x1b[0m\n", boss->name);
                    boss_damage = calculate_damage(boss->attack * 1.5f, player->defense + player->tempDefenseBoost);
                    printf("\x1b[90m¡La oscuridad debilita tu defensa temporalmente!\x1b[0m\n");
                    player->tempDefenseBoost -= 5; // Aplicar debuff temporal al jugador
                    break;
                case 3:
                    printf("\x1b[91m¡%s desata 'ANIQUILACIÓN FINAL'!\x1b[0m\n", boss->name);
                    boss_damage = calculate_damage(boss->attack * 1.8f, player->defense + player->tempDefenseBoost);
                    printf("\x1b[91m¡El poder del vacío consume todo a su paso!\x1b[0m\n");
                    break;
            }
        } else {
            // Ataque normal del boss
            printf("\x1b[91m%s ataca con sus garras del vacío.\x1b[0m\n", boss->name);
            boss_damage = calculate_damage(boss->attack, player->defense + player->tempDefenseBoost);
        }
        
        // Aplicar daño del boss al jugador
        apply_damage(&player->currentHP, boss_damage);
        printf("\x1b[31m« %s inflige %d de daño devastador. »\x1b[0m\n", boss->name, boss_damage);
        printf("\x1b[90m──────────────────────────────────────────────────────────────\x1b[0m\n");

        // Verificar derrota del jugador
        if (player->currentHP <= 0) {
            printf("\x1b[91m¡%s ha caído ante el poder del %s!\x1b[0m\n", player->name, boss->name);
            return false; // Jugador pierde el combate final
        } else {
            waitForKeyPress();
        }

        // Incrementar contadores especiales del boss si está en furia
        if (boss_enraged) boss_rage_turns++;
    }

    return false; // Fallback de seguridad (no debería ejecutarse)
}