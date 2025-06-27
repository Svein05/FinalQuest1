#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

// Módulos del juego y estructuras de datos
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

// Parámetros de juego
#define MAX_DIFFICULTY 3
#define MAX_STEPS_PER_SCENARIO 1

// Variable para volver a jugar
extern int gameover_retry_flag;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    do {
        clearScreen();
        gameover_retry_flag = 0;

        // INICIALIZACIÓN DEL JUGADOR
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

        // CARGA DE DATOS DEL JUEGO
        enemy_array = load_enemies(ENEMIES_CSV_PATH, &numEnemies);
        if (enemy_array == NULL) return EXIT_FAILURE;

        item_array = load_items(ITEMS_CSV_PATH, &numItems);
        if (item_array == NULL) return EXIT_FAILURE;

        scenario_array = load_scenarios(SCENARIOS_CSV_PATH, &numScenarios);
        if (scenario_array == NULL) return EXIT_FAILURE;

        Map* lore_map = lore_init_all(LORE_CSV_PATH, &tracker_ambiental, &tracker_profundo);
        if (lore_map == NULL) return EXIT_FAILURE;

        // CONFIGURACIÓN DEL MAPA, LORE INICIAL Y ITEMS INICIALES
        poblarGameMap(game_map, scenario_array, numScenarios); // Crear cola de escenarios
        player_add_initial_class_items(&player, INITIAL_ITEMS_CSV_PATH);

        // Mostrar portada del juego con su lore inicial
        ui_lore_zero(lore_map, -1);

        // BUCLE PRINCIPAL DEL JUEGO
        Scenario* currentScenario = queue_front(game_map); // Primer escenario
        while (currentScenario != NULL) {
            clearScreen();
            ui_scenario(currentScenario); // Descripcion de Escenario
            ui_player_summary(&player);

            // Pasos en el escenario actual
            int steps = MAX_STEPS_PER_SCENARIO;
                
            waitForKeyPress();
            
            // SIMULAR PASOS
            while (steps) { 
                // Evento del escenario actual
                scenario_manage_event(&player, item_array, numItems, enemy_array, numEnemies, currentScenario, lore_map, &tracker_ambiental, &tracker_profundo); 
                printf("Pasos restantes: %d\n", steps);
                waitForKeyPress();
                steps--;

                // Si el jugador muere sale del bucle
                if (player.currentHP <= 0) {
                    if (gameover_retry_flag) {
                        currentScenario = NULL;
                        break;
                    }
                    break;
                }
                clearScreen();
            }
            // Avanzar al siguiente escenario si el juego no terminó
            if (currentScenario != NULL) {  
                queue_remove(game_map);       
                currentScenario = queue_front(game_map); 
            }
        }

        // ENFRENTAMIENTO FINAL (JEFE)
        if (player.currentHP > 0 && currentScenario == NULL) { 
            if (!FINALBOSS(&player, enemy_array, numEnemies, lore_map, &tracker_profundo) && gameover_retry_flag) { 
                free_all_resources(scenario_array, enemy_array, item_array, numEnemies, numItems, numScenarios, game_map, lore_map, &tracker_ambiental, &tracker_profundo);
                continue;
            }
            printf("\n--- FIN DEL JUEGO ---\n");
        } else if (player.currentHP <= 0) {
            printf("Mejor suerte la proxima vez, %s.\n", player.name);
        }

        // LIBERACIÓN DE MEMORIA Y REINICIO
        free_all_resources(scenario_array, enemy_array, item_array, numEnemies, numItems, numScenarios, game_map, lore_map, &tracker_ambiental, &tracker_profundo);
    } while (gameover_retry_flag);
    printf("¡Gracias por jugar!\n");
    return EXIT_SUCCESS; 
}
