#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

// Los módulos que se van a utilizar
#include "game/data_types.h" // Estructuras de datos
#include "game/player.h"     // Funciones del jugador
#include "game/combat.h"     // Funciones de combate
#include "game/shop.h"       // Funciones de tienda
#include "game/scenario.h"   // Funciones de escenario
#include "tdas/extra.h"

// --- RUTAS A TUS ARCHIVOS CSV ---
#define SCENARIOS_CSV_PATH "data/scenarios.csv"
#define ENEMIES_CSV_PATH "data/enemies.csv"
#define ITEMS_CSV_PATH "data/items.csv"
#define INITIAL_ITEMS_CSV_PATH "data/initial_items.csv"

// --- FUNCIÓN PRINCIPAL DEL JUEGO ---
int main() {
    SetConsoleOutputCP(CP_UTF8);
    limpiarPantalla();
    printf("--- ¡BIENVENIDO A TU AVENTURA! ---\n");
    printf("Un juego de rol sencillo en C.\n");
    presioneTeclaParaContinuar();
    limpiarPantalla();

    // --- 1. Inicializar Jugador ---
    Player player;
    initializePlayer(&player, "Heroe Valiente", 100, 10, 5, 200); 
    // HP, Atk, Def, Oro inicial

    // --- 2. Cargar Datos del Juego ---
    // NOTA IMPORTANTE: La función loadGameData en scenario.c carga todo,
    // pero actualmente retorna solo ScenarioNode*. Para obtener allEnemies y allItems
    // en main.c, llamaremos a loadEnemies y loadItems por separado.
    // Una mejora futura podría ser tener una estructura GameData que contenga todo.

    Enemy* allEnemies = NULL;
    int numEnemies = 0;
    Item* allItems = NULL;
    int numItems = 0;
    ScenarioNode* gameMap = NULL;

    allEnemies = loadEnemies(ENEMIES_CSV_PATH, &numEnemies);
    if (allEnemies == NULL) {
        fprintf(stderr, "Error: No se pudieron cargar los enemigos. Saliendo.\n");
        return EXIT_FAILURE;
    }

    allItems = loadItems(ITEMS_CSV_PATH, &numItems);
    if (allItems == NULL) {
        fprintf(stderr, "Error: No se pudieron cargar los ítems. Saliendo.\n");
        // Asegúrate de liberar los enemigos si los ítems fallan
        freeEnemies(allEnemies, numEnemies);
        return EXIT_FAILURE;
    }

    gameMap = loadScenarios(SCENARIOS_CSV_PATH);
    if (gameMap == NULL) {
        fprintf(stderr, "Error: No se pudieron cargar los escenarios. Saliendo.\n");
        // Asegúrate de liberar enemigos e ítems si los escenarios fallan
        freeEnemies(allEnemies, numEnemies);
        freeItems(allItems, numItems);
        return EXIT_FAILURE;
    }

    // --- 3. Bucle Principal del Juego: Recorrer el Mapa ---
    ScenarioNode* currentScenario = gameMap;
    int scenario_counter = 1;

    while (currentScenario != NULL) {
        limpiarPantalla();
        printf("\n--- ESCENARIO %d ---\n", scenario_counter);
        printf("Estas en: %s\n", currentScenario->description);

        if (player.currentHP <= 0) { // Comprobar si el jugador murió en el escenario anterior
            printf("\n--- GAME OVER ---\n");
            printf("Tu aventura ha terminado. Has sido derrotado.\n");
            break;
        }

        switch (currentScenario->type) {
            case SCENARIO_TYPE_COMBAT: {
                printf("¡Un combate te espera!\n");
                Enemy* enemy_to_fight = getEnemyForScenario(currentScenario, allEnemies, numEnemies);
                if (enemy_to_fight == NULL) {
                    printf("Error: No se pudo encontrar un enemigo para este escenario. Saltando...\n");
                    break;
                }
                // Crear una copia temporal del enemigo para el combate, para no modificar el original en allEnemies
                Enemy combatEnemyCopy = *enemy_to_fight;
                bool playerWon = combat_manage_turn(&player, &combatEnemyCopy);
                if (!playerWon) {
                    // El jugador ha sido derrotado, el bucle principal se romperá en la siguiente iteración
                    // o aquí si se quiere salir inmediatamente.
                    printf("¡Tu aventura ha terminado aquí!\n");
                    currentScenario = NULL; // Forzar salida del bucle principal
                } else {
                    printf("\nHas superado el combate en %s!\n", currentScenario->description);
                }
                presioneTeclaParaContinuar();
                break;
            }
            case SCENARIO_TYPE_SHOP: {
                printf("Has encontrado una tienda.\n");
                Shop* startShop = shop_initialize_start_shop(ITEMS_CSV_PATH);
                if (startShop != NULL) {
                    shop_interact(&player, startShop);
                    shop_free(startShop);
                } else {
                    printf("No se pudo iniciar la tienda.\n");
                }
                presioneTeclaParaContinuar();
                break;
            }
            case SCENARIO_TYPE_EVENT: {
                printf("Hay un evento especial aquí.\n");
                scenario_manage_event(&player, allItems, numItems, allEnemies, numEnemies);
                if (player.currentHP <= 0) { // Si el evento resultó en muerte (ej. combate)
                    printf("\n¡Tu aventura ha terminado!\n");
                    currentScenario = NULL; // Forzar salida
                }
                presioneTeclaParaContinuar();
                break;
            }
            case SCENARIO_TYPE_BOSS: {
                printf("¡Te enfrentas al Jefe Final del calabozo!\n");
                // Para el jefe final, getEnemyForScenario debería devolver un enemigo específico o el más difícil.
                // Aquí podrías asignar un boss directamente si su ID está en el CSV de escenarios
                // o si es el último enemigo en la lista de enemigos de mayor dificultad.
                Enemy* bossEnemy = getEnemyForScenario(currentScenario, allEnemies, numEnemies);
                if (bossEnemy == NULL) {
                    printf("Error: No se pudo encontrar al jefe final. Abortando.\n");
                    currentScenario = NULL;
                    break;
                }
                Enemy combatBossCopy = *bossEnemy; // Copia para el combate
                bool playerWon = combat_manage_turn(&player, &combatBossCopy);
                if (!playerWon) {
                    printf("¡La oscuridad te ha consumido! Game Over.\n");
                    currentScenario = NULL; // Forzar salida
                } else {
                    printf("\n¡FELICITACIONES! Has derrotado al poderoso %s y completado tu aventura!\n", combatBossCopy.name);
                    player.gold += combatBossCopy.goldReward * 2; // Recompensa extra por jefe
                    printf("Recompensa del Jefe: %d oro.\n", combatBossCopy.goldReward * 2);
                    currentScenario = NULL; // El juego termina después del jefe
                }
                presioneTeclaParaContinuar();
                break;
            }
            default:
                printf("Tipo de escenario desconocido. Saltando...\n");
                presioneTeclaParaContinuar();
                break;
        }

        if (currentScenario != NULL) { // Si el juego no terminó, avanza al siguiente escenario
            currentScenario = currentScenario->next;
            scenario_counter++;
        }
    }

    printf("\n--- FIN DEL JUEGO ---\n");
    if (player.currentHP > 0 && currentScenario == NULL) { // Si el bucle terminó por el final del mapa
        printf("¡Gracias por jugar, %s! Has llegado al final de tu aventura.\n", player.name);
    } else if (player.currentHP <= 0) {
        printf("Mejor suerte la proxima vez, %s.\n", player.name);
    }

    // --- 4. Liberar Memoria ---
    printf("\nLiberando recursos del juego...\n");
    freeGameData(gameMap, allEnemies, allItems); // Llama a la función de limpieza

    return EXIT_SUCCESS; // El programa terminó exitosamente
}
