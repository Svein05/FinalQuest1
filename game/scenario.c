#include <stdio.h>    // Para printf, fopen, fclose, perror
#include <stdlib.h>   // Para malloc, free, atoi, rand, srand
#include <string.h>   // Para strncpy, strlen, strcspn
#include <stdbool.h>  // Para bool
#include <time.h>     // Para srand(time(NULL))

#include "scenario.h"   // Declaraciones de las funciones de escenario
#include "data_types.h" // Definiciones de las estructuras Player, Enemy, Item, Scenario
#include "combat.h"     // Funciones de combate (combat_manage_turn)
#include "player.h"     // Funciones del jugador (player_add_item_to_inventory, etc.)
#include "shop.h"       // Funciones de tienda (shop_initialize_random_merchant, shop_interact, shop_free)
#include "../tdas/extra.h" // Función para leer líneas del CSV
#include "../tdas/stack.h"

// --- FUNCIONES DE LIBERACIÓN DE MEMORIA ---
#define NUM_EVENT_TYPES 3
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
    free(filteredEnemies); // Liberar memoria de la lista filtrada
    return spawnedEnemy; 
}

void poblarGameMap(Stack* game_map, Scenario* escenarios, int numScenarios) {
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

    // Empujar escenarios en orden inverso: 3 → 2 → 1
    int pushed = 0;
    if (count3 > 0) {
        Scenario* s = dificultad3[rand() % count3];
        stack_push(game_map, s);
        pushed++;
    }
    if (count2 > 0) {
        Scenario* s = dificultad2[rand() % count2];
        stack_push(game_map, s);
        pushed++;
    }
    if (count1 > 0) {
        Scenario* s = dificultad1[rand() % count1];
        stack_push(game_map, s);
        pushed++;
    }

    if (pushed == 0) {
        fprintf(stderr, "Error: No se pudo agregar ningún escenario al mapa\n");
    }
}

// --- Variables de control para eventos aleatorios ---
static int merchant_count = 0;
static int last_event_type = -1;

void scenario_manage_event(Player* player, Item* allItems, int numItems, Enemy* allEnemies, int numEnemies, int currentScenarioDifficulty) {
    if (player == NULL || allItems == NULL || numItems == 0 || allEnemies == NULL || numEnemies == 0) {
        printf("Error: Datos incompletos para gestionar evento.\n");
        return;
    }

    printf("\n--- EVENTO ALEATORIO ---\n");

    int event_type = -1;
    int roll = rand() % 100;
    // 0-54: combate (55%), 55-69: mercader (15%), 70-99: bonus (30%)
    if (roll < 55) {
        event_type = 0; // Combate
    } else if (roll < 70) {
        event_type = 1; // Mercader
    } else {
        event_type = 2; // Bonus
    }

    // Limitar mercader a 2 por escenario y nunca seguidos
    if (event_type == 1) {
        if (merchant_count >= 2 || last_event_type == 1) {
            event_type = (roll < 85) ? 0 : 2; // Si no puede ser mercader, prioriza combate
        } else {
            merchant_count++;
        }
    }
    if (event_type != 1) merchant_count = 0; // Reset si no es mercader

    last_event_type = event_type;

    if (event_type == 0) { // Combate
        printf("Has encontrado un enemigo inesperado!\n");
        Enemy* randomEnemy = spawnRandomEnemy(currentScenarioDifficulty, allEnemies, numEnemies);
        printf("¡Un %s aparece!\n", randomEnemy->name);
        Enemy combatEnemy = *randomEnemy;
        bool combatWon = combat_manage_turn(player, &combatEnemy);
        if (combatWon) {
            int base = rand() % 51 + 50;
            int multiplier = 133 + (rand() % 3) * 33;
            int won_gold = combatEnemy.difficulty * base * multiplier / 100;
            printf("Has derrotado a %s! Ganas %d de oro.\n", combatEnemy.name, won_gold);
            player->gold += won_gold; 
        } else {
            printf("Has sido derrotado por %s!.\n", combatEnemy.name);
            player->currentHP = 0;
        }
    } else if (event_type == 1) { // Mercader
        printf("Has encontrado a un mercader errante!\n");
        Shop* randomMerchant = shop_initialize_random_merchant(
            "items.csv",
            1,
            3
        );
        if (randomMerchant != NULL) {
            shop_interact(player, randomMerchant);
            shop_free(randomMerchant);
        } else {
            printf("El mercader no tenia nada que vender o hubo un error.\n");
        }
    } else { // Bonus
        printf("Has descubierto algo interesante!\n");
        int bonus_type = rand() % 10; // 0-3: oro (40%), 4-6: stats (30%), 7-9: item (30%)
        if (bonus_type < 4) { // Oro
            int gold_found = (rand() % 100) + 50;
            player->gold += gold_found;
            printf("Encontraste %d oro!\n", gold_found);
        } else if (bonus_type < 7) { // Stats
            int stat_choice = rand() % 2;
            if (stat_choice == 0) {
                int atk_boost = (rand() % 5) + 1;
                player->attack += atk_boost;
                printf("Te sientes mas fuerte! Tu ataque aumento en %d.\n", atk_boost);
            } else {
                int def_boost = (rand() % 3) + 1;
                player->defense += def_boost;
                printf("Tu piel se ha endurecido! Tu defensa aumento en %d.\n", def_boost);
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
    }
    printf("--- FIN DE EVENTO ---\n");
}

bool FINALBOSS(Player* player, Enemy* allEnemies, int numEnemies) {
    // Aquí podrías implementar la lógica del jefe final.
    // Por ahora, simplemente retornamos true para simular que el jugador lo derrotó.
    printf("¡Has llegado al jefe final! Preparándote para la batalla...\n");
    // Simulación de combate con el jefe final
    // Aquí podrías llamar a combat_manage_turn() con un enemigo especial.
    return true; // Simulamos que el jugador gana
}