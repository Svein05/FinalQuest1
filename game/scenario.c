#include <stdio.h>    // Para printf, fopen, fclose, perror
#include <stdlib.h>   // Para malloc, free, atoi, rand, srand
#include <string.h>   // Para strncpy, strlen, strcspn
#include <stdbool.h>  // Para bool
#include <time.h>     // Para srand(time(NULL))

#include "scenario.h"   // Declaraciones de las funciones de escenario
#include "data_types.h" // Definiciones de las estructuras Player, Enemy, Item, Scenario
#include "combat.h"     // Funciones de combate (combat_manage_turn)
#include "player.h"     // Funciones del jugador (player_add_item_to_inventory, etc.)
#include "shop.h"       // Funciones de tienda (shop_initialize_random_merchant, shop_interact)
#include "../tdas/map.h" // Para Map*
#include "../tdas/extra.h" // Función para leer líneas del CSV
#include "../tdas/queue.h"
#include "lore.h" // Incluir lore.h para lógica de trackers

// --- FUNCIONES DE LIBERACIÓN DE MEMORIA ---
#define NUM_EVENT_TYPES 4 // Ahora hay 4 tipos de eventos
#define MAX_DIFFICULTY 3    

Enemy* spawnRandomEnemy(int currentScenarioDifficulty, Enemy* enemy_array, int numEnemies) {
    if (enemy_array == NULL || numEnemies <= 0) {
        printf("Error: No hay enemigos disponibles para spawn.\n");
        return NULL;
    }
    // Filtrar enemigos por dificultad
    Enemy* filteredEnemies = malloc(sizeof(Enemy) * numEnemies);
    if (filteredEnemies == NULL) {
        printf("Error: No se pudo asignar memoria para enemigos filtrados.\n");
        return NULL;
    }
    int count = 0;
    for (int i = 0; i < numEnemies; i++) {
        if (enemy_array[i].difficulty == currentScenarioDifficulty) {
            filteredEnemies[count++] = enemy_array[i];
        }
    }
    if (count == 0) {
        printf("Error: No hay enemigos disponibles con la dificultad %d.\n", currentScenarioDifficulty);
        free(filteredEnemies);
        return NULL;
    }
    // Seleccionar un enemigo aleatorio de los filtrados
    int randomIndex = rand() % count;
    Enemy* spawnedEnemy = malloc(sizeof(Enemy));
    if (spawnedEnemy == NULL) {
        printf("Error: No se pudo asignar memoria para el enemigo spawn.\n");
        free(filteredEnemies);
        return NULL;
    }
    *spawnedEnemy = filteredEnemies[randomIndex]; // Copiar el enemigo seleccionado
    
    // Para el boss final (dificultad 4), asegurar que tenga HP completo
    if (currentScenarioDifficulty == 4) {
        spawnedEnemy->currentHP = spawnedEnemy->HP;
    } else {
        spawnedEnemy->currentHP = spawnedEnemy->HP; // HP completo para todos
    }
    
    free(filteredEnemies); // Liberar memoria de la lista filtrada
    return spawnedEnemy; 
}

void poblarGameMap(Queue* game_map, Scenario* escenarios, int numScenarios) {
    // Validación de parámetros
    if (!game_map || !escenarios || numScenarios <= 0) {
        fprintf(stderr, "Error: Parámetros inválidos para poblarGameMap\n");
        return;
    }

    srand(time(NULL)); // semilla de RNG

    // Listas temporales para escenarios por dificultad
    Scenario* dificultad1[10] = {NULL};
    Scenario* dificultad2[10] = {NULL}; 
    Scenario* dificultad3[10] = {NULL}; 
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    
    // Clasificar escenarios por dificultad
    for (int i = 0; i < numScenarios; i++) {
        if (escenarios[i].difficulty < 1 || escenarios[i].difficulty > 3) {
            fprintf(stderr, "Advertencia: Escenario con dificultad inválida %d\n", 
                    escenarios[i].difficulty);
            continue;
        }

        switch (escenarios[i].difficulty) {
            case 1: dificultad1[count1++] = &escenarios[i]; break;
            case 2: dificultad2[count2++] = &escenarios[i]; break;
            case 3: dificultad3[count3++] = &escenarios[i]; break;
        }
    }

    // Insertar escenarios en orden: 1 → 2 → 3
    int pushed = 0;
    if (count1 > 0) {
        Scenario* s = dificultad1[rand() % count1];
        queue_insert(game_map, s);
        pushed++;
    }
    if (count2 > 0) {
        Scenario* s = dificultad2[rand() % count2];
        queue_insert(game_map, s);
        pushed++;
    }
    if (count3 > 0) {
        Scenario* s = dificultad3[rand() % count3];
        queue_insert(game_map, s);
        pushed++;
    }

    if (pushed == 0) {
        fprintf(stderr, "Error: No se pudo agregar ningún escenario al mapa\n");
    }
}

