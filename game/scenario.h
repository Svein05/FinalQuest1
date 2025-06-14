#ifndef SCENARIO_H
#define SCENARIO_H

#include <stdbool.h>    // Para usar el tipo de dato 'bool'
#include "data_types.h" // Incluimos data_types.h para las definiciones de Player, Enemy, Item, ScenarioNode

// --- DEFINICIONES DE TIPOS DE ESCENARIO ---
// Estos valores corresponden a los tipos de escenario en la estructura ScenarioNode.
// 1: Combate
// 2: Tienda (solo la inicial)
// 3: Evento Aleatorio (puede ser combate, mercader o bonus)
// 4: Jefe Final
#define SCENARIO_TYPE_COMBAT 1
#define SCENARIO_TYPE_SHOP 2
#define SCENARIO_TYPE_EVENT 3
#define SCENARIO_TYPE_BOSS 4

// --- DECLARACIONES DE FUNCIONES DEL MÓDULO SCENARIO ---

/**
 * @brief Carga todos los datos del juego (mapa de escenarios, enemigos, ítems)
 * desde archivos CSV y construye el mapa lineal del juego.
 *
 * @param scenariosCsvPath Ruta al archivo CSV de escenarios.
 * @param enemiesCsvPath Ruta al archivo CSV de enemigos.
 * @param itemsCsvPath Ruta al archivo CSV de ítems.
 * @return Un puntero al primer nodo del mapa de escenarios (lista enlazada),
 * o NULL en caso de error al cargar los datos.
 */
ScenarioNode* loadGameData(const char* scenariosCsvPath, const char* enemiesCsvPath, const char* itemsCsvPath);

/**
 * @brief Libera toda la memoria asignada dinámicamente para el mapa del juego
 * y los datos cargados (enemigos, ítems, etc.) que estén asociados a él.
 * Esto es crucial para evitar fugas de memoria al finalizar el juego.
 *
 * @param gameMap Puntero al primer nodo del mapa de escenarios a liberar.
 * @param allEnemies Arreglo de todos los enemigos cargados (para liberar su memoria si es dinámica).
 * @param allItems Arreglo de todos los ítems cargados (para liberar su memoria si es dinámica).
 */
void freeGameData(ScenarioNode* gameMap, Enemy* allEnemies, Item* allItems);

/**
 * @brief Obtiene el enemigo específico para un nodo de escenario de combate.
 * Este enemigo puede ser aleatorio según la dificultad del escenario,
 * o un enemigo predefinido si el escenario lo especifica.
 *
 * @param scenarioNode Puntero al nodo de escenario actual.
 * @param allEnemies Arreglo de todos los enemigos disponibles en el juego.
 * @param numEnemies Número total de enemigos en allEnemies.
 * @return Un puntero al enemigo que debe aparecer en este escenario.
 */
Enemy* getEnemyForScenario(ScenarioNode* scenarioNode, Enemy* allEnemies, int numEnemies);

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
void scenario_manage_event(Player* player, Item* allItems, int numItems, Enemy* allEnemies, int numEnemies);


// --- FUNCIONES ADICIONALES PARA LA CARGA DE DATOS ---
// Estas funciones podrían ser auxiliares internas o externas, dependiendo de la implementación
// en scenario.c. Aquí se incluyen como posibles declaraciones si se usan globalmente.

/**
 * @brief Carga los enemigos desde un archivo CSV.
 * @param enemiesCsvPath Ruta al archivo CSV de enemigos.
 * @param numEnemies Puntero a un entero donde se guardará el número de enemigos cargados.
 * @return Un puntero a un arreglo de estructuras Enemy, o NULL en caso de error.
 */
Enemy* loadEnemies(const char* enemiesCsvPath, int* numEnemies);

/**
 * @brief Carga los ítems desde un archivo CSV.
 * @param itemsCsvPath Ruta al archivo CSV de ítems.
 * @param numItems Puntero a un entero donde se guardará el número de ítems cargados.
 * @return Un puntero a un arreglo de estructuras Item, o NULL en caso de error.
 */
Item* loadItems(const char* itemsCsvPath, int* numItems);

/**
 * @brief Carga los escenarios desde un archivo CSV y construye la lista enlazada del mapa.
 * @param scenariosCsvPath Ruta al archivo CSV de escenarios.
 * @return Un puntero al primer nodo del mapa de escenarios, o NULL en caso de error.
 */
ScenarioNode* loadScenarios(const char* scenariosCsvPath);

// Función para liberar la memoria de un arreglo de enemigos (incluyendo sus cadenas)
void freeEnemies(Enemy* enemies, int count);
// Función para liberar la memoria de un arreglo de ítems (incluyendo sus cadenas)
void freeItems(Item* items, int count);
// Función para liberar la memoria del mapa de escenarios (nodos)
void freeScenarioMap(ScenarioNode* head);

#endif // SCENARIO_H
