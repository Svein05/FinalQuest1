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
#include "tdas/extra.h"      
#include "tdas/stack.h"
#include "tdas/list.h"

// Rutas a archivos CSV
#define SCENARIOS_CSV_PATH "data/scenarios.csv"
#define ENEMIES_CSV_PATH "data/enemies.csv"
#define ITEMS_CSV_PATH "data/items.csv"
#define INITIAL_ITEMS_CSV_PATH "data/initial_items.csv"
#define MAX_DIFFICULTY 3    

// --- FUNCIÓN PRINCIPAL DEL JUEGO ---
int main() {
    SetConsoleOutputCP(CP_UTF8);
    clearScreen();
    printf("--- ¡BIENVENIDO A TU AVENTURA! ---\n");
    printf("Un juego de rol sencillo en C.\n");
    waitForKeyPress();
    clearScreen();

    // --- 1. Inicializar Jugador ---
    Player player;
    initializePlayer(&player, "Heroe Valiente", 100, 10, 5, 200); 
    // HP, Atk, Def, Oro inicial

    Enemy* enemy_array = NULL;
    Item* item_array = NULL;
    Scenario* scenario_array = NULL;
    Stack* game_map = stack_create(NULL);

    int numEnemies = 0;
    int numItems = 0;  
    int numScenarios = 0;
    printf("Cargando datos del juego...\n");
    enemy_array = load_enemies(ENEMIES_CSV_PATH, &numEnemies);
    if (enemy_array == NULL) {
        fprintf(stderr, "Error: No se pudieron cargar los enemigos. Saliendo.\n");
        return EXIT_FAILURE;
    }
    printf("Enemigos cargados: %d\n", numEnemies);
    item_array = load_items(ITEMS_CSV_PATH, &numItems);
    if (item_array == NULL) {
        fprintf(stderr, "Error: No se pudieron cargar los ítems. Saliendo.\n");

        freeEnemies(enemy_array);
        return EXIT_FAILURE;
    }
    printf("Ítems cargados: %d\n", numItems);
    scenario_array = load_scenarios(SCENARIOS_CSV_PATH, &numScenarios);
    if (game_map == NULL) {
        fprintf(stderr, "Error: No se pudieron cargar los escenarios. Saliendo.\n");
        
        freeEnemies(enemy_array);
        freeItems(item_array);
        return EXIT_FAILURE;
    }

    printf("el pepe\n");
    // --- 3. Bucle Principal del Juego: Recorrer el Mapa ---
    // GENERAR UN COMANDO PARA POBLAR STACK GAMEMAP EN BASE A LOS ESCENARIOS CARGADOS - SE TIENE QUE ELEGIR AL AZAR UNO ENTRE CADA DIFICULTAD DEL 1 AL 3
    poblarGameMap(game_map, scenario_array, numScenarios); // Crear el stack para el mapa del juego
    Scenario* currentScenario = stack_top(game_map); // Comenzar desde el primer escenario
    int scenario_counter = 0;
    printf("current scenario: %s\n", currentScenario->description);
    printf("TODO LISTO PARA COMENZAAAAAAAAAAAAAAAAAR\n");
    waitForKeyPress();
    while (currentScenario != NULL) {
        clearScreen();
        if (scenario_counter == 0) {
            printf("--- INICIO DEL JUEGO ---\n");
            printf("¡Bienvenido, %s! Tu aventura comienza ahora.\n", player.name);
            printf("Explora el mapa y enfrenta los desafíos que te esperan.\n");

            waitForKeyPress(); // Esperar a que el jugador presione una tecla antes de continuar
            clearScreen();
            printf("\n--- ESCENARIO %d ---\n", scenario_counter);
            printf("Estas en: %s\n", currentScenario->description);
            printf("...\n");
            printf("......\n");
            printf("\n");
            printf("\n");
            printf("¡Es peligroso que vayas solo! Toma esto.\n");
        
            // Añadir ítems iniciales al inventario del jugador
            int numInitialItems = 0;
            Item* initialItems = load_initial_items(INITIAL_ITEMS_CSV_PATH, &numInitialItems);
            if (initialItems != NULL) {
                for (int i = 0; i < numInitialItems; i++) {
                    if (!player_add_item_to_inventory(&player, initialItems[i])) {
                        printf("No se pudo añadir el ítem %s al inventario.\n", initialItems[i].name);
                    }
                }
                freeItems(initialItems); // Liberar memoria de los ítems iniciales
            } else {
                printf("No se encontraron ítems iniciales para añadir al inventario.\n");
            }
            printf("¡Ahora estás listo para comenzar tu aventura!\n");
            waitForKeyPress();
            scenario_counter++; 
    } else {
        //// ESCRIBIR MAIN
        printf("\n--- ESCENARIO %d ---\n", scenario_counter);
        printf("Estas en: %s\n", currentScenario->description);
        printf("...\n");
        printf("......\n");
        printf("TESTEANDO ESCENARIO %d\n", currentScenario->id);
        if (currentScenario != NULL) { // Si el juego no terminó, avanza al siguiente escenario
            
            stack_pop(game_map); // Sacar el escenario actual del stack
            currentScenario = stack_top(game_map); // Obtener el siguiente escenario en el stack
            scenario_counter++;
            }
        }
    }
    

    if (player.currentHP > 0 && currentScenario == NULL) { // Si el bucle terminó por el final del mapa
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
