#include <stdio.h>    // Para printf, fopen, fclose, perror
#include <stdlib.h>   // Para malloc, free, atoi, rand, srand
#include <string.h>   // Para strncpy, strlen, strcspn
#include <stdbool.h>  // Para bool
#include <time.h>     // Para srand(time(NULL))

#include "scenario.h"   // Declaraciones de las funciones de escenario
#include "data_types.h" // Definiciones de las estructuras Player, Enemy, Item, ScenarioNode
#include "combat.h"     // Funciones de combate (combat_manage_turn)
#include "player.h"     // Funciones del jugador (player_add_item_to_inventory, etc.)
#include "shop.h"       // Funciones de tienda (shop_initialize_random_merchant, shop_interact, shop_free)
#include "../tdas/extra.h" // Función para leer líneas del CSV

// --- CONSTANTES INTERNAS ---
#define CSV_DELIMITER ',' // Separador de campos en los archivos CSV
#define NUM_EVENT_TYPES 3 // Número de tipos de eventos aleatorios (Batalla, Mercader, Bonus)

// --- ASUNCIÓN DE leer_linea_csv ---
// La función leer_linea_csv(FILE *archivo, char separador)
// se asume que está definida en "tdas/extra.h" y que:
// 1. Usa memoria estática internamente para los tokens que devuelve (char**).
// 2. NO es necesario que el llamador (este .c) libere esa memoria con free().
// 3. El arreglo de char* devuelto por leer_linea_csv está terminado en NULL.

// --- FUNCIONES AUXILIARES INTERNAS PARA PARSEO DE CSV ---

/**
 * @brief Parsea un arreglo de tokens de cadena en una estructura Enemy.
 * Asume el orden de las columnas del CSV:
 * ID,Nombre,currentHP,attack,defense,goldReward,difficulty
 * @param tokens Arreglo de cadenas (char**) a parsear.
 * @param enemy Puntero a la estructura Enemy donde se guardarán los datos.
 * @return true si el parseo fue exitoso, false en caso de error.
 */
static bool parse_enemy_from_tokens(char** tokens, Enemy* enemy) {
    if (tokens == NULL || enemy == NULL) return false;

    enemy->id = atoi(tokens[0]);
    strncpy(enemy->name, tokens[1], sizeof(enemy->name) - 1);
    enemy->name[sizeof(enemy->name) - 1] = '\0';
    enemy->currentHP = atoi(tokens[2]);
    enemy->attack = atoi(tokens[3]);
    enemy->defense = atoi(tokens[4]);
    enemy->goldReward = atoi(tokens[5]);
    enemy->difficulty = atoi(tokens[6]);

    return true;
}

/**
 * @brief Parsea un arreglo de tokens de cadena en una estructura Item.
 * Asume el orden de las columnas del CSV:
 * ID,Nombre,Tipo,Rareza,Damage,Defense,Heal,Costo,Dificultad,EffectDuration
 * @param tokens Arreglo de cadenas (char**) a parsear.
 * @param item Puntero a la estructura Item donde se guardarán los datos.
 * @return true si el parseo fue exitoso, false en caso de error.
 */
static bool parse_item_from_tokens(char** tokens, Item* item) {
    if (tokens == NULL || item == NULL) return false;

    item->id = atoi(tokens[0]);
    strncpy(item->name, tokens[1], sizeof(item->name) - 1);
    item->name[sizeof(item->name) - 1] = '\0';
    item->type = atoi(tokens[2]);
    strncpy(item->rarity, tokens[3], sizeof(item->rarity) - 1);
    item->rarity[sizeof(item->rarity) - 1] = '\0';
    item->damage = atoi(tokens[4]);
    item->defense = atoi(tokens[5]);
    item->heal = atoi(tokens[6]);
    item->cost = atoi(tokens[7]);
    item->difficulty = atoi(tokens[8]);
    item->effectDuration = atoi(tokens[9]);

    return true;
}

/**
 * @brief Parsea un arreglo de tokens de cadena en una estructura ScenarioNode.
 * Asume el orden de las columnas del CSV:
 * ID,Difficulty,Description,Type
 * @param tokens Arreglo de cadenas (char**) a parsear.
 * @param node Puntero a la estructura ScenarioNode donde se guardarán los datos.
 * @return true si el parseo fue exitoso, false en caso de error.
 */
