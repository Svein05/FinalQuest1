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
 * 
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
    }
}

void freeScenarioMap(Scenario* scenarios) {
    if (scenarios != NULL) {
        free(scenarios);
    }
}

void freeItems(Item* items) {
    if (items != NULL) {
        free(items);
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
            return false;
        }
    }

    // Parsear ID
    char* endptr;
    node->id = strtol(tokens[0], &endptr, 10);
    if (*endptr != '\0' || node->id <= 0) {
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
        return false;
    }

    return true;
}

// --- FUNCIONES DE CARGA ---
Enemy* load_enemies(const char* ENEMIES_CSV_PATH, int* numEnemies) {
    // Abrir el archivo CSV de enemigos del juego
    FILE* file = fopen(ENEMIES_CSV_PATH, "r");
    if (!file) {
        perror("Error al abrir CSV");
        *numEnemies = 0;
        return NULL;
    }
    
    // Inicializar capacidad y contador para array dinámico de enemigos
    int capacity = 10;
    int count = 0;
    Enemy* enemies = malloc(sizeof(Enemy) * capacity);
    if (!enemies) {
        perror("Error al asignar memoria para enemigos");
        fclose(file);
        *numEnemies = 0;
        return NULL;
    }
    
    // Leer y descartar la línea de encabezado del CSV
    char** tokens = read_csv_line(file, CSV_DELIMITER);
    free_tokens(tokens);

    // Procesar cada línea de enemigos del archivo
    while ((tokens = read_csv_line(file, CSV_DELIMITER)) != NULL) {
        // Verificar si necesitamos expandir el array de enemigos
        if (count >= capacity) {
            capacity *= 2;  // Duplicar la capacidad del array
            Enemy* temp = realloc(enemies, sizeof(Enemy) * capacity);
            if (!temp) {
                perror("Error al redimensionar memoria para enemigos");
                free(enemies);
                fclose(file);
                *numEnemies = 0;
                return NULL;
            }
            enemies = temp;  // Actualizar el puntero al array expandido
        }

        // Crear enemigo temporal para el parseo
        Enemy parsedEnemy;
        
        // Intentar parsear el enemigo actual desde los tokens
        if (parse_enemy(tokens, &parsedEnemy)) {
            enemies[count++] = parsedEnemy;  // Copiar el enemigo al array y incrementar contador
        } else {
            printf("Advertencia: Error al parsear un enemigo. Saltando línea.\n");
        }

        // Liberar los tokens de esta línea
        free_tokens(tokens);
    }
    
    fclose(file);
    *numEnemies = count;  // Retornar el número total de enemigos cargados
    return enemies;
}


Item* load_items(const char* ITEMS_CSV_PATH, int* numItems) {
    // Abrir el archivo CSV de ítems del juego
    FILE* file = fopen(ITEMS_CSV_PATH, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo de ítems");
        *numItems = 0;
        return NULL;
    }

    // Inicializar capacidad y contador para array dinámico de ítems
    int capacity = 10;
    int count = 0;
    Item* items = malloc(sizeof(Item) * capacity);
    if (items == NULL) {
        perror("Error al asignar memoria inicial para ítems");
        fclose(file);
        *numItems = 0;
        return NULL;
    }

    // Leer y descartar la línea de encabezado del CSV
    char** tokens = read_csv_line(file, CSV_DELIMITER);
    free_tokens(tokens);

    // Procesar cada línea de ítems del archivo
    while ((tokens = read_csv_line(file, CSV_DELIMITER)) != NULL) {
        // Verificar si necesitamos expandir el array de ítems
        if (count >= capacity) {
            capacity *= 2;  // Duplicar la capacidad del array
            Item* temp = realloc(items, sizeof(Item) * capacity);
            if (temp == NULL) {
                perror("Error al redimensionar memoria para ítems");
                freeItems(items);
                fclose(file);
                *numItems = 0;
                return NULL;
            }
            items = temp;  // Actualizar el puntero al array expandido
        }
        
        // Intentar parsear el ítem actual usando la función básica
        if (parse_item_basic(tokens, &items[count])) {
            count++;  // Incrementar contador solo si el parseo fue exitoso
        } else {
            printf("Advertencia: Error al parsear un ítem. Saltando línea.\n");
        }
        
        // Liberar los tokens de esta línea
        free_tokens(tokens);
    }

    fclose(file);
    *numItems = count;  // Retornar el número total de ítems cargados
    return items;
}

