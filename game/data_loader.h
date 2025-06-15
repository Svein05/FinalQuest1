#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <stdbool.h>
#include "data_types.h"

void free_tokens(char** tokens);

void freeEnemies(Enemy* enemies);
void freeItems(Item* item);
void freeScenarioMap(Scenario* head);
void freeGameData(Scenario* gameMap, Enemy* enemy_array, Item* item_array);

Enemy* load_enemies(const char* ENEMIES_CSV_PATH, int* numEnemies);
Item* load_items(const char* ITEMS_CSV_PATH, int* numItems); 
Item* load_initial_items(const char* INITIAL_ITEMS_CSV_PATH, int* numItems);
Scenario* load_scenarios(const char* SCENARIOS_CSV_PATH, int* numScenarios);


#endif // DATALOADER_H