static bool parse_scenario_from_tokens(char** tokens, ScenarioNode* node) {
    if (tokens == NULL || node == NULL) return false;

    node->id = atoi(tokens[0]);
    node->difficulty = atoi(tokens[1]);
    strncpy(node->description, tokens[2], sizeof(node->description) - 1);
    node->description[sizeof(node->description) - 1] = '\0';
    node->type = atoi(tokens[3]);
    node->next = NULL; // Siempre inicializar como NULL
    node->boss = NULL; // Siempre inicializar como NULL, se asignará si es un nodo de jefe

    return true;
}

// --- FUNCIONES DE LIBERACIÓN DE MEMORIA ---

/**
 * @brief Libera la memoria de un arreglo de estructuras Enemy.
 * Como las cadenas (name) son de tamaño fijo, solo se libera el arreglo principal.
 * @param enemies Arreglo de enemigos a liberar.
 * @param count Número de enemigos en el arreglo.
 */
void freeEnemies(Enemy* enemies, int count) {
    if (enemies != NULL) {
        // No hay cadenas dinámicas char* en Enemy, así que solo liberamos el arreglo.
        free(enemies);
        printf("Memoria de %d enemigos liberada.\n", count);
    }
}

/**
 * @brief Libera la memoria de un arreglo de estructuras Item.
 * Como las cadenas (name, rarity) son de tamaño fijo, solo se libera el arreglo principal.
 * @param items Arreglo de ítems a liberar.
 * @param count Número de ítems en el arreglo.
 */
void freeItems(Item* items, int count) {
    if (items != NULL) {
        // No hay cadenas dinámicas char* en Item, así que solo liberamos el arreglo.
        free(items);
        printf("Memoria de %d ítems liberada.\n", count);
    }
}

/**
 * @brief Libera la memoria del mapa de escenarios (lista enlazada de ScenarioNode).
 * @param head Puntero al primer nodo del mapa.
 */
void freeScenarioMap(ScenarioNode* head) {
    ScenarioNode* current = head;
    while (current != NULL) {
        ScenarioNode* next_node = current->next;
        // Si el nodo de escenario tiene un puntero a un boss,
        // la memoria de ese boss se libera con el arreglo general de enemigos,
        // no aquí.
        free(current);
        current = next_node;
    }
    printf("Memoria del mapa de escenarios liberada.\n");
}

/**
 * @brief Libera toda la memoria asignada dinámicamente para el mapa del juego
 * y los datos cargados.
 * @param gameMap Puntero al primer nodo del mapa de escenarios.
 * @param allEnemies Arreglo de todos los enemigos cargados.
 * @param allItems Arreglo de todos los ítems cargados.
 */
void freeGameData(ScenarioNode* gameMap, Enemy* allEnemies, Item* allItems) {
    freeScenarioMap(gameMap);
    freeEnemies(allEnemies, 0); // Count no es necesario para free (solo para el mensaje)
    freeItems(allItems, 0);     // Count no es necesario para free
    printf("Todos los datos del juego han sido liberados.\n");
}

// --- FUNCIONES DE CARGA DE DATOS ---

/**
 * @brief Carga los enemigos desde un archivo CSV.
 * @param enemiesCsvPath Ruta al archivo CSV de enemigos.
 * @param numEnemies Puntero a un entero donde se guardará el número de enemigos cargados.
 * @return Un puntero a un arreglo de estructuras Enemy, o NULL en caso de error.
 */
Enemy* loadEnemies(const char* enemiesCsvPath, int* numEnemies) {
    FILE* file = fopen(enemiesCsvPath, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo de enemigos");
        *numEnemies = 0;
        return NULL;
    }

    Enemy* enemies = NULL;
    int count = 0;
    int capacity = 10;
    enemies = (Enemy*) malloc(sizeof(Enemy) * capacity);
    if (enemies == NULL) {
        perror("Error al asignar memoria inicial para enemigos");
        fclose(file);
        *numEnemies = 0;
        return NULL;
    }

    char** tokens = NULL;
    // Saltar la línea de encabezado
    tokens = leer_linea_csv(file, CSV_DELIMITER);
    if (tokens != NULL) { /* Asumimos que leer_linea_csv gestiona su memoria estática */ }

    while ((tokens = leer_linea_csv(file, CSV_DELIMITER)) != NULL) {
        if (count >= capacity) {
            capacity *= 2;
            Enemy* temp_realloc = (Enemy*) realloc(enemies, sizeof(Enemy) * capacity);
            if (temp_realloc == NULL) {
                perror("Error al redimensionar memoria para enemigos");
                freeEnemies(enemies, count);
                fclose(file);
                *numEnemies = 0;
                return NULL;
            }
            enemies = temp_realloc;
        }

        if (parse_enemy_from_tokens(tokens, &enemies[count])) {
            count++;
        } else {
            printf("Advertencia: Error al parsear un enemigo. Saltando linea.\n");
        }
    }

    fclose(file);
    *numEnemies = count;
    printf("Cargados %d enemigos desde %s.\n", count, enemiesCsvPath);
    return enemies;
}

