#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "shop.h"
#include "data_types.h"
#include "ui.h"
#include "player.h"
#include "data_loader.h"
#include "../tdas/extra.h"
#include "../tdas/map.h"


// Comparador para IDs de ítems (int)
static int int_equals(void* a, void* b) {
    return (*(int*)a) == (*(int*)b);
}


/**
 * Permite al jugador comprar un ítem de la tienda
 * @param player Puntero al jugador que realizará la compra
 * @param itemMap Mapa que contiene los ítems disponibles en la tienda
 * @param itemId ID del ítem que se desea comprar
 * @return true si la compra fue exitosa, false en caso contrario
 */
bool shop_buy_item(Player* player, Map* itemMap, int itemId) {
    // Validar que los parámetros no sean nulos
    if (player == NULL || itemMap == NULL) {
        ui_msg_error("Error interno de compra. Por favor, reporta este bug.");
        return false;
    }
    
    // Buscar el ítem en el mapa de la tienda
    MapPair* pair = map_search(itemMap, &itemId);
    if (!pair || !pair->value) {
        ui_msg_error("Error: El ítem seleccionado no existe en la tienda.");
        return false;
    }
    
    // Obtener referencia al ítem a comprar
    Item* itemToBuy = (Item*)pair->value;
    
    // Verificar si el jugador tiene suficiente oro
    if (player->gold < itemToBuy->price) {
        printf("\033[1;31mNo tienes suficiente oro para comprar %s (necesitas %d, tienes %d).\033[0m\n",
               itemToBuy->name, itemToBuy->price, player->gold);
        return false;
    }
    
    // Intentar agregar el ítem al inventario del jugador
    if (player_add_item_to_inventory(player, *itemToBuy)) {
        // Si se pudo agregar, descontar el oro y remover el ítem de la tienda
        player->gold -= itemToBuy->price;
        map_remove(itemMap, &itemId);
        return true;
    } else {
        // Si no se pudo agregar (inventario lleno o equipo no es mejor)
        printf("\033[1;31mNo se pudo comprar %s. (Inventario lleno o no fue mejor equipo)\033[0m\n", itemToBuy->name);
        return false;
    }
}

Map* shop_initialize_random_merchant(Item* item_array, int numItems, int maxDifficulty, Player* player) {
    // Inicializar semilla para números aleatorios (solo una vez)
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = true;
    }
    
    // Crear array de índices válidos para ítems que cumplan los criterios
    int* indices = malloc(sizeof(int) * numItems);
    int validCount = 0;
    
    // Filtrar ítems por dificultad y excluir equipo ya equipado por el jugador
    for (int i = 0; i < numItems; i++) {
        if (item_array[i].difficulty <= maxDifficulty) {
            // Saltar armas ya equipadas (tipo 1)
            if (item_array[i].type == 1 && player && player->equippedWeapon.id == item_array[i].id) continue;
            // Saltar armaduras ya equipadas (tipo 2)
            if (item_array[i].type == 2 && player && player->equippedArmor.id == item_array[i].id) continue;
            indices[validCount++] = i;
        }
    }
    
    // Crear el mapa para almacenar los ítems de la tienda
    Map* tempMap = map_create(int_equals);
    
    // Buscar la mejor poción de curación disponible
    int healingPotionIdx = -1;
    int boostPotionIdx = -1;
    for (int i = 0; i < numItems; i++) {
        // Pociones de curación (tipo 3 con heal > 0)
        if (item_array[i].type == 3 && item_array[i].heal > 0 && item_array[i].difficulty <= maxDifficulty) {
            if (healingPotionIdx == -1 || item_array[i].difficulty > item_array[healingPotionIdx].difficulty) {
                healingPotionIdx = i;
            }
        }
    }
    
    // Agregar la poción de curación al mapa si se encontró una
    if (healingPotionIdx != -1) {
        int* key = malloc(sizeof(int));
        *key = item_array[healingPotionIdx].id;
        map_insert(tempMap, key, &item_array[healingPotionIdx]);
    }

    // Buscar la mejor poción de boost (ataque/defensa) disponible
    for (int i = 0; i < numItems; i++) {
        // Pociones de boost (tipo 3 con effectDuration > 0)
        if (item_array[i].type == 3 && item_array[i].effectDuration > 0 && item_array[i].difficulty <= maxDifficulty) {
            if (boostPotionIdx == -1 || item_array[i].difficulty > item_array[boostPotionIdx].difficulty) {
                boostPotionIdx = i;
            }
        }
    }
    
    // Agregar la poción de boost al mapa si es diferente a la de curación
    if (boostPotionIdx != -1 && boostPotionIdx != healingPotionIdx) {
        int* key = malloc(sizeof(int));
        *key = item_array[boostPotionIdx].id;
        map_insert(tempMap, key, &item_array[boostPotionIdx]);
    }

    // Preparar estructuras para agregar ítems aleatorios adicionales
    bool* selected = calloc(validCount, sizeof(bool)); // Array para marcar ítems ya seleccionados
    int alreadyAdded[2] = {-1, -1}; // Índices de pociones ya agregadas
    int alreadyCount = 0;
    
    // Registrar las pociones ya agregadas para evitar duplicados
    if (healingPotionIdx != -1) alreadyAdded[alreadyCount++] = healingPotionIdx;
    if (boostPotionIdx != -1 && boostPotionIdx != healingPotionIdx) alreadyAdded[alreadyCount++] = boostPotionIdx;
    
    // Determinar cuántos ítems aleatorios agregar (1-3)
    int merchantItemCount = 0;
    if (validCount > 0) {
        merchantItemCount = (rand() % 3) + 1;
        if (merchantItemCount > validCount) merchantItemCount = validCount;
    }
    
    // Agregar ítems aleatorios sin repetir los ya agregados
    for (int count = 0; count < merchantItemCount && validCount > 0;) {
        int r;
        // Seleccionar un índice aleatorio no usado
        do { r = rand() % validCount; } while (selected[r]);
        int idx = indices[r];
        
        // Verificar si el ítem ya fue agregado como poción obligatoria
        bool skip = false;
        for (int j = 0; j < alreadyCount; j++) {
            if (idx == alreadyAdded[j]) { skip = true; break; }
        }
        
        // Si ya fue agregado, marcar como seleccionado y continuar
        if (skip) { selected[r] = true; continue; }
        
        // Marcar como seleccionado y agregar al mapa
        selected[r] = true;
        int* key = malloc(sizeof(int));
        *key = item_array[idx].id;
        map_insert(tempMap, key, &item_array[idx]);
        count++;
    }
    
    // Liberar memoria temporal
    free(selected);
    free(indices);
    return tempMap;
}

void shop_interact(Player* player, Map* itemMap) {
    // Validar parámetros de entrada
    if (player == NULL || itemMap == NULL) {
        ui_msg_error("Error: Datos de jugador o tienda inválidos.");
        return;
    }

    // Variables para manejar la entrada del usuario
    int choice;
    char input[10];

    // Mostrar mensaje de bienvenida con el oro actual del jugador
    ui_shop_welcome(player->gold);

    // Bucle principal de interacción con la tienda
    while (true) {
        // Mostrar todos los ítems disponibles en la tienda
        ui_shop_items(itemMap);

        // Verificar si hay ítems disponibles en la tienda
        MapPair* pair = map_first(itemMap);
        bool hay_items = (pair != NULL);

        // Si no hay ítems, salir de la tienda automáticamente
        if (!hay_items) {
            waitForPress("Presiona ENTER para salir de la tienda...");
            break;
        }

        // Mostrar el menú de opciones
        ui_shop_menu(hay_items);

        // Leer la entrada del usuario
        if (fgets(input, sizeof(input), stdin) == NULL) {
            ui_msg_error("Error al leer la entrada. Saliendo de la tienda.");
            break;
        }

        // Convertir la entrada a número
        choice = atoi(input);

        // Procesar la opción seleccionada
        if (choice == 1) {
            // Opción 1: Comprar un ítem
            printf("\033[1;36mIngresa el ID del item a comprar: \033[0m");
            
            // Leer el ID del ítem a comprar
            if (fgets(input, sizeof(input), stdin) == NULL) {
                ui_msg_error("Error al leer la entrada. Regresando al menu.");
                continue;
            }
            
            // Convertir ID a número e intentar comprar
            int itemId = atoi(input);
            bool purchased = shop_buy_item(player, itemMap, itemId);
            
            // Si la compra fue exitosa, mostrar mensaje de confirmación
            if (purchased) {
                ui_shop_buy(player->gold);
            }
        } else if (choice == 2) {
            // Opción 2: Salir de la tienda
            printf("\033[1;35mGracias por tu visita! Vuelve pronto.\033[0m\n");
            break;
        } else {
            // Opción inválida
            ui_msg_error("Opcion invalida. Por favor, elige 1 o 2.");
            printf("\x1b[90m──────────────────────────────────────────────────────────────\x1b[0m\n");
        }
    }
}