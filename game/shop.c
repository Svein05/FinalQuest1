#include <stdio.h>    // Para printf, fopen, fclose, perror
#include <stdlib.h>   // Para malloc, free, realloc, atoi
#include <string.h>   // Para strncpy, strlen, strcspn
#include <stdbool.h>
#include <time.h>

#include "shop.h"
#include "data_types.h"
#include "player.h" // Incluido para las funciones de jugador
#include "../tdas/extra.h" // Asegúrate de que esta ruta es correcta para tu extra.h y extra.c
#include "data_loader.h"
#include "../tdas/map.h"

// Comparador para IDs de ítems (int)
static int int_equals(void* a, void* b) {
    return (*(int*)a) == (*(int*)b);
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
    int merchantItemCount = 0;
    if (validCount > 0) {
        merchantItemCount = (rand() % 3) + 1;
        if (merchantItemCount > validCount) merchantItemCount = validCount;
    }
    Map* tempMap = map_create(int_equals);
    bool* selected = calloc(validCount, sizeof(bool));
    for (int count = 0; count < merchantItemCount && validCount > 0;) {
        int r;
        do { r = rand() % validCount; } while (selected[r]);
        selected[r] = true;
        int idx = indices[r];
        int* key = malloc(sizeof(int));
        *key = item_array[idx].id;
        map_insert(tempMap, key, &item_array[idx]);
        count++;
    }
    free(selected);
    free(indices);
    printf("Un mercader misterioso ha aparecido con %d items de dificultad hasta %d!\n",
           merchantItemCount, maxDifficulty);
    return tempMap;
}

void shop_interact(Player* player, Map* itemMap) {
    if (player == NULL || itemMap == NULL) {
        printf("Error: Datos de jugador o tienda inválidos.\n");
        return;
    }
    int choice;
    char input[10];
    printf("\n--- Bienvenido a la tienda! ---\n");
    printf("Tienes %d oro.\n", player->gold);
    while (true) {
        printf("\nItems disponibles:\n");
        MapPair* pair = map_first(itemMap);
        if (!pair) {
            printf("   (No hay ítems en venta en este momento.)\n");
        } else {
            while (pair) {
                Item* item = (Item*)pair->value;
                int id = *(int*)pair->key;
                printf("   [%d] %s (%s) - Costo: %d oro. ",
                       id, item->name, item->rarity, item->price);
                if (item->type == 1) {
                    printf("Daño: %d.\n", item->damage);
                } else if (item->type == 2) {
                    printf("Defensa: %d.\n", item->defense);
                } else if (item->type == 3) {
                    // Consumible: mostrar curación y boosts
                    if (item->heal > 0) printf("Cura: %d HP. ", item->heal);
                    if (item->damage > 0) printf("Daño Boost: +%d Atk ", item->damage);
                    if (item->defense > 0) printf("Defensa Boost: +%d Def ", item->defense);
                    if (item->damage > 0 || item->defense > 0) printf("por %d turnos. ", item->effectDuration);
                    printf("\n");
                } else {
                    printf(")\n");
                }
                pair = map_next(itemMap);
            }
        }
        printf("\nQue deseas hacer?\n");
        printf("1. Comprar Item\n");
        printf("2. Salir de la tienda\n");
        printf("Tu eleccion: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error al leer la entrada. Saliendo de la tienda.\n");
            break;
        }
        choice = atoi(input);
        if (choice == 1) {
            printf("Ingresa el ID del item a comprar: ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("Error al leer la entrada. Regresando al menu.\n");
                continue;
            }
            int itemId = atoi(input);
            bool purchased = shop_buy_item(player, itemMap, itemId);
            if (purchased) {
                printf("¡Compra exitosa! Tienes %d oro restante.\n", player->gold);
            }
        } else if (choice == 2) {
            printf("Gracias por tu visita! Vuelve pronto.\n");
            break;
        } else {
            printf("Opcion invalida. Por favor, elige 1 o 2.\n");
        }
    }
}

bool shop_buy_item(Player* player, Map* itemMap, int itemId) {
    if (player == NULL || itemMap == NULL) {
        printf("Error interno de compra. Por favor, reporta este bug.\n");
        return false;
    }
    MapPair* pair = map_search(itemMap, &itemId);
    if (!pair || !pair->value) {
        printf("Error: El ítem seleccionado no existe en la tienda.\n");
        return false;
    }
    Item* itemToBuy = (Item*)pair->value;
    if (player->gold < itemToBuy->price) {
        printf("No tienes suficiente oro para comprar %s (necesitas %d, tienes %d).\n",
               itemToBuy->name, itemToBuy->price, player->gold);
        return false;
    }
    if (player_add_item_to_inventory(player, *itemToBuy)) {
        player->gold -= itemToBuy->price;
        // Eliminar el ítem del Map tras la compra
        map_remove(itemMap, &itemId);
        printf("Has comprado %s y se ha gestionado tu inventario.\n", itemToBuy->name);
        return true;
    } else {
        printf("No se pudo comprar %s. (Inventario lleno o no fue mejor equipo)\n", itemToBuy->name);
        return false;
    }
}