/**
 * @brief Carga los ítems desde un archivo CSV.
 * @param itemsCsvPath Ruta al archivo CSV de ítems.
 * @param numItems Puntero a un entero donde se guardará el número de ítems cargados.
 * @return Un puntero a un arreglo de estructuras Item, o NULL en caso de error.
 */
Item* loadItems(const char* itemsCsvPath, int* numItems) {
    FILE* file = fopen(itemsCsvPath, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo de items");
        *numItems = 0;
        return NULL;
    }

    Item* items = NULL;
    int count = 0;
    int capacity = 10;
    items = (Item*) malloc(sizeof(Item) * capacity);
    if (items == NULL) {
        perror("Error al asignar memoria inicial para items");
        fclose(file);
        *numItems = 0;
        return NULL;
    }

    char** tokens = NULL;
    // Saltar la línea de encabezado
    tokens = leer_linea_csv(file, CSV_DELIMITER);
    if (tokens != NULL) { /* Asumimos que leer_linea_csv gestiona su memoria estática */ }

    while ((tokens = leer_linea_csv(file, CSV_DELIMITER)) != NULL) {
        if (count >= capacity) {
            capacity *= 2;
            Item* temp_realloc = (Item*) realloc(items, sizeof(Item) * capacity);
            if (temp_realloc == NULL) {
                perror("Error al redimensionar memoria para items");
                freeItems(items, count);
                fclose(file);
                *numItems = 0;
                return NULL;
            }
            items = temp_realloc;
        }

        if (parse_item_from_tokens(tokens, &items[count])) {
            count++;
        } else {
            printf("Advertencia: Error al parsear un item. Saltando linea.\n");
        }
    }

    fclose(file);
    *numItems = count;
    printf("Cargados %d ítems desde %s.\n", count, itemsCsvPath);
    return items;
}

/**
 * @brief Carga los escenarios desde un archivo CSV y construye la lista enlazada del mapa.
 * @param scenariosCsvPath Ruta al archivo CSV de escenarios.
 * @return Un puntero al primer nodo del mapa de escenarios, o NULL en caso de error.
 */
ScenarioNode* loadScenarios(const char* scenariosCsvPath) {
    FILE* file = fopen(scenariosCsvPath, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo de escenarios");
        return NULL;
    }

    ScenarioNode* head = NULL;
    ScenarioNode* tail = NULL;

    char** tokens = NULL;
    // Saltar la línea de encabezado
    tokens = leer_linea_csv(file, CSV_DELIMITER);
    if (tokens != NULL) { /* Asumimos que leer_linea_csv gestiona su memoria estática */ }

    while ((tokens = leer_linea_csv(file, CSV_DELIMITER)) != NULL) {
        ScenarioNode* newNode = (ScenarioNode*) malloc(sizeof(ScenarioNode));
        if (newNode == NULL) {
            perror("Error al asignar memoria para un nodo de escenario");
            freeScenarioMap(head); // Liberar lo que ya se cargó
            fclose(file);
            return NULL;
        }

        if (parse_scenario_from_tokens(tokens, newNode)) {
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        } else {
            printf("Advertencia: Error al parsear un escenario. Saltando linea.\n");
            free(newNode); // Liberar el nodo si el parseo falla
        }
    }

    fclose(file);
    printf("Mapa de escenarios cargado desde %s.\n", scenariosCsvPath);
    return head;
}


/**
 * @brief Carga todos los datos del juego (mapa de escenarios, enemigos, ítems)
 * desde archivos CSV y construye el mapa lineal del juego.
 * @param scenariosCsvPath Ruta al archivo CSV de escenarios.
 * @param enemiesCsvPath Ruta al archivo CSV de enemigos.
 * @param itemsCsvPath Ruta al archivo CSV de ítems.
 * @return Un puntero al primer nodo del mapa de escenarios (lista enlazada),
 * o NULL en caso de error al cargar los datos.
 */
