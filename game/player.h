#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "data_types.h" // Incluimos data_types.h para las definiciones de Player, Item, etc.

// --- DECLARACIONES DE FUNCIONES DEL MÓDULO PLAYER ---

/**
 * @brief Inicializa la estructura del jugador con sus estadísticas base y equipo vacío.
 * @param player Puntero a la estructura Player a inicializar.
 * @param name Nombre del jugador.
 * @param hp Vida máxima inicial del jugador.
 * @param atk Ataque inicial del jugador.
 * @param def Defensa inicial del jugador.
 * @param gold Oro inicial del jugador.
 */
void initializePlayer(Player* player, const char* name, int hp, int atk, int def, int gold);

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
 * @brief Equipa un arma al jugador, actualizando su ataque.
 * Si ya hay un arma equipada, la anterior va al inventario (si hay espacio).
 * @param player Puntero al jugador.
 * @param weapon El arma a equipar (se copia por valor).
 * @param from_inventory Indica si el arma viene del inventario (true) o es nueva (false).
 */
void player_equip_weapon(Player* player, Item weapon, bool from_inventory);

/**
 * @brief Equipa una armadura al jugador, actualizando su defensa.
 * Si ya hay una armadura equipada, la anterior va al inventario (si hay espacio).
 * @param player Puntero al jugador.
 * @param armor La armadura a equipar (se copia por valor).
 * @param from_inventory Indica si la armadura viene del inventario (true) o es nueva (false).
 */
void player_equip_armor(Player* player, Item armor, bool from_inventory);

/**
 * @brief Muestra un menú detallado del jugador con sus estadísticas, oro y equipo actual.
 * @param player Puntero a la estructura del Jugador.
 */
void displayPlayerMenu(Player* player);

/**
 * @brief Remueve un ítem específico del inventario del jugador por su ID.
 * Útil cuando un ítem es equipado (y se mueve del inventario al slot de equipo)
 * o cuando un consumible es usado.
 * @param player Puntero al jugador.
 * @param item_id El ID del ítem a remover.
 * @return true si el ítem fue removido, false si no se encontró.
 */
bool player_remove_item_from_inventory(Player* player, int item_id);

// --- DECLARACIONES DE FUNCIONES ADICIONALES (que ya estaban en player.c) ---
// Función para usar un consumible (ej. poción) desde el inventario del jugador
void player_use_consumable(Player* player, int itemIndexInInventory);

// Función para actualizar los efectos temporales del jugador al final de un turno
void player_update_temporary_boosts(Player* player);


#endif // PLAYER_H