Scenario* load_scenarios(const char* SCENARIOS_CSV_PATH, int* numScenarios) {
    // Abrir el archivo CSV de escenarios
    FILE* file = fopen(SCENARIOS_CSV_PATH, "r");
    if (!file) {
        perror("Error al abrir el archivo de escenarios");
        *numScenarios = 0;
        return NULL;
    }

    // Inicializar capacidad y contador para array dinámico
    int capacity = 10;
    int count = 0;
    Scenario* scenarios = malloc(sizeof(Scenario) * capacity);
    if (!scenarios) {
        perror("Error al asignar memoria para escenarios");
        fclose(file);
        *numScenarios = 0;
        return NULL;
    }

    // Leer y descartar la línea de encabezado del CSV
    char** tokens = read_csv_line(file, CSV_DELIMITER);
    free_tokens(tokens);

    // Procesar cada línea de escenarios del archivo
    while ((tokens = read_csv_line(file, CSV_DELIMITER)) != NULL) {
        // Verificar si necesitamos expandir el array
        if (count >= capacity) {
            capacity *= 2;  // Duplicar la capacidad
            Scenario* temp = realloc(scenarios, sizeof(Scenario) * capacity);
            if (!temp) {
                perror("Error al redimensionar memoria para escenarios");
                free(scenarios);
                fclose(file);
                *numScenarios = 0;
                return NULL;
            }
            scenarios = temp;  // Actualizar el puntero al array expandido
        }

        // Intentar parsear el escenario actual
        if (parse_scenario(tokens, &scenarios[count])) {
            count++;  // Incrementar contador solo si el parseo fue exitoso
        } else {
            printf("Advertencia: Error al parsear un escenario. Saltando línea.\n");
        }

        // Liberar los tokens de esta línea
        free_tokens(tokens);
    }

    fclose(file);
    *numScenarios = count;  // Retornar el número total de escenarios cargados
    return scenarios;
}

// Comparador seguro para Map de strings
int string_equals(void* a, void* b) {
    return strcmp((const char*)a, (const char*)b) == 0;
}

Map* load_initial_items_map(const char* INITIAL_ITEMS_CSV_PATH) {
    // Abrir el archivo CSV de ítems iniciales
    FILE* file = fopen(INITIAL_ITEMS_CSV_PATH, "r");
    if (!file) {
        perror("Error al abrir el archivo de ítems iniciales");
        return NULL;
    }
    
    // Crear mapa que relaciona clases de jugador con listas de ítems
    Map* clase_a_items = map_create(string_equals);

    // Leer y descartar la línea de encabezado del CSV
    char** tokens = read_csv_line(file, CSV_DELIMITER);
    free_tokens(tokens);

    // Procesar cada línea de ítems iniciales
    while ((tokens = read_csv_line(file, CSV_DELIMITER)) != NULL) {
        // Asignar memoria para un nuevo ítem
        Item* item = malloc(sizeof(Item));
        
        // Intentar parsear el ítem desde los tokens del CSV
        if (parse_item(tokens, item)) {
            List* lista = NULL;
            
            // Buscar si ya existe una lista para esta clase de jugador
            MapPair* pair = map_search(clase_a_items, item->class);
            
            if (pair) {
                // Ya existe una lista para esta clase, usarla
                lista = (List*)pair->value;
            } else {
                // Crear nueva lista para esta clase y añadirla al mapa
                lista = list_create();
                map_insert(clase_a_items, strdup(item->class), lista);
            }
            
            // Agregar el ítem a la lista correspondiente de su clase
            list_pushBack(lista, item);
        } else {
            // Error al parsear el ítem, liberar memoria y continuar
            free(item);
        }
        
        // Liberar los tokens de esta línea
        free_tokens(tokens);
    }
    
    fclose(file);
    return clase_a_items;
}

// Comparador para claves int en Map
int int_key_equal(void* a, void* b) {
    return *((int*)a) == *((int*)b);
}

Map* load_lore_map(const char* lore_csv_path) {
    // Crear mapa con comparador de claves enteras para organizar lore por tipo
    Map* lore_map = map_create(int_key_equal);
    FILE* file = fopen(lore_csv_path, "r");
    if (!file) return NULL;
    
    char** tokens;
    
    // Leer y descartar la línea de encabezado del CSV
    tokens = read_csv_line(file, CSV_DELIMITER);
    free_tokens(tokens);
    
    // Procesar cada línea del archivo CSV
    while ((tokens = read_csv_line(file, CSV_DELIMITER)) != NULL) {
        // Validar que los campos obligatorios no estén vacíos
        if (!tokens[0] || !tokens[1] || !tokens[3]) {
            free_tokens(tokens);
            continue;  // Saltar líneas con datos incompletos
        }
        
        // Extraer el tipo de lore y el texto de la historia
        int tipo = atoi(tokens[1]);
        char* historia = tokens[3];
        
        // Crear clave para buscar en el mapa
        int* key = malloc(sizeof(int));
        *key = tipo;
        
        // Buscar si ya existe una lista para este tipo de lore
        MapPair* pair = map_search(lore_map, key);
        List* lista;
        
        if (pair) {
            // Ya existe una lista para este tipo, usarla
            lista = (List*)pair->value;
            free(key); // Liberar la clave ya que no se necesita
        } else {
            // Crear nueva lista para este tipo de lore
            lista = list_create();
            map_insert(lore_map, key, lista);
        }
        
        // Agregar la historia a la lista correspondiente
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