// --- Variables de control para eventos aleatorios ---
static int merchant_count = 0;
static int last_event_type = -1;
static int forced_merchant = 0; // Para forzar aparición de mercader
static int scenario_event_count = 0; // Cuenta eventos en el escenario

// --- Variable global para reinicio tras derrota ---
int gameover_retry_flag = 0;

static int elegir_evento(int *merchant_count, int last_event_type, int forced_merchant, int scenario_event_count) {
    // Si el mercader no ha salido 2 veces, forzamos su aparición (pero nunca dos veces seguidas)
    if (*merchant_count < 2 && last_event_type != 1) {
        // Forzar mercader cada 3 eventos si no ha salido suficiente
        if ((scenario_event_count % 3 == 2) || (forced_merchant < 2 && rand() % 4 == 0)) {
            return 1; // Mercader
        }
    }
    // Probabilidades: 0-69 combate, 70-84 bonus, 85-99 lore
    int roll = rand() % 100;
    int event_type = -1;
    if (roll < 70) event_type = 0; // Combate
    else if (roll < 85) event_type = 2; // Bonus
    else event_type = 3; // Lore
    // Si el evento es igual al anterior y NO es combate, elegir otro (excepto si solo queda mercader)
    if (event_type == last_event_type && event_type != 0) {
        if (*merchant_count < 2 && last_event_type != 1) return 1; // Mercader
        // Alternar entre bonus y lore si bonus/lore fue el anterior
        event_type = (event_type == 2) ? 3 : 2;
    }
    return event_type;
}

