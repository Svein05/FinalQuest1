#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>  
#include <stdbool.h> 
#include <time.h>   

#include "data_types.h"
#include "combat.h"
#include "player.h"
#include "shop.h"
#include "lore.h"
#include "../tdas/extra.h" 
#include "../tdas/map.h"
#include "../tdas/list.h"
#include "../tdas/queue.h"

#define CSV_DELIMITER ','
#define NUM_EVENT_TYPES 3 // (Batalla, Mercader, Bonus)
#define MAX_DIFFICULTY 3    

/**  --- FUNCIONES DE LECTURA ---
 * @param tokens Arreglo de cadenas (char**) a parsear; cada linea del .csv 
 * @return true si el parseo fue exitoso, false en caso de error.
*/
void free_tokens(char** tokens) {
    if (!tokens) return;

    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

void freeEnemies(Enemy* enemies) {
    if (enemies != NULL) {
        free(enemies); 
        // printf("Memoria de enemigos liberada.\n");
    }
}

void freeScenarioMap(Scenario* scenarios) {
    if (scenarios != NULL) {
        free(scenarios);
        // printf("Memoria de escenarios liberada.\n");
    }
}

void freeItems(Item* items) {
    if (items != NULL) {
        free(items);
        // printf("Memoria de ítems liberada.\n");
    }
}

void freeGameData(Scenario* gameMap, Enemy* enemy_array, Item* item_array, int numEnemies, int numItems, int numScenarios) {
    freeScenarioMap(gameMap);
    freeEnemies(enemy_array);
    freeItems(item_array);     
}

bool parse_enemy(char** tokens, Enemy* enemy) {
    if (tokens == NULL || enemy == NULL) return false;

    enemy->id = atoi(tokens[0]);
    strncpy(enemy->name, tokens[1], sizeof(enemy->name) - 1);
    enemy->name[sizeof(enemy->name) - 1] = '\0';
    enemy->HP = atoi(tokens[2]);
    enemy->currentHP = enemy->HP; // Inicializar currentHP igual a HP
    enemy->attack = atoi(tokens[3]);
    enemy->defense = atoi(tokens[4]);
    enemy->difficulty = atoi(tokens[5]);
    return true;
}

bool parse_item(char** tokens, Item* item) {
    if (tokens == NULL || item == NULL) return false;

    item->id = atoi(tokens[0]);
    strncpy(item->name, tokens[1], sizeof(item->name) - 1);
    item->name[sizeof(item->name) - 1] = '\0';
    item->type = atoi(tokens[2]);
    strncpy(item->rarity, tokens[3], sizeof(item->rarity) - 1);
    item->rarity[sizeof(item->rarity) - 1] = '\0';
    item->damage = atoi(tokens[4]);
    item->heal = atoi(tokens[5]);
    item->defense = atoi(tokens[6]);
    item->price = atoi(tokens[7]);
    item->difficulty = atoi(tokens[8]);
    item->effectDuration = (tokens[9] != NULL) ? atoi(tokens[9]) : 0;
    if (tokens[10] != NULL) {
        strncpy(item->class, tokens[10], sizeof(item->class) - 1);
        item->class[sizeof(item->class) - 1] = '\0';
    } else {
        item->class[0] = '\0';
    }
    return true;
}

bool parse_item_basic(char** tokens, Item* item) {
    if (tokens == NULL || item == NULL) return false;
    item->id = atoi(tokens[0]);
    strncpy(item->name, tokens[1], sizeof(item->name) - 1);
    item->name[sizeof(item->name) - 1] = '\0';
    item->type = atoi(tokens[2]);
    strncpy(item->rarity, tokens[3], sizeof(item->rarity) - 1);
    item->rarity[sizeof(item->rarity) - 1] = '\0';
    item->damage = atoi(tokens[4]);
    item->heal = atoi(tokens[5]);
    item->defense = atoi(tokens[6]);
    item->price = atoi(tokens[7]);
    item->difficulty = atoi(tokens[8]);
    item->effectDuration = atoi(tokens[9]);
    item->class[0] = '\0'; // No hay clase en items.csv
    return true;
}

bool parse_scenario(char** tokens, Scenario* node) {
    if (!tokens || !node) return false;

    // Verificar que tenemos todos los campos necesarios
    for (int i = 0; i < 4; i++) {
        if (!tokens[i]) {
            // printf(stderr, "Error: Faltan campos en el escenario\n");
            return false;
        }
    }

    // Parsear ID
    char* endptr;
    node->id = strtol(tokens[0], &endptr, 10);
    if (*endptr != '\0' || node->id <= 0) {
        // printf(stderr, "Error: ID de escenario inválido '%s'\n", tokens[0]);
        return false;
    }

    // Parsear Nombre (con protección de buffer)
    strncpy(node->name, tokens[1], sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';

    // Parsear Descripción (puede contener comas)
    strncpy(node->description, tokens[2], sizeof(node->description) - 1);
    node->description[sizeof(node->description) - 1] = '\0';

    // Parsear Dificultad
    node->difficulty = strtol(tokens[3], &endptr, 10);
    if (*endptr != '\0' || node->difficulty < 1 || node->difficulty > 3) {
        // printf(stderr, "Error: Dificultad inválida '%s' (debe ser 1-3)\n", tokens[3]);
        return false;
    }

    return true;
}

// --- FUNCIONES DE CARGA ---
Enemy* load_enemies(const char* ENEMIES_CSV_PATH, int* numEnemies) {
    FILE* file = fopen(ENEMIES_CSV_PATH, "r");
    if (!file) {
        perror("Error al abrir CSV");
        *numEnemies = 0;
        return NULL;
    }
    
    int capacity = 10;
    int count = 0;
    Enemy* enemies = malloc(sizeof(Enemy) * capacity);
    if (!enemies) {
        perror("Error al asignar memoria para enemigos");
        fclose(file);
        *numEnemies = 0;
        return NULL;
    }
    // printf("Memoria asignada para %d enemigos.\n", capacity);
    // Leer y descartar el encabezado
    char** tokens = read_csv_line(file, CSV_DELIMITER);
    free_tokens(tokens);

    // Leer enemigos del CSV
    // printf("Leyendo enemigos...\n");
    while ((tokens = read_csv_line(file, CSV_DELIMITER)) != NULL) {
        if (count >= capacity) {
            capacity *= 2;
            Enemy* temp = realloc(enemies, sizeof(Enemy) * capacity);
            if (!temp) {
                perror("Error al redimensionar memoria para enemigos");
                free(enemies);
                fclose(file);
                *numEnemies = 0;
                return NULL;
            }
            enemies = temp;
        }

        Enemy parsedEnemy;
        if (parse_enemy(tokens, &parsedEnemy)) {
            enemies[count++] = parsedEnemy;
        } else {
            printf("Advertencia: Error al parsear un enemigo. Saltando línea.\n");
        }

        free_tokens(tokens);
    }

    // printf("Total de enemigos leídos: %d\n", count);
    fclose(file);
    *numEnemies = count;
    // printf("Cargados %d enemigos desde %s.\n", count, ENEMIES_CSV_PATH);
    return enemies;
}


Item* load_items(const char* ITEMS_CSV_PATH, int* numItems) {
    FILE* file = fopen(ITEMS_CSV_PATH, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo de ítems");
        *numItems = 0;
        return NULL;
    }

    int capacity = 10;
    int count = 0;
    Item* items = malloc(sizeof(Item) * capacity);
    if (items == NULL) {
        perror("Error al asignar memoria inicial para ítems");
        fclose(file);
        *numItems = 0;
        return NULL;
    }

    // Leer encabezado
    char** tokens = read_csv_line(file, CSV_DELIMITER);
    free_tokens(tokens);

    while ((tokens = read_csv_line(file, CSV_DELIMITER)) != NULL) {
        if (count >= capacity) {
            capacity *= 2;
            Item* temp = realloc(items, sizeof(Item) * capacity);
            if (temp == NULL) {
                perror("Error al redimensionar memoria para ítems");
                freeItems(items);
                fclose(file);
                *numItems = 0;
                return NULL;
            }
            items = temp;
        }
        if (parse_item_basic(tokens, &items[count])) {
            count++;
        } else {
            printf("Advertencia: Error al parsear un ítem. Saltando línea.\n");
        }
        free_tokens(tokens);
    }

    fclose(file);
    *numItems = count;
    // printf("Cargados %d ítems desde %s.\n", count, ITEMS_CSV_PATH);
    return items;
}

Scenario* load_scenarios(const char* SCENARIOS_CSV_PATH, int* numScenarios) {
    FILE* file = fopen(SCENARIOS_CSV_PATH, "r");
    if (!file) {
        perror("Error al abrir el archivo de escenarios");
        *numScenarios = 0;
        return NULL;
    }

    int capacity = 10;
    int count = 0;
    Scenario* scenarios = malloc(sizeof(Scenario) * capacity);
    if (!scenarios) {
        perror("Error al asignar memoria para escenarios");
        fclose(file);
        *numScenarios = 0;
        return NULL;
    }

    // Leer encabezado
    char** tokens = read_csv_line(file, CSV_DELIMITER);
    free_tokens(tokens);

    // Leer escenario por escenario
    while ((tokens = read_csv_line(file, CSV_DELIMITER)) != NULL) {
        if (count >= capacity) {
            capacity *= 2;
            Scenario* temp = realloc(scenarios, sizeof(Scenario) * capacity);
            if (!temp) {
                perror("Error al redimensionar memoria para escenarios");
                free(scenarios);
                fclose(file);
                *numScenarios = 0;
                return NULL;
            }
            scenarios = temp;
        }

        if (parse_scenario(tokens, &scenarios[count])) {
            count++;
        } else {
            printf("Advertencia: Error al parsear un escenario. Saltando línea.\n");
        }

        free_tokens(tokens);
    }

    fclose(file);
    *numScenarios = count;
    // printf("Cargados %d escenarios desde %s.\n", count, SCENARIOS_CSV_PATH);
    return scenarios;
}

// Comparador seguro para Map de strings
int string_equals(void* a, void* b) {
    return strcmp((const char*)a, (const char*)b) == 0;
}

// Carga los ítems iniciales en un Map: clave=clase, valor=List* de Item*
Map* load_initial_items_map(const char* INITIAL_ITEMS_CSV_PATH) {
    FILE* file = fopen(INITIAL_ITEMS_CSV_PATH, "r");
    if (!file) {
        perror("Error al abrir el archivo de ítems iniciales");
        return NULL;
    }
    Map* clase_a_items = map_create(string_equals);
    // Leer encabezado
    char** tokens = read_csv_line(file, CSV_DELIMITER);
    free_tokens(tokens);
    // Leer ítems iniciales
    while ((tokens = read_csv_line(file, CSV_DELIMITER)) != NULL) {
        Item* item = malloc(sizeof(Item));
        if (parse_item(tokens, item)) {
            List* lista = NULL;
            MapPair* pair = map_search(clase_a_items, item->class);
            if (pair) {
                lista = (List*)pair->value;
            } else {
                lista = list_create();
                map_insert(clase_a_items, strdup(item->class), lista);
            }
            list_pushBack(lista, item);
        } else {
            free(item);
        }
        free_tokens(tokens);
    }
    fclose(file);
    return clase_a_items;
}

/**
 * Carga todos los fragmentos de lore desde el CSV y los agrupa en un Map,
 * donde la key es el tipo (int*) y el value es una List* de strings (char*).
 * El Map debe ser liberado por el llamador.
 */
// Comparador para claves int en Map
int int_key_equal(void* a, void* b) {
    return *((int*)a) == *((int*)b);
}

Map* load_lore_map(const char* lore_csv_path) {
    Map* lore_map = map_create(int_key_equal);
    FILE* file = fopen(lore_csv_path, "r");
    if (!file) return NULL;
    char** tokens;
    // Leer encabezado
    tokens = read_csv_line(file, CSV_DELIMITER);
    free_tokens(tokens);
    while ((tokens = read_csv_line(file, CSV_DELIMITER)) != NULL) {
        if (!tokens[0] || !tokens[1] || !tokens[3]) {
            free_tokens(tokens);
            continue;
        }
        int tipo = atoi(tokens[1]);
        char* historia = tokens[3];
        // Buscar lista para este tipo
        int* key = malloc(sizeof(int));
        *key = tipo;
        MapPair* pair = map_search(lore_map, key);
        List* lista;
        if (pair) {
            lista = (List*)pair->value;
            free(key); // Ya existe la key
        } else {
            lista = list_create();
            map_insert(lore_map, key, lista);
        }
        list_pushBack(lista, strdup(historia));
        free_tokens(tokens);
    }
    fclose(file);
    return lore_map;
}

void free_all_resources(Scenario* scenario_array, Enemy* enemy_array, Item* item_array, int numEnemies, int numItems, int numScenarios, Queue* game_map, Map* lore_map, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo) {
    freeGameData(scenario_array, enemy_array, item_array, numEnemies, numItems, numScenarios);
    queue_clean(game_map);
    if (lore_map) {
        lore_free_all(lore_map, tracker_ambiental, tracker_profundo);
        free(lore_map);
    }
}

