#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

// Los módulos que se van a utilizar
#include "game/data_loader.h"
#include "game/data_types.h" 
#include "game/player.h"     
#include "game/combat.h"   
#include "game/shop.h"       
#include "game/scenario.h"  
#include "game/ui.h"        
#include "tdas/extra.h"      
#include "tdas/stack.h"
#include "tdas/list.h"
#include "tdas/queue.h"

// Rutas a archivos CSV
#define SCENARIOS_CSV_PATH "data/scenarios.csv"
#define ENEMIES_CSV_PATH "data/enemies.csv"
#define ITEMS_CSV_PATH "data/items.csv"
#define INITIAL_ITEMS_CSV_PATH "data/initial_items.csv"
#define MAX_DIFFICULTY 3    
#define MAX_STEPS_PER_SCENARIO 5

extern int gameover_retry_flag;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    do {
        clearScreen();
        gameover_retry_flag = 0;

        // --- 1. Inicializamos al Jugador ---
        Player player;
        player_choose_and_assign_class(&player);

        Enemy* enemy_array = NULL;
        Item* item_array = NULL;
        Scenario* scenario_array = NULL;
        Queue* game_map = queue_create(NULL);

        int numEnemies = 0;
        int numItems = 0;  
        int numScenarios = 0;

        // --- 2. Cargar Datos del Juego ---
        enemy_array = load_enemies(ENEMIES_CSV_PATH, &numEnemies);
        if (enemy_array == NULL) return EXIT_FAILURE;

        item_array = load_items(ITEMS_CSV_PATH, &numItems);
        if (item_array == NULL) return EXIT_FAILURE;

        scenario_array = load_scenarios(SCENARIOS_CSV_PATH, &numScenarios);
        if (scenario_array == NULL) return EXIT_FAILURE;

        // --- 3. Bucle Principal del Juego: Recorrer el Mapa ---
        poblarGameMap(game_map, scenario_array, numScenarios); // Crear una cola para el mapa del juego
        Scenario* currentScenario = queue_front(game_map); // Comenzar desde el primer escenario

        player_add_initial_class_items(&player, INITIAL_ITEMS_CSV_PATH);

        // Cargar todos los fragmentos de lore agrupados por tipo
        Map* lore_map = load_lore_map("data/lore.csv");
        LoreTracker tracker_ambiental, tracker_profundo;
        int cantidad_ambiental = 0, cantidad_profundo = 0;
        if (lore_map) {
            int tipo_inicial = -1;
            MapPair* pair = map_search(lore_map, &tipo_inicial);
            if (pair && pair->value) {
                List* lista = (List*)pair->value;
                char* lore_inicial = (char*)list_first(lista); // Solo hay uno para tipo -1
                display_intro_lore_and_ascii(lore_inicial);
            } else {
                printf("No se encontro el lore inicial en el mapa.\n");
                waitForKeyPress();
            }
            // Inicializar trackers para lore ambiental (tipo 0) y profundo (tipo 1)
            int tipo_ambiental = 0, tipo_profundo = 1;
            MapPair* pair_ambiental = map_search(lore_map, &tipo_ambiental);
            MapPair* pair_profundo = map_search(lore_map, &tipo_profundo);
            if (pair_ambiental && pair_ambiental->value) cantidad_ambiental = list_size((List*)pair_ambiental->value);
            if (pair_profundo && pair_profundo->value) cantidad_profundo = list_size((List*)pair_profundo->value);
            init_lore_tracker(&tracker_ambiental, tipo_ambiental, cantidad_ambiental);
            init_lore_tracker(&tracker_profundo, tipo_profundo, cantidad_profundo);
        } else {
            printf("No se pudo cargar el mapa de lore.\n");
            waitForKeyPress();
        }

        while (currentScenario != NULL) {
            clearScreen();
            display_scenario(currentScenario);
            display_player_summary(&player);

            int steps = MAX_STEPS_PER_SCENARIO; // Simular pasos del jugador en el escenario actual
                
            waitForKeyPress();
            
            while (steps) { 
                // Generar el evento para el paso actual
                scenario_manage_event(&player, item_array, numItems, enemy_array, numEnemies, currentScenario, lore_map, &tracker_ambiental, &tracker_profundo); 
                printf("Pasos restantes: %d\n", steps);
                waitForKeyPress();
                steps--;

                // Si el jugador ha muerto, termina el juego
                if (player.currentHP <= 0) {
                    // Si el usuario eligió reiniciar, salir del bucle de escenarios
                    if (gameover_retry_flag) {
                        currentScenario = NULL;
                        break;
                    }
                    // Si el usuario eligió salir, terminar inmediatamente
                    break;
                }
                clearScreen();
            }
            
            // Si el juego no terminó, avanza al siguiente escenario
            if (currentScenario != NULL) {  
                queue_remove(game_map);       
                currentScenario = queue_front(game_map); 
            }
            
        }
        // Si el jugador ha llegado al final del juego y no ha muerto, se enfrenta al jefe final
        if (player.currentHP > 0 && currentScenario == NULL) { 
            if (FINALBOSS(&player, enemy_array, numEnemies)) { 
                printf("\n¡Felicidades! Has derrotado al jefe final y completado el juego.\n");
            } else {
                // Si el usuario eligió reiniciar tras perder con el boss, saltar a reinicio
                if (gameover_retry_flag) {
                    // Liberar memoria antes de reiniciar
                    freeGameData(scenario_array, enemy_array, item_array);
                    queue_clean(game_map);
                    free(lore_map);
                    if (lore_map) {
                        free_lore_tracker(&tracker_ambiental);
                        free_lore_tracker(&tracker_profundo);
                    }
                    continue;
                }
                printf("\nNo has logrado derrotar al jefe final. Fin del juego.\n");
            }
            printf("\n--- FIN DEL JUEGO ---\n");
        } else if (player.currentHP <= 0) {
            printf("Mejor suerte la proxima vez, %s.\n", player.name);
        }

        // --- 4. Liberar Memoria ---
        freeGameData(scenario_array, enemy_array, item_array);
        queue_clean(game_map);
        free(lore_map); // Liberar memoria del mapa de lore
        // Liberar memoria de trackers de lore
        if (lore_map) {
            free_lore_tracker(&tracker_ambiental);
            free_lore_tracker(&tracker_profundo);
        }
    } while (gameover_retry_flag);
    printf("¡Gracias por jugar!\n");
    return EXIT_SUCCESS; 
}
