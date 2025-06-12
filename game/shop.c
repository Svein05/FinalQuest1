#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "shop.h"
#include "data_types.h"
#include "player.h"
#include "tdas/extra.h"

/**
 * @brief Parsea un arreglo de tokens de cadena en una estructura Item.
 * Asume el orden de las columnas del CSV:
 * ID,Nombre,Tipo,Rareza,Damage,Defense,Heal,Costo,Dificultad,EffectDuration
 * @param tokens Arreglo de cadenas (char**) a parsear, obtenido de leer_linea_csv.
 * @param item Puntero a la estructura Item donde se guardarán los datos.
 * @return true si el parseo fue exitoso, false en caso de error.
 *
 * NOTA: Esta función asume que los tokens son válidos y que el arreglo contiene
 * suficientes elementos hasta donde se especifica en el CSV.
 */
bool parse_item_from_tokens(char** tokens, Item* item) {
    if (tokens == NULL || item == NULL) {
        // No hay validación de numTokens aquí, porque leer_linea_csv no lo devuelve.
        // Se asume que el arreglo 'tokens' es suficientemente grande o que los índices
        // accederán a valores válidos si el CSV está bien formado.
        return false;
    }

    // Usamos strncpy para copiar las cadenas de forma segura a los arreglos fijos del struct Item.
    // atoi para convertir cadenas a enteros.
    item->id = atoi(tokens[0]);
    strncpy(item->name, tokens[1], sizeof(item->name) - 1);
    item->name[sizeof(item->name) - 1] = '\0'; // Asegurar terminación nula
    item->type = atoi(tokens[2]);
    strncpy(item->rarity, tokens[3], sizeof(item->rarity) - 1);
    item->rarity[sizeof(item->rarity) - 1] = '\0'; // Asegurar terminación nula

    item->damage = atoi(tokens[4]);
    item->defense = atoi(tokens[5]);
    item->heal = atoi(tokens[6]);
    item->cost = atoi(tokens[7]);
    item->difficulty = atoi(tokens[8]);
    item->effectDuration = atoi(tokens[9]);

    return true;
}

// --- IMPLEMENTACIÓN DE FUNCIONES DEL MÓDULO SHOP ---

Shop* shop_initialize_start_shop(const char* itemsCsvPath) {
    FILE* file = fopen(itemsCsvPath, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo de items para la tienda inicial");
        return NULL;
    }

    Shop* startShop = (Shop*) malloc(sizeof(Shop));
    if (startShop == NULL) {
        perror("Error al asignar memoria para la tienda inicial");
        fclose(file);
        return NULL;
    }
    startShop->items = NULL;
    startShop->itemCount = 0;

    int capacity = 10; // Capacidad inicial para el arreglo de items
    startShop->items = (Item*) malloc(sizeof(Item) * capacity);
    if (startShop->items == NULL) {
        perror("Error al asignar memoria inicial para los items de la tienda");
        free(startShop);
        fclose(file);
        return NULL;
    }

    char** tokens = NULL;
    char separator = ','; // Definimos el separador de tu CSV

    // Saltar la línea de encabezado del CSV
    tokens = leer_linea_csv(file, separator); // Se lee la primera línea (encabezado)

    // Leer ítems del CSV
    while ((tokens = leer_linea_csv(file, separator)) != NULL) {
        // Redimensionar si es necesario
        if (startShop->itemCount >= capacity) {
            capacity *= 2;
            Item* temp_items = (Item*) realloc(startShop->items, sizeof(Item) * capacity);
            if (temp_items == NULL) {
                perror("Error al redimensionar memoria para items de la tienda");
                shop_free(startShop);
                fclose(file);
                return NULL;
            }
            startShop->items = temp_items;
        }

        // Parsear el ítem y añadirlo
        if (parse_item_from_tokens(tokens, &startShop->items[startShop->itemCount])) {
            startShop->itemCount++;
        } else {
            // Esto podría ocurrir si una línea no tiene suficientes campos o hay un error de formato
            printf("Advertencia: Error al parsear un item en la tienda inicial. Saltando linea.\n");
        }
    }

    fclose(file);
    printf("Tienda inicial cargada con %d items desde %s.\n", startShop->itemCount, itemsCsvPath);
    return startShop;
}

