#include <stdio.h>    // Para printf, fopen, fclose, perror
#include <stdlib.h>   // Para malloc, free, realloc, atoi
#include <string.h>   // Para strncpy, strlen, strcspn
#include <stdbool.h>
#include <time.h>

#include "shop.h"
#include "data_types.h"
#include "player.h" // Incluido para las funciones de jugador
#include "../tdas/extra.h" // Asegúrate de que esta ruta es correcta para tu extra.h y extra.c

// NO NECESITAMOS free_tokens AQUÍ SI leer_linea_csv NO USA strdup
// y su buffer es estático o gestiona la memoria de otra forma interna.
// Si leer_linea_csv usa strdup, SÍ NECESITARÍAMOS free_tokens.
// Basado en la simplificación que discutimos, asumiremos que leer_linea_csv
// NO usa strdup y la memoria devuelta no necesita ser liberada por el llamador.

/**
 * @brief Parsea un arreglo de tokens de cadena en una estructura Item.
 * Asume el orden de las columnas del CSV:
 * ID,Nombre,Tipo,Rareza,Damage,Defense,Heal,Costo,Dificultad,EffectDuration
 * @param tokens Arreglo de cadenas (char**) a parsear.
 * @param item Puntero a la estructura Item donde se guardarán los datos.
 * @return true si el parseo fue exitoso, false en caso de error.
 */
bool parse_item_from_tokens(char** tokens, Item* item) {
    if (tokens == NULL || item == NULL) return false;

    item->id = atoi(tokens[0]);
    strncpy(item->name, tokens[1], sizeof(item->name) - 1);
    item->name[sizeof(item->name) - 1] = '\0';

    item->type = atoi(tokens[2]);
    strncpy(item->rarity, tokens[3], sizeof(item->rarity) - 1);
    item->rarity[sizeof(item->rarity) - 1] = '\0';

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
    tokens = leer_linea_csv(file, separator); 

    // Leer ítems del CSV
    while ((tokens = leer_linea_csv(file, separator)) != NULL) {
        Item tempItem;
        if (parse_item_from_tokens(tokens, &tempItem)) {
            // Se asume que TODOS los ítems en 'initial_items.csv' son los que queremos
            // para la tienda inicial y ya tienen la dificultad 0 asignada en el CSV.
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
            startShop->items[startShop->itemCount] = tempItem; // Copia el ítem a la tienda
            startShop->itemCount++;
        } else {
            printf("Advertencia: Error al parsear un item en la tienda inicial. Saltando linea.\n");
        }
    }

    fclose(file);
    // Mensaje actualizado para reflejar que se cargan todos los items del CSV inicial
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

    // suitableItems contendrá copias de los Item structs, incluyendo sus cadenas fijas.
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
            // Filtrar por dificultad (aquí se mantiene el filtro por rango)
            if (tempItem.difficulty >= minDifficulty && tempItem.difficulty <= maxDifficulty) {
                if (suitableItemCount >= capacity) {
                    capacity *= 2;
                    Item* temp_realloc = (Item*) realloc(suitableItems, sizeof(Item) * capacity);
                    if (temp_realloc == NULL) {
                        perror("Error al redimensionar memoria para items adecuados");
                        free(suitableItems); // Libera el arreglo de Items (sus cadenas fijas se liberan con la Item)
                        fclose(file);
                        return NULL;
                    }
                    suitableItems = temp_realloc;
                }
                suitableItems[suitableItemCount++] = tempItem; // Copiar el ítem COMPLETO (cadenas fijas incluidas)
            }
        }
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
             free(suitableItems); // Libera el arreglo de Items (cadenas fijas incluidas)
             shop_free(randomMerchant); // Libera la tienda y sus items
             return NULL;
        }

        for (int i = 0; i < merchantItemCount; i++) {
            int randomIndex;
            do {
                randomIndex = rand() % suitableItemCount;
            } while (selectedIndices[randomIndex]);

            randomMerchant->items[i] = suitableItems[randomIndex]; // Copiar el ítem COMPLETO
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
            printf("   (No hay ítems en venta en este momento.)\n");
        } else {
            for (int i = 0; i < currentShop->itemCount; i++) {
                printf("   %d. %s (%s) - Costo: %d oro. ",
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
                    printf(")\n"); // Tipo desconocido o sin propiedades específicas
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

    // player_add_item_to_inventory ahora maneja el equipamiento automático si es mejor
    // Si player_add_item_to_inventory devuelve true, el ítem fue añadido o equipado con éxito.
    if (player_add_item_to_inventory(player, itemToBuy)) {
        player->gold -= itemToBuy.cost;

        // **AQUÍ ESTÁ LA CORRECCIÓN**
        // Si el ítem es un arma o armadura y no fue equipado automáticamente (es decir,
        // no era "mejor"), entonces simplemente se añadió al inventario.
        // Si SÍ fue equipado automáticamente, la función player_add_item_to_inventory
        // ya llamó a player_equip_weapon/armor con el parámetro 'false'.
        // Por lo tanto, estas llamadas directas aquí son redundantes y problemáticas.
        // Las he comentado ya que la lógica de equipamiento ahora está en player_add_item_to_inventory.

        // if (itemToBuy.type == 1) { // Arma
        //     player_equip_weapon(player, itemToBuy, false); // false porque es un ítem nuevo de la tienda
        //     printf("Has equipado %s (+%d Atk).\n", itemToBuy.name, itemToBuy.damage);
        // } else if (itemToBuy.type == 2) { // Armadura
        //     player_equip_armor(player, itemToBuy, false); // false porque es un ítem nuevo de la tienda
        //     printf("Has equipado %s (+%d Def).\n", itemToBuy.name, itemToBuy.defense);
        // } else if (itemToBuy.type == 3) { // Poción
        //     printf("Has comprado %s y se ha añadido a tu inventario.\n", itemToBuy.name);
        // }
        // La confirmación de equipamiento o adición ya se maneja en player_add_item_to_inventory.

        // Imprimimos un mensaje general de compra exitosa
        printf("Has comprado %s y se ha gestionado tu inventario.\n", itemToBuy.name);
        return true;
    } else {
        printf("No se pudo comprar %s. (Inventario lleno o no fue mejor equipo)\n", itemToBuy.name);
        return false;
    }
}

void shop_free(Shop* shopToFree) {
    if (shopToFree == NULL) {
        return;
    }
    if (shopToFree->items != NULL) {
        // Con name y rarity como char[], no necesitamos liberar cada cadena individualmente.
        // La memoria para esas cadenas es parte del bloque de memoria de cada Item.
        // Al liberar shopToFree->items, se libera todo el bloque.
        free(shopToFree->items);
        shopToFree->items = NULL;
    }
    free(shopToFree);
    printf("Memoria de la tienda liberada.\n");
}
