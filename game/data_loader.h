#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <stdbool.h>
#include "data_types.h"
#include "lore.h"
#include "../tdas/map.h"
#include "../tdas/queue.h"

/**
 * @brief Libera todos los recursos dinámicos del juego.
 *
 * @param scenario_array Arreglo de escenarios.
 * @param enemy_array Arreglo de enemigos.
 * @param item_array Arreglo de ítems.
 * @param numEnemies Número de enemigos.
 * @param numItems Número de ítems.
 * @param numScenarios Número de escenarios.
 * @param game_map Cola del mapa del juego.
 * @param lore_map Mapa de lore.
 * @param tracker_ambiental Puntero al tracker de lore ambiental.
 * @param tracker_profundo Puntero al tracker de lore profundo.
 */
void free_all_resources(Scenario* scenario_array, Enemy* enemy_array, Item* item_array, int numEnemies, int numItems, int numScenarios, Queue* game_map, Map* lore_map, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo);

Enemy* load_enemies(const char* ENEMIES_CSV_PATH, int* numEnemies);
Item* load_items(const char* ITEMS_CSV_PATH, int* numItems); 
Map* load_initial_items_map(const char* INITIAL_ITEMS_CSV_PATH);
Scenario* load_scenarios(const char* SCENARIOS_CSV_PATH, int* numScenarios);
Map* load_lore_map(const char* lore_csv_path);


#endif // DATALOADER_H