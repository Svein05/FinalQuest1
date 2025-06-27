#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "data_types.h" // Incluimos data_types.h para las definiciones de Player, Item, etc.

// --- DECLARACIONES DE FUNCIONES DEL MÓDULO PLAYER ---

/**
 * @brief Añade un ítem al inventario del jugador.
 * Si el ítem es equipable (arma/armadura) y mejora el equipo actual, lo equipa automáticamente.
 * Si no es equipable o no mejora el equipo, se añade al inventario si hay espacio.
 * @param player Puntero al jugador.
 * @param item El ítem a añadir/considerar (se copia por valor).
 * @return true si el ítem se añadió/equipó correctamente, false si el inventario está lleno y no se pudo equipar.
 */
bool player_add_item_to_inventory(Player* player, Item item);

/**
 * @brief Pregunta al usuario por la clase y asigna los valores al jugador.
 * @param player Puntero al jugador.
 */
void player_choose_and_assign_class(Player* player);

/**
 * @brief Añade ítems iniciales al inventario del jugador según su clase.
 * @param player Puntero al jugador.
 * @param initial_items_csv Cadena CSV con los ítems iniciales (id,cantidad) para añadir.
 */
void player_add_initial_class_items(Player* player, const char* initial_items_csv);

/**
 * @brief Muestra el inventario del jugador con formato visual, ocultando stats en 0.
 * @param player Puntero al jugador.
 * @param show_index Si es true, muestra el índice para selección.
 * @param show_use_option Si es true, muestra la opción de usar/cancelar.
 */
void display_inventory(Player* player, bool show_index, bool show_use_option);

// --- DECLARACIONES DE FUNCIONES ADICIONALES (que ya estaban en player.c) ---
// Función para usar un consumible (ej. poción) desde el inventario del jugador
void player_use_consumable(Player* player, int itemIndexInInventory);

// Función para actualizar los efectos temporales del jugador al final de un turno
void player_update_temporary_boosts(Player* player);


#endif // PLAYER_H
