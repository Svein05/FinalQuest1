#ifndef SHOP_H
#define SHOP_H

#include <stdbool.h>
#include <data_types.h>

// --- ESTRUCTURA DE TIENDA ---

// Estructura que representa una Tienda o un Mercader.
// Contiene un conjunto de ítems que están a la venta.
typedef struct {
    Item* items;        // Puntero al arreglo de Items disponibles en esta tienda.
    int itemCount;      // La cantidad actual de ítems en venta en esta tienda.
} Shop;

// --- FUNCIONES DEL MÓDULO DE TIENDA ---

/**
 * @brief Inicializa la tienda principal del juego (la del primer mapa).
 * Asigna memoria para la tienda y sus ítems, y los carga.
 * @return Un puntero a la estructura Shop inicializada, o NULL en caso de error.
 */
Shop* shop_initialize_start_shop();

/**
 * @brief Inicializa un mercader aleatorio con ítems únicos para eventos.
 * Esta función es llamada cuando se encuentra un mercader en un evento aleatorio.
 * @return Un puntero a la estructura Shop del mercader, o NULL en caso de error.
 */
Shop* shop_initialize_random_merchant();

/**
 * @brief Gestiona la interacción principal del jugador con una tienda.
 * Presenta el menú de la tienda, muestra ítems, el oro del jugador y maneja
 * las opciones de compra hasta que el jugador decide salir.
 * @param player Puntero al jugador actual.
 * @param currentShop Puntero a la tienda/mercader con el que se está interactuando.
 */
void shop_interact(Player* player, Shop* currentShop);

/**
 * @brief Permite al jugador comprar un ítem específico de la tienda.
 * Realiza las validaciones necesarias (oro, espacio en inventario) y aplica
 * los cambios correspondientes al jugador (deduce oro, añade ítem, actualiza stats).
 * @param player Puntero al jugador actual.
 * @param currentShop Puntero a la tienda de la que se desea comprar.
 * @param itemIndex El índice (posición) del ítem que el jugador desea comprar en la tienda.
 * @return 'true' si la compra fue exitosa, 'false' en caso contrario (ej. no hay oro).
 */
bool shop_buy_item(Player* player, Shop* currentShop, int itemIndex);

/**
 * @brief Libera la memoria asignada dinámicamente para una estructura Shop
 * y los ítems que contenía.
 * Debe ser llamada cuando una tienda (especialmente los mercaderes aleatorios)
 * ya no se necesite para evitar fugas de memoria.
 * @param shopToFree Puntero a la estructura Shop a liberar.
 */
void shop_free(Shop* shopToFree);

#endif