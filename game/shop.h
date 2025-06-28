#ifndef SHOP_H
#define SHOP_H

#include <stdbool.h>
#include "data_types.h"
#include "../tdas/map.h"

// --- FUNCIONES DEL MÓDULO DE TIENDA ---

/**
 * @brief Inicializa un mercader aleatorio con ítems únicos para eventos.
 * Esta función es llamada cuando se encuentra un mercader en un evento aleatorio.
 * @param item_array Arreglo global de ítems ya cargados.
 * @param numItems Cantidad de ítems en el arreglo global.
 * @param maxDifficulty Dificultad máxima de los ítems a vender.
 * @return Un Map* temporal (clave: ID del ítem, valor: puntero a Item) con los ítems seleccionados.
 */
Map* shop_initialize_random_merchant(Item* item_array, int numItems, int maxDifficulty, Player* player);

/**
 * @brief Gestiona la interacción principal del jugador con una tienda.
 * Presenta el menú de la tienda, muestra ítems, el oro del jugador y maneja
 * las opciones de compra hasta que el jugador decide salir.
 * @param player Puntero al jugador actual.
 * @param itemMap Mapa de ítems del mercader (clave: ID, valor: Item*).
 */
void shop_interact(Player* player, Map* itemMap);

#endif