Shop* shop_initialize_random_merchant(const char* itemsCsvPath, int minDifficulty, int maxDifficulty) {
    // Inicializar el generador de números aleatorios si no se ha hecho
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = true;
    }

    FILE* file = fopen(itemsCsvPath, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo de items para el mercader aleatorio");
        return NULL;
    }

    // Nota: suitableItems contendrá copias de los Item structs,
    // no punteros a los tokens estáticos.
    Item* suitableItems = NULL;
    int suitableItemCount = 0;
    int capacity = 10;
    suitableItems = (Item*) malloc(sizeof(Item) * capacity);
    if (suitableItems == NULL) {
        perror("Error al asignar memoria inicial para ítems adecuados");
        fclose(file);
        return NULL;
    }

    char** tokens = NULL;
    char separator = ',';

    // Saltar la línea de encabezado
    tokens = leer_linea_csv(file, separator);

    while ((tokens = leer_linea_csv(file, separator)) != NULL) {
        Item tempItem; // Creamos una instancia temporal del Item
        if (parse_item_from_tokens(tokens, &tempItem)) {
            // Filtrar por dificultad
            if (tempItem.difficulty >= minDifficulty && tempItem.difficulty <= maxDifficulty) {
                if (suitableItemCount >= capacity) {
                    capacity *= 2;
                    Item* temp_realloc = (Item*) realloc(suitableItems, sizeof(Item) * capacity);
                    if (temp_realloc == NULL) {
                        perror("Error al redimensionar memoria para items adecuados");
                        free(suitableItems);
                        fclose(file);
                        return NULL;
                    }
                    suitableItems = temp_realloc;
                }
                suitableItems[suitableItemCount++] = tempItem; // Copiar el ítem COMPLETO
            }
        }
        // No se llama free_tokens(tokens, numTokens)
    }
    fclose(file);

    // Ahora, seleccionar un número aleatorio de ítems de 'suitableItems' para el mercader
    int merchantItemCount = 0;
    if (suitableItemCount > 0) {
        merchantItemCount = (rand() % 3) + 1; // El mercader vende entre 1 y 3 ítems
        if (merchantItemCount > suitableItemCount) {
            merchantItemCount = suitableItemCount;
        }
    }

    Shop* randomMerchant = (Shop*) malloc(sizeof(Shop));
    if (randomMerchant == NULL) {
        perror("Error al asignar memoria para el mercader");
        free(suitableItems);
        return NULL;
    }
    randomMerchant->itemCount = merchantItemCount;
    randomMerchant->items = (Item*) malloc(sizeof(Item) * randomMerchant->itemCount);
    if (randomMerchant->items == NULL) {
        perror("Error al asignar memoria para los items del mercader");
        free(randomMerchant);
        free(suitableItems);
        return NULL;
    }

    if (suitableItemCount > 0) {
        bool* selectedIndices = (bool*) calloc(suitableItemCount, sizeof(bool));
        if (selectedIndices == NULL) {
             perror("Error al asignar memoria para selectedIndices");
             shop_free(randomMerchant);
             free(suitableItems);
             return NULL;
        }

        for (int i = 0; i < merchantItemCount; i++) {
            int randomIndex;
            do {
                randomIndex = rand() % suitableItemCount;
            } while (selectedIndices[randomIndex]);

            randomMerchant->items[i] = suitableItems[randomIndex]; // Copiar el ítem
            selectedIndices[randomIndex] = true;
        }
        free(selectedIndices);
    }

    free(suitableItems); // Liberar el arreglo temporal de ítems adecuados

    printf("Un mercader misterioso ha aparecido con %d items de dificultad %d-%d!\n",
           randomMerchant->itemCount, minDifficulty, maxDifficulty);
    return randomMerchant;
}