ScenarioNode* loadGameData(const char* scenariosCsvPath, const char* enemiesCsvPath, const char* itemsCsvPath) {
    // Inicializar el generador de números aleatorios una vez
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = true;
    }

    ScenarioNode* gameMap = NULL;
    Enemy* loadedEnemies = NULL;
    Item* loadedItems = NULL;
    int numEnemies = 0;
    int numItems = 0;

    printf("Cargando datos del juego...\n");

    loadedEnemies = loadEnemies(enemiesCsvPath, &numEnemies);
    if (loadedEnemies == NULL || numEnemies == 0) {
        printf("Fallo al cargar enemigos. Asegúrate que %s existe y tiene datos.\n", enemiesCsvPath);
        return NULL;
    }

    loadedItems = loadItems(itemsCsvPath, &numItems);
    if (loadedItems == NULL || numItems == 0) {
        printf("Fallo al cargar ítems. Asegúrate que %s existe y tiene datos.\n", itemsCsvPath);
        // Liberar enemigos ya cargados antes de salir
        freeEnemies(loadedEnemies, numEnemies);
        return NULL;
    }

    gameMap = loadScenarios(scenariosCsvPath);
    if (gameMap == NULL) {
        printf("Fallo al cargar escenarios. Asegúrate que %s existe y tiene datos.\n", scenariosCsvPath);
        // Liberar enemigos e ítems ya cargados antes de salir
        freeEnemies(loadedEnemies, numEnemies);
        freeItems(loadedItems, numItems);
        return NULL;
    }

    // Aquí, podrías iterar sobre gameMap para asignar los punteros a los boss
    // Si tus escenarios de tipo BOSS tienen un ID de enemigo específico en el CSV
    // que necesitarías para buscarlo en loadedEnemies.
    // Por ahora, asumiremos que getEnemyForScenario se encarga de esto.

    // Guardar los punteros a los datos cargados globalmente o pasarlos a main,
    // para que freeGameData pueda liberarlos al final.
    // Esto es un desafío con una función loadGameData que retorna solo ScenarioNode*.
    // Una opción es usar variables globales para loadedEnemies, loadedItems y sus counts
    // o pasar una struct que contenga todo GameData.
    // Para simplificar, asumiremos que main.c manejará estos punteros
    // y los pasará a freeGameData.

    printf("Datos del juego cargados exitosamente.\n");
    return gameMap; // gameMap es el puntero al inicio de la lista de escenarios
}


/**
 * @brief Obtiene el enemigo específico para un nodo de escenario de combate.
 * Este enemigo puede ser aleatorio según la dificultad del escenario,
 * o un enemigo predefinido si el escenario lo especifica (ej. Boss).
 *
 * @param scenarioNode Puntero al nodo de escenario actual.
 * @param allEnemies Arreglo de todos los enemigos disponibles en el juego.
 * @param numEnemies Número total de enemigos en allEnemies.
 * @return Un puntero al enemigo que debe aparecer en este escenario.
 */
Enemy* getEnemyForScenario(ScenarioNode* scenarioNode, Enemy* allEnemies, int numEnemies) {
    if (scenarioNode == NULL || allEnemies == NULL || numEnemies == 0) {
        return NULL; // Datos inválidos
    }

    // Si el escenario tiene un boss asignado directamente (para mini-jefes o jefe final)
    if (scenarioNode->boss != NULL) {
        return scenarioNode->boss;
    }

    // Si no es un boss específico, encontrar un enemigo aleatorio por dificultad
    Enemy* suitableEnemies[numEnemies]; // Un arreglo temporal para enemigos de la dificultad correcta
    int suitableCount = 0;

    for (int i = 0; i < numEnemies; i++) {
        if (allEnemies[i].difficulty == scenarioNode->difficulty) {
            // Evitar bosses si no es un nodo de boss, asumiendo que los bosses tienen dificultad alta o ID especial
            // Podrías añadir una condición tipo: && allEnemies[i].type != ENEMY_TYPE_BOSS si tuvieras un campo 'type' en Enemy
            suitableEnemies[suitableCount++] = &allEnemies[i];
        }
    }

    if (suitableCount == 0) {
        printf("Advertencia: No se encontraron enemigos adecuados para la dificultad %d.\n", scenarioNode->difficulty);
        return NULL; // No se encontró ningún enemigo adecuado
    }

    // Seleccionar un enemigo aleatorio de los adecuados
    int randomIndex = rand() % suitableCount;
    return suitableEnemies[randomIndex];
}

/**
 * @brief Gestiona un evento aleatorio cuando el jugador entra a un escenario de tipo EVENTO.
 * Puede resultar en un combate (con enemigo aleatorio), un encuentro con un mercader,
 * o una bonificación (oro, vida, estadísticas).
 *
 * @param player Puntero al jugador actual.
 * @param allItems Arreglo de todos los ítems disponibles en el juego.
 * @param numItems Número total de ítems en allItems.
 * @param allEnemies Arreglo de todos los enemigos disponibles en el juego.
 * @param numEnemies Número total de enemigos en allEnemies.
 */
