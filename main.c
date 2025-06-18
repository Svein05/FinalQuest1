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

// --- FUNCIÓN PRINCIPAL DEL JUEGO ---
int main() {
    SetConsoleOutputCP(CP_UTF8);
    clearScreen();
    printf("--- ¡BIENVENIDO A TU AVENTURA! ---\n");
    printf("Un juego de rol sencillo en C.\n");
    printf("Elige tu clase:\n");
    printf("1. Guerrero (Balanceado)\n");
    printf("2. Tanque (Mucha defensa y vida, menos daño)\n");
    printf("3. Asesino (Mucho daño, poca vida y defensa)\n");
    int clase = 0;
    while (clase < 1 || clase > 3) {
        printf("Ingresa el número de tu clase: ");
        char input[10];
        fgets(input, sizeof(input), stdin);
        clase = atoi(input);
    }
    char* nombreClase;
    int hp, atk, def, oro;
    switch (clase) {
        case 1: nombreClase = "Guerrero"; hp = 100; atk = 10; def = 5; oro = 200; break;
        case 2: nombreClase = "Tanque";   hp = 130; atk = 7;  def = 12; oro = 200; break;
        case 3: nombreClase = "Asesino";  hp = 70;  atk = 18; def = 2; oro = 200; break;
    }
    Player player;
    initializePlayer(&player, nombreClase, hp, atk, def, oro); 
    // HP, Atk, Def, Oro inicial

    // Añadir TDAS
    Enemy* enemy_array = NULL;
    Item* item_array = NULL;
    Scenario* scenario_array = NULL;
    Stack* game_map = stack_create(NULL);

    int numEnemies = 0;
    int numItems = 0;  
    int numScenarios = 0;

    // --- 2. Cargar Datos del Juego ---
    printf("Cargando datos del juego\n");
    //wait_three_points();

    enemy_array = load_enemies(ENEMIES_CSV_PATH, &numEnemies);
    if (enemy_array == NULL) {
        fprintf(stderr, "Error: No se pudieron cargar los enemigos. Saliendo.\n");
        return EXIT_FAILURE;
    } printf("Enemigos cargados: %d\n", numEnemies);

    item_array = load_items(ITEMS_CSV_PATH, &numItems);
    if (item_array == NULL) {
        fprintf(stderr, "Error: No se pudieron cargar los ítems. Saliendo.\n");

        freeEnemies(enemy_array);
        return EXIT_FAILURE;
    } printf("Ítems cargados: %d\n", numItems);
    
    scenario_array = load_scenarios(SCENARIOS_CSV_PATH, &numScenarios);
    if (game_map == NULL) {
        fprintf(stderr, "Error: No se pudieron cargar los escenarios. Saliendo.\n");
        
        freeEnemies(enemy_array);
        freeItems(item_array);
        return EXIT_FAILURE;
    }

    // --- 3. Bucle Principal del Juego: Recorrer el Mapa ---
    // GENERAR UN COMANDO PARA POBLAR STACK GAMEMAP EN BASE A LOS ESCENARIOS CARGADOS - SE TIENE QUE ELEGIR AL AZAR UNO ENTRE CADA DIFICULTAD DEL 1 AL 3
    poblarGameMap(game_map, scenario_array, numScenarios); // Crear el stack para el mapa del juego
    Scenario* currentScenario = stack_top(game_map); // Comenzar desde el primer escenario
    int scenario_counter = 0;
    
    printf("Todo cargado correctamente. ¡Comencemos la aventura!\n");
    waitForKeyPress();
    while (currentScenario != NULL) {
        clearScreen();
        if (scenario_counter == 0) {
            welcome_zero(&player); // Mostrar bienvenida y primer escenario
            
            // Añadir ítems iniciales al inventario del jugador
            int numInitialItems = 0;
            Item* initialItems = load_initial_items(INITIAL_ITEMS_CSV_PATH, &numInitialItems);
            if (initialItems == NULL) {
                printf("No se encontraron ítems iniciales para añadir al inventario.\n");
                exit(EXIT_FAILURE);
            }

            // Solo añadir los ítems de la clase elegida
            for (int i = 0; i < numInitialItems; i++) {
                if ((clase == 1 && strcmp(initialItems[i].class, "Guerrero") == 0) ||
                    (clase == 2 && strcmp(initialItems[i].class, "Tanque") == 0) ||
                    (clase == 3 && strcmp(initialItems[i].class, "Asesino") == 0)) {
                    if (!player_add_item_to_inventory(&player, initialItems[i])) {
                        printf("No se pudo añadir el ítem %s al inventario.\n", initialItems[i].name);
                    } else Sleep(1000);
                }
            }
            freeItems(initialItems); // Liberar memoria de los ítems iniciales
            
            printf("Automaticamente te equiparás con tu mejor equipamiento.\n");
            waitForKeyPress();
            scenario_counter++;
        } else {
            printf("\n--- ESCENARIO %d ---\n", scenario_counter);
            printf("Estas en: %s\n", currentScenario->name);
            printf("%s\n", currentScenario->description);
            int steps = MAX_STEPS_PER_SCENARIO; // Simular pasos del jugador en el escenario actual
            
            while (steps) { 
                scenario_manage_event(&player, item_array, numItems, enemy_array, numEnemies, currentScenario->difficulty); // Manejar el evento del escenario actual
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