void shop_interact(Player* player, Shop* currentShop) {
    if (player == NULL || currentShop == NULL) {
        printf("Error: Datos de jugador o tienda inválidos.\n");
        return;
    }

    int choice;
    char input[10];

    printf("\n--- Bienvenido a la tienda! ---\n");
    printf("Tienes %d oro.\n", player->gold);

    while (true) {
        printf("\nItems disponibles:\n");
        if (currentShop->itemCount == 0) {
            printf("  (No hay ítems en venta en este momento.)\n");
        } else {
            for (int i = 0; i < currentShop->itemCount; i++) {
                printf("  %d. %s (%s) - Costo: %d oro. ",
                       i + 1, currentShop->items[i].name, currentShop->items[i].rarity, currentShop->items[i].cost);

                if (currentShop->items[i].type == 1) { // Arma
                    printf("Daño: %d.\n", currentShop->items[i].damage);
                } else if (currentShop->items[i].type == 2) { // Armadura
                    printf("Defensa: %d.\n", currentShop->items[i].defense);
                } else if (currentShop->items[i].type == 3) { // Poción
                    printf("Cura: %d HP. ", currentShop->items[i].heal);
                    if (currentShop->items[i].damage > 0 || currentShop->items[i].defense > 0) {
                        printf("Boost: ");
                        if (currentShop->items[i].damage > 0) printf("+%d Atk ", currentShop->items[i].damage);
                        if (currentShop->items[i].defense > 0) printf("+%d Def ", currentShop->items[i].defense);
                        printf("por %d turnos.\n", currentShop->items[i].effectDuration);
                    } else {
                        printf("\n"); // Solo cura
                    }
                } else {
                    printf("\n"); // Tipo desconocido
                }
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
            if (currentShop->itemCount == 0) {
                printf("No hay nada que comprar aqui!\n");
                continue;
            }
            printf("Ingresa el numero del item a comprar (1-%d): ", currentShop->itemCount);
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("Error al leer la entrada. Regresando al menu.\n");
                continue;
            }
            int itemChoice = atoi(input);

            if (itemChoice >= 1 && itemChoice <= currentShop->itemCount) {
                bool purchased = shop_buy_item(player, currentShop, itemChoice - 1);
                if (purchased) {
                    printf("¡Compra exitosa! Tienes %d oro restante.\n", player->gold);
                }
            } else {
                printf("Numero de item invalido.\n");
            }
        } else if (choice == 2) {
            printf("Gracias por tu visita! Vuelve pronto.\n");
            break;
        } else {
            printf("Opcion invalida. Por favor, elige 1 o 2.\n");
        }
    }
}

bool shop_buy_item(Player* player, Shop* currentShop, int itemIndex) {
    if (player == NULL || currentShop == NULL || itemIndex < 0 || itemIndex >= currentShop->itemCount) {
        printf("Error interno de compra. Por favor, reporta este bug.\n");
        return false;
    }

    Item itemToBuy = currentShop->items[itemIndex];

    if (player->gold < itemToBuy.cost) {
        printf("No tienes suficiente oro para comprar %s (necesitas %d, tienes %d).\n",
               itemToBuy.name, itemToBuy.cost, player->gold);
        return false;
    }

    if (player_add_item_to_inventory(player, itemToBuy)) {
        player->gold -= itemToBuy.cost;

        if (itemToBuy.type == 1) { // Arma
            player_equip_weapon(player, itemToBuy);
            printf("Has equipado %s (+%d Atk).\n", itemToBuy.name, itemToBuy.damage);
        } else if (itemToBuy.type == 2) { // Armadura
            player_equip_armor(player, itemToBuy);
            printf("Has equipado %s (+%d Def).\n", itemToBuy.name, itemToBuy.defense);
        } else if (itemToBuy.type == 3) { // Poción
            printf("Has comprado %s y se ha añadido a tu inventario.\n", itemToBuy.name);
        }
        return true;
    } else {
        printf("Tu inventario esta lleno! No puedes comprar %s.\n", itemToBuy.name);
        return false;
    }
}

void shop_free(Shop* shopToFree) {
    if (shopToFree == NULL) {
        return;
    }
    if (shopToFree->items != NULL) {
        free(shopToFree->items);
        shopToFree->items = NULL;
    }
    free(shopToFree);
    printf("Memoria de la tienda liberada.\n");
}