void scenario_manage_event(Player* player, Item* allItems, int numItems, Enemy* allEnemies, int numEnemies) {
    if (player == NULL || allItems == NULL || numItems == 0 || allEnemies == NULL || numEnemies == 0) {
        printf("Error: Datos incompletos para gestionar evento.\n");
        return;
    }

    printf("\n--- EVENTO ALEATORIO ---\n");

    int event_type = rand() % NUM_EVENT_TYPES; // 0: Combate, 1: Mercader, 2: Bonus
    // TODO: Implementar la lógica para asegurar que el mercader aparezca al menos una vez por dificultad.
    // Esto podría requerir pasar el nivel de dificultad actual o un contador de eventos sin mercader.

    if (event_type == 0) { // Combate
        printf("Has encontrado un enemigo inesperado!\n");
        // Seleccionar un enemigo aleatorio basado en la dificultad actual del jugador o del escenario.
        // Aquí necesitamos una forma de saber la dificultad actual. Por simplicidad, un enemigo genérico.
        // O buscar un enemigo aleatorio entre allEnemies con una dificultad media.
        // Por ahora, seleccionamos un enemigo aleatorio de todos los disponibles.
        Enemy* randomEnemy = &allEnemies[rand() % numEnemies];
        printf("¡Un %s aparece!\n", randomEnemy->name);

        // Se usa una copia del enemigo para el combate, ya que su HP se modificará.
        // Esto es importante para no alterar el array global de enemigos.
        Enemy combatEnemy = *randomEnemy;

        bool combatWon = combat_manage_turn(player, &combatEnemy);
        if (combatWon) {
            printf("Has derrotado al %s! Ganas %d oro.\n", combatEnemy.name, combatEnemy.goldReward);
            player->gold += combatEnemy.goldReward;
        } else {
            printf("Has sido derrotado por el %s! Game Over.\n", combatEnemy.name);
            player->currentHP = 0; // Asegurarse de que el jugador esté "muerto"
        }

    } else if (event_type == 1) { // Mercader
        printf("Has encontrado a un mercader errante!\n");
        // Para este mercader aleatorio, podríamos usar un rango de dificultad basado en la dificultad del escenario actual
        // o del jugador. Por ahora, un rango fijo para la demostración.
        Shop* randomMerchant = shop_initialize_random_merchant(
            "items.csv", // Ruta a tu CSV de ítems global
            1, // Dificultad mínima de ítems del mercader
            3  // Dificultad máxima de ítems del mercader
        );
        if (randomMerchant != NULL) {
            shop_interact(player, randomMerchant);
            shop_free(randomMerchant); // Liberar la memoria del mercader después de la interacción
        } else {
            printf("El mercader no tenia nada que vender o hubo un error.\n");
        }

    } else { // event_type == 2: Bonificación (Oro o Ítem o Stats)
        printf("Has descubierto algo interesante!\n");
        int bonus_type = rand() % 3; // 0: Oro, 1: Ítem, 2: Stats

        if (bonus_type == 0) { // Oro
            int gold_found = (rand() % 100) + 50; // Entre 50 y 149 oro
            player->gold += gold_found;
            printf("Encontraste %d oro!\n", gold_found);
        } else if (bonus_type == 1) { // Ítem
            if (numItems > 0) {
                Item randomItem = allItems[rand() % numItems]; // Obtener un ítem aleatorio
                // Si el ítem ya es un arma o armadura equipada, no debería darlo así.
                // O solo dar ítems consumibles.
                if (player_add_item_to_inventory(player, randomItem)) {
                    printf("Encontraste un %s!\n", randomItem.name);
                } else {
                    printf("Encontraste un %s, pero tu inventario esta lleno!\n", randomItem.name);
                }
            } else {
                printf("No se encontraron ítems para dar como bonificación.\n");
            }
        } else { // Stats
            int stat_choice = rand() % 2; // 0: Ataque, 1: Defensa
            if (stat_choice == 0) {
                int atk_boost = (rand() % 5) + 1; // +1 a +5 ataque
                player->attack += atk_boost;
                printf("Te sientes mas fuerte! Tu ataque aumento en %d.\n", atk_boost);
            } else {
                int def_boost = (rand() % 3) + 1; // +1 a +3 defensa
                player->defense += def_boost;
                printf("Tu piel se ha endurecido! Tu defensa aumento en %d.\n", def_boost);
            }
        }
    }
    printf("--- FIN DE EVENTO ---\n");
}