void scenario_manage_event(Player* player, Item* allItems, int numItems, Enemy* allEnemies, int numEnemies, Scenario *scenario, Map* lore_map, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo) {
    if (player == NULL || allItems == NULL || numItems == 0 || allEnemies == NULL || numEnemies == 0) {
        printf("Error: Datos incompletos para gestionar evento.\n");
        return;
    }

    clearScreen();  

    int currentScenarioDifficulty = scenario->difficulty;
    int event_type = -1;
    scenario_event_count++;
    event_type = elegir_evento(&merchant_count, last_event_type, forced_merchant, scenario_event_count);

    // Limitar mercader a 2 por escenario y nunca seguidos
    if (event_type == 1) {
        if (merchant_count >= 2 || last_event_type == 1) {
            // Si ya salió 2 veces o fue el último, elige otro evento
            event_type = (rand() % 2) ? 0 : ((rand() % 2) ? 2 : 3); // Prioriza combate, luego bonus/lore
        } else {
            merchant_count++;
            forced_merchant++;
        }
    }
    if (event_type != 1) forced_merchant = 0; // Reset si no es mercader
    if (event_type != 1) merchant_count = (merchant_count > 2) ? 2 : merchant_count; // No resetear merchant_count si ya salió 2 veces

    // Evitar dos eventos iguales seguidos
    if (event_type == last_event_type) {
        if (event_type == 0) event_type = (rand() % 2) ? 2 : 3;
        else event_type = 0;
    }
    last_event_type = event_type;

    if (event_type == 0) { // Combate
        Enemy* randomEnemy = spawnRandomEnemy(currentScenarioDifficulty, allEnemies, numEnemies);
        ui_combat_text();
        Enemy combatEnemy = *randomEnemy;
        bool combatWon = combat_manage_turn(player, &combatEnemy);
        if (combatWon) {
            int base = rand() % 51 + 50;
            int multiplier = 133 + (rand() % 3) * 33;
            int won_gold = combatEnemy.difficulty * base * multiplier / 100;
            printf("\x1b[33m═══════════════════════════════════════════════════════════════\x1b[0m\n");
            printf("\x1b[33m🏅  %s ha caído en combate. ¡Recompensa: %d oro!\x1b[0m\n", combatEnemy.name, won_gold);
            printf("\x1b[33m═══════════════════════════════════════════════════════════════\x1b[0m\n");
            player->gold += won_gold; 
        } else {
            player->currentHP = 0;
            // Menú para reiniciar o salir
            if (ui_gameover_retry()) gameover_retry_flag = 1;
            if (!gameover_retry_flag) return; // Si elige salir, cortar la función inmediatamente
        }
        show_random_lore_no_repeat(lore_map, tracker_ambiental, 0);
    } else if (event_type == 1) { // Mercader
        printf("Un mercader aparece en tu camino");
        ui_wait_dots();
        Map* itemMap = shop_initialize_random_merchant(allItems, numItems, currentScenarioDifficulty, player);
        if (itemMap != NULL) {
            shop_interact(player, itemMap);
            map_destroy(itemMap);
        } else {
            printf("El mercader no tenia nada que vender o hubo un error.\n");
        }
        show_random_lore_no_repeat(lore_map, tracker_ambiental, 0); // Mostrar lore ambiental
    } else if (event_type == 2) { // Bonus
        printf("\x1b[33m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
        printf("\x1b[33m            ¡Has descubierto algo interesante!\x1b[0m\n");
        printf("\x1b[33m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");

        printf("\x1b[33m   _________\n");
        printf("  /        /\\\n");
        printf(" /        /  \\\n");
        printf("/________/____\\\n");
        printf("|        |    |\n");
        printf("|        | 💰 |\n");
        printf("|________|____|\x1b[0m\n\n");
        printf("Buscando");
        ui_wait_dots();
        int bonus_type = rand() % 10; // 0-3: oro (40%), 4-6: stats (30%), 7-9: item (30%)
        if (bonus_type < 4) { // Oro
            int gold_found = (rand() % 100) + 50;
            player->gold += gold_found;
            printf("Encontraste \x1b[33m%d oro\x1b[0m!\n", gold_found);
        } else if (bonus_type < 7) { // Stats
            int stat_choice = rand() % 2;
            if (stat_choice == 0) {
                int atk_boost = (rand() % 5) + 1;
                player->attack += atk_boost;
                printf("Te sientes mas fuerte! \x1b[31mTu ataque aumento en %d\x1b[0m.\n", atk_boost);
            } else {
                int def_boost = (rand() % 3) + 1;
                player->defense += def_boost;
                printf("Tu piel se ha endurecido! \x1b[34mTu defensa aumento en %d\x1b[0m.\n", def_boost);
            }
        } else { // Ítem (menos frecuente)
            if (numItems > 0) {
                Item randomItem = allItems[rand() % numItems];
                if (player_add_item_to_inventory(player, randomItem)) {
                    printf("Encontraste un %s!\n", randomItem.name);
                } else {
                    printf("Encontraste un %s, pero tu inventario esta lleno!\n", randomItem.name);
                }
            } else {
                printf("No se encontraron ítems para dar como bonificación.\n");
            }
        }
        show_random_lore_no_repeat(lore_map, tracker_ambiental, 0); // Mostrar lore ambiental
        waitForKeyPress();
    } else if (event_type == 3) { // Historia/Lore
        printf("Recuerdos vienen hacia ti");
        ui_wait_dots();
        clearScreen();
        show_random_lore_no_repeat(lore_map, tracker_profundo, 1); // Mostrar lore profundo
        waitForKeyPress();
    }
    printf("--- FIN DE EVENTO ---\n");
}

bool FINALBOSS(Player* player, Enemy* allEnemies, int numEnemies, Map* lore_map, LoreTracker* tracker_profundo) {
    if (!player || !allEnemies || numEnemies <= 0) {
        printf("Error: Parámetros inválidos para el boss final.\n");
        return false;
    }

    // Buscar el boss final (dificultad 4)
    Enemy* finalBoss = spawnRandomEnemy(4, allEnemies, numEnemies);
    if (!finalBoss) {
        printf("Error: No se pudo encontrar el boss final.\n");
        return false;
    }

    // Mostrar la entrada épica del boss final
    ui_entrance_boss(finalBoss->name);

    // Dar una última oportunidad al jugador para prepararse
    printf("\x1b[93m╔═══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[93m║              ÚLTIMA OPORTUNIDAD DE PREPARACIÓN                ║\x1b[0m\n");
    printf("\x1b[93m╠═══════════════════════════════════════════════════════════════╣\x1b[0m\n");
    printf("\x1b[93m║  ¿Quieres usar algún ítem de tu inventario antes del combate? ║\x1b[0m\n");
    printf("\x1b[93m║                    [1] Sí  [2] No, estoy listo                ║\x1b[0m\n");
    printf("\x1b[93m╚═══════════════════════════════════════════════════════════════╝\x1b[0m\n");
    
    char input[10];
    printf("Tu elección: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        int choice = atoi(input);
        if (choice == 1) {
            printf("\x1b[96m¡Úsalo sabiamente, puede ser tu última oportunidad!\x1b[0m\n\n");
            // --- Inventario de uso de ítem (igual que combate normal) ---
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
        }
    }

    // Mostrar estadísticas finales antes del combate
    printf("\x1b[95m╔═══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[95m║                     ESTADÍSTICAS FINALES                      ║\x1b[0m\n");
    printf("\x1b[95m╠═══════════════════════════════════════════════════════════════╣\x1b[0m\n");
    printf("\x1b[95m║  Héroe: %-20s  Enemigos Derrotados: %-8d   ║\x1b[0m\n", 
           player->name, player->enemiesDefeated);
    printf("\x1b[95m║  HP: %3d/%-3d  ATK: %-3d  DEF: %-3d  Oro: %-5d                ║\x1b[0m\n", 
           player->currentHP, player->maxHP, 
           player->attack + player->tempAttackBoost,
           player->defense + player->tempDefenseBoost, 
           player->gold);
    printf("\x1b[95m╚═══════════════════════════════════════════════════════════════╝\x1b[0m\n\n");
    
    printf("¡Que el destino esté de tu lado!");
    ui_wait_dots();

    // ¡COMBATE FINAL!
    bool victory = combat_final_boss(player, finalBoss);

    if (victory) {
        // ¡VICTORIA ÉPICA!
        ui_boss_victory();
        
        // Recompensas épicas por derrotar al boss final
        int epic_gold = 5000;
        player->gold += epic_gold;
        player->enemiesDefeated++;
        
        printf("\x1b[93m╔═══════════════════════════════════════════════════════════════╗\x1b[0m\n");
        printf("\x1b[93m║                      RECOMPENSAS ÉPICAS                       ║\x1b[0m\n");
        printf("\x1b[93m╠═══════════════════════════════════════════════════════════════╣\x1b[0m\n");
        printf("\x1b[93m║  • Oro del Tesoro Final: %d                                 ║\x1b[0m\n", epic_gold);
        printf("\x1b[93m║  • Título: 'Devorador de Devoradores'                         ║\x1b[0m\n");
        printf("\x1b[93m║  • Leyenda Eterna: Tu nombre será recordado por siempre       ║\x1b[0m\n");
        printf("\x1b[93m╚═══════════════════════════════════════════════════════════════╝\x1b[0m\n");
        
        free(finalBoss);
        clearScreen();
        show_random_lore_no_repeat(lore_map, tracker_profundo, 2);
        return true;
    } else {
        // Derrota final
        ui_boss_defeat(finalBoss->name);
        // Menú para reiniciar o salir
        if (ui_gameover_retry()) gameover_retry_flag = 1;
        free(finalBoss);
        return false;
    }
}

// Recibe el Map* de lore, el tracker y el tipo de evento, y muestra un fragmento aleatorio no repetido
void show_random_lore_no_repeat(Map* lore_map, LoreTracker* tracker, int tipo) {
    int key = tipo;
    MapPair* pair = map_search(lore_map, &key);
    if (!pair || !pair->value) return;
    List* lista = (List*)pair->value;
    int n = list_size(lista);
    if (n == 0) return;
    int idx = get_random_unused_lore(tracker);
    if (idx == -1) {
        // Si ya se mostraron todos, reiniciar tracker y volver a elegir
        free_lore_tracker(tracker);
        init_lore_tracker(tracker, tipo, n);
        idx = get_random_unused_lore(tracker);
    }
    void* node = list_first(lista);
    for (int i = 0; i < idx; i++) node = list_next(lista);
    char* lore = (char*)node;
    mark_lore_used(tracker, idx);
    ui_lore_event(lore);
}