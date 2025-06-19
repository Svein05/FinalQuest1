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

// Rutas a archivos CSV
#define SCENARIOS_CSV_PATH "data/scenarios.csv"
#define ENEMIES_CSV_PATH "data/enemies.csv"
#define ITEMS_CSV_PATH "data/items.csv"
#define INITIAL_ITEMS_CSV_PATH "data/initial_items.csv"
#define MAX_DIFFICULTY 3    
#define MAX_STEPS_PER_SCENARIO 8

int main() {
    SetConsoleOutputCP(CP_UTF8);
    clearScreen();

    // --- 1. Inicializamos al Jugador ---
    Player player;
    player_choose_and_assign_class(&player);

    Enemy* enemy_array = NULL;
    Item* item_array = NULL;
    Scenario* scenario_array = NULL;
    Stack* game_map = stack_create(NULL);

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
    poblarGameMap(game_map, scenario_array, numScenarios); // Crear el stack para el mapa del juego
    Scenario* currentScenario = stack_top(game_map); // Comenzar desde el primer escenario
    int scenario_counter = 0;
    
    // Quite el if de scenario uno, porque era innecesario ya que solo sucedia una vez
    // asique solamente se carga una vez afuera el inicio del juego y ya 
    // luego funciona el juego de manera normal.
    pretty_loading_animation("Cargando datos del juego");
    player_add_initial_class_items(&player, INITIAL_ITEMS_CSV_PATH);
    waitForKeyPress();
    while (currentScenario != NULL) {
        clearScreen();
        display_scenario(currentScenario);
        display_player_summary(&player);

        int steps = MAX_STEPS_PER_SCENARIO; // Simular pasos del jugador en el escenario actual
            
        waitForKeyPress();
        while (steps) { 
            scenario_manage_event(&player, item_array, numItems, enemy_array, numEnemies, currentScenario); // Manejar el evento del escenario actual
            printf("Pasos restantes: %d\n", steps);
            steps--;
            if (player.currentHP <= 0) { // Si el jugador ha muerto, termina el juego
                printf("Has sido derrotado. Fin del juego.\n");
                currentScenario = NULL; // Terminar el bucle
                break;
            }
        }
            
        if (currentScenario != NULL) {  // Si el juego no terminó, avanza al siguiente escenario
            stack_pop(game_map);        // Sacar el escenario actual del stack
            currentScenario = stack_top(game_map); // Obtener el siguiente escenario en el stack
            scenario_counter++;
        }
        
    }
    

    if (player.currentHP > 0 && currentScenario == NULL) { // Si el bucle terminó por el final del mapa
        if (FINALBOSS(&player, enemy_array, numEnemies)) { // Luchar contra el jefe final
            printf("\n¡Felicidades! Has derrotado al jefe final y completado el juego.\n");
        }
        printf("\n--- FIN DEL JUEGO ---\n");
        printf("¡Gracias por jugar, %s! Has llegado al final de tu aventura.\n", player.name);
    } else if (player.currentHP <= 0) {
        printf("Mejor suerte la proxima vez, %s.\n", player.name);
    }

    // --- 4. Liberar Memoria ---
    freeGameData(scenario_array, enemy_array, item_array); // Llama a la función de limpieza
    stack_clean(game_map); // Liberar el stack del mapa del juego

    return EXIT_SUCCESS; // El programa terminó exitosamente
}
