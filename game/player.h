#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "data_types.h"

// --- DECLARACIONES DE FUNCIONES DEL MÓDULO PLAYER ---

/**
 * Gestiona la adición de ítems al inventario del jugador con lógica inteligente
 * @param player Puntero al jugador que recibirá el ítem
 * @param item Ítem a procesar (pasado por valor para hacer una copia)
 * @return true si se pudo equipar o añadir al inventario, false si no hay espacio o falló
 */
bool player_add_item_to_inventory(Player* player, Item item);

/**
 * Gestiona el proceso completo de selección de clase del jugador
 * @param player Puntero al jugador al que se asignará la clase
 */
void player_choose_and_assign_class(Player* player);

/**
 * Procesa y añade los ítems iniciales correspondientes a la clase del jugador
 * @param player Puntero al jugador que recibirá los ítems iniciales
 * @param initial_items_csv Cadena CSV con los ítems iniciales (formato: "id,cant,id,cant,...")
 */
void player_add_initial_class_items(Player* player, const char* initial_items_csv);

/**
 * Muestra el inventario completo del jugador con formato visual mejorado
 * @param player Puntero al jugador cuyo inventario se mostrará
 * @param show_index Si es true, muestra números de índice para cada ítem
 * @param show_use_option Si es true, muestra opciones de usar/cancelar al final
 */
void display_inventory(Player* player, bool show_index, bool show_use_option);

/**
 * Ejecuta el uso de un ítem consumible desde el inventario del jugador
 * @param player Puntero al jugador que usará el consumible
 * @param itemIndexInInventory Índice del ítem en el inventario (base 0)
 */
void player_use_consumable(Player* player, int itemIndexInInventory);

/**
 * Actualiza y gestiona todos los efectos temporales activos del jugador
 * @param player Puntero al jugador cuyos efectos temporales se actualizarán
 */
void player_update_temporary_boosts(Player* player);


#endif // PLAYER_H
