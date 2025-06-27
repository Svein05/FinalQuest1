#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

// Los módulos que se van a utilizar
#include "game/data_loader.h"
#include "game/data_types.h" 
#include "game/player.h"     
#include "game/scenario.h"  
#include "game/ui.h"        
#include "game/lore.h"
#include "tdas/extra.h"      
#include "tdas/queue.h"

// Rutas a archivos CSV
#define SCENARIOS_CSV_PATH "data/scenarios.csv"
#define ENEMIES_CSV_PATH "data/enemies.csv"
#define ITEMS_CSV_PATH "data/items.csv"
#define INITIAL_ITEMS_CSV_PATH "data/initial_items.csv"
#define LORE_CSV_PATH "data/lore.csv"
#define MAX_DIFFICULTY 3
#define MAX_STEPS_PER_SCENARIO 1

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
        LoreTracker tracker_ambiental, tracker_profundo;

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

        Map* lore_map = lore_init_all(LORE_CSV_PATH, &tracker_ambiental, &tracker_profundo);
        if (lore_map == NULL) return EXIT_FAILURE;

        // --- 3. Bucle Principal del Juego: Recorrer el Mapa ---
        poblarGameMap(game_map, scenario_array, numScenarios); // Crear una cola para el mapa del juego
        Scenario* currentScenario = queue_front(game_map); // Comenzar desde el primer escenario

        player_add_initial_class_items(&player, INITIAL_ITEMS_CSV_PATH);

        // Mostrar portada del juego usando el lore_map y tipo -1 (portada)
        ui_lore_zero(lore_map, -1);

        while (currentScenario != NULL) {
            clearScreen();
            ui_scenario(currentScenario);
            ui_player_summary(&player);

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
                    free_all_resources(scenario_array, enemy_array, item_array, numEnemies, numItems, numScenarios, game_map, lore_map, &tracker_ambiental, &tracker_profundo);
                    continue;
                }
                printf("\nNo has logrado derrotar al jefe final. Fin del juego.\n");
            }
            printf("\n--- FIN DEL JUEGO ---\n");
        } else if (player.currentHP <= 0) {
            printf("Mejor suerte la proxima vez, %s.\n", player.name);
        }

        // --- 4. Liberar Memoria ---
        free_all_resources(scenario_array, enemy_array, item_array, numEnemies, numItems, numScenarios, game_map, lore_map, &tracker_ambiental, &tracker_profundo);
    } while (gameover_retry_flag);
    printf("¡Gracias por jugar!\n");
    return EXIT_SUCCESS; 
}
