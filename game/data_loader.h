#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <stdbool.h>
#include "data_types.h"
#include "../tdas/map.h"

void free_tokens(char** tokens);

void freeEnemies(Enemy* enemies);
void freeItems(Item* item);
void freeScenarioMap(Scenario* head);
void freeGameData(Scenario* gameMap, Enemy* enemy_array, Item* item_array);

Enemy* load_enemies(const char* ENEMIES_CSV_PATH, int* numEnemies);
Item* load_items(const char* ITEMS_CSV_PATH, int* numItems); 
Item* load_initial_items(const char* INITIAL_ITEMS_CSV_PATH, int* numItems);
Map* load_initial_items_map(const char* INITIAL_ITEMS_CSV_PATH);
Scenario* load_scenarios(const char* SCENARIOS_CSV_PATH, int* numScenarios);
int int_key_equal(void* a, void* b);
Map* load_lore_map(const char* lore_csv_path);


#endif // DATALOADER_H