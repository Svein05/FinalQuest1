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


bool shop_buy_item(Player* player, Map* itemMap, int itemId) {
    if (player == NULL || itemMap == NULL) {
        ui_msg_error("Error interno de compra. Por favor, reporta este bug.");
        return false;
    }
    MapPair* pair = map_search(itemMap, &itemId);
    if (!pair || !pair->value) {
        ui_msg_error("Error: El ítem seleccionado no existe en la tienda.");
        return false;
    }
    Item* itemToBuy = (Item*)pair->value;
    if (player->gold < itemToBuy->price) {
        printf("\033[1;31mNo tienes suficiente oro para comprar %s (necesitas %d, tienes %d).\033[0m\n",
               itemToBuy->name, itemToBuy->price, player->gold);
        return false;
    }
    if (player_add_item_to_inventory(player, *itemToBuy)) {
        player->gold -= itemToBuy->price;
        map_remove(itemMap, &itemId);
        return true;
    } else {
        printf("\033[1;31mNo se pudo comprar %s. (Inventario lleno o no fue mejor equipo)\033[0m\n", itemToBuy->name);
        return false;
    }
}

// Cambia la firma para recibir Player* y filtrar armas/armaduras ya equipadas
Map* shop_initialize_random_merchant(Item* item_array, int numItems, int maxDifficulty, Player* player) {
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = true;
    }
    int* indices = malloc(sizeof(int) * numItems);
    int validCount = 0;
    for (int i = 0; i < numItems; i++) {
        if (item_array[i].difficulty <= maxDifficulty) {
            if (item_array[i].type == 1 && player && player->equippedWeapon.id == item_array[i].id) continue;
            if (item_array[i].type == 2 && player && player->equippedArmor.id == item_array[i].id) continue;
            indices[validCount++] = i;
        }
    }
    Map* tempMap = map_create(int_equals);
    // --- SIEMPRE agregar una poción de curación ---
    int healingPotionIdx = -1;
    int boostPotionIdx = -1;
    for (int i = 0; i < numItems; i++) {
        if (item_array[i].type == 3 && item_array[i].heal > 0 && item_array[i].difficulty <= maxDifficulty) {
            if (healingPotionIdx == -1 || item_array[i].difficulty > item_array[healingPotionIdx].difficulty) {
                healingPotionIdx = i;
            }
        }
    }
    if (healingPotionIdx != -1) {
        int* key = malloc(sizeof(int));
        *key = item_array[healingPotionIdx].id;
        map_insert(tempMap, key, &item_array[healingPotionIdx]);
    }
    // --- SIEMPRE agregar una poción de boost (ataque o defensa, la de mayor dificultad posible) ---
    for (int i = 0; i < numItems; i++) {
        if (item_array[i].type == 3 && item_array[i].effectDuration > 0 && item_array[i].difficulty <= maxDifficulty) {
            if (boostPotionIdx == -1 || item_array[i].difficulty > item_array[boostPotionIdx].difficulty) {
                boostPotionIdx = i;
            }
        }
    }
    if (boostPotionIdx != -1 && boostPotionIdx != healingPotionIdx) {
        int* key = malloc(sizeof(int));
        *key = item_array[boostPotionIdx].id;
        map_insert(tempMap, key, &item_array[boostPotionIdx]);
    }
    // --- Agregar ítems aleatorios, sin repetir los ya agregados ---
    bool* selected = calloc(validCount, sizeof(bool));
    int alreadyAdded[2] = {-1, -1};
    int alreadyCount = 0;
    if (healingPotionIdx != -1) alreadyAdded[alreadyCount++] = healingPotionIdx;
    if (boostPotionIdx != -1 && boostPotionIdx != healingPotionIdx) alreadyAdded[alreadyCount++] = boostPotionIdx;
    int merchantItemCount = 0;
    if (validCount > 0) {
        merchantItemCount = (rand() % 3) + 1;
        if (merchantItemCount > validCount) merchantItemCount = validCount;
    }
    for (int count = 0; count < merchantItemCount && validCount > 0;) {
        int r;
        do { r = rand() % validCount; } while (selected[r]);
        int idx = indices[r];
        // No repetir los ya agregados
        bool skip = false;
        for (int j = 0; j < alreadyCount; j++) {
            if (idx == alreadyAdded[j]) { skip = true; break; }
        }
        if (skip) { selected[r] = true; continue; }
        selected[r] = true;
        int* key = malloc(sizeof(int));
        *key = item_array[idx].id;
        map_insert(tempMap, key, &item_array[idx]);
        count++;
    }
    free(selected);
    free(indices);
    return tempMap;
}

void shop_interact(Player* player, Map* itemMap) {
    if (player == NULL || itemMap == NULL) {
        ui_msg_error("Error: Datos de jugador o tienda inválidos.");
        return;
    }

    int choice;
    char input[10];

    ui_shop_welcome(player->gold);

    while (true) {
        ui_shop_items(itemMap);

        // Verificar si hay items disponibles
        MapPair* pair = map_first(itemMap);
        bool hay_items = (pair != NULL);

        if (!hay_items) {
            waitForPress("Presiona ENTER para salir de la tienda...");
            break;
        }

        ui_shop_menu(hay_items);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            ui_msg_error("Error al leer la entrada. Saliendo de la tienda.");
            break;
        }

        choice = atoi(input);

        if (choice == 1) {
            printf("\033[1;36mIngresa el ID del item a comprar: \033[0m");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                ui_msg_error("Error al leer la entrada. Regresando al menu.");
                continue;
            }
            int itemId = atoi(input);
            bool purchased = shop_buy_item(player, itemMap, itemId);
            if (purchased) {
                ui_shop_buy(player->gold);
            }
        } else if (choice == 2) {
            printf("\033[1;35mGracias por tu visita! Vuelve pronto.\033[0m\n");
            break;
        } else {
            ui_msg_error("Opcion invalida. Por favor, elige 1 o 2.");
            printf("\x1b[90m──────────────────────────────────────────────────────────────\x1b[0m\n");
        }
    }
}