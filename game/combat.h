#ifndef COMBAT_H
#define COMBAT_H

#include <stdbool.h>
#include "data_types.h"
#include "player.h"

// --- DECLARACIONES DE FUNCIONES DEL MÓDULO COMBATE ---

/**
 * @brief Gestiona el bucle de combate por turnos entre el jugador y un enemigo.
 * En cada turno, permite al jugador realizar una acción y luego al enemigo atacar.
 * También gestiona los efectos temporales del jugador y las condiciones de victoria/derrota.
 *
 * @param player Puntero a la estructura del Jugador actual.
 * @param enemy Puntero a la estructura del Enemigo actual al que se enfrenta.
 * @return true si el jugador gana el combate, false si el jugador es derrotado.
 */
bool combat_manage_turn(Player* player, Enemy* enemy);

// Calcula el daño real después de aplicar la defensa.
int calculate_damage(int attack, int defense);

// Muestra el estado actual del combate (HP de jugador y enemigo).
void display_combat_status(Player* player, Enemy* enemy);

// Permite al jugador elegir una acción durante su turno (atacar, usar ítem, etc.).
int player_choose_action(Player* player);

// Aplica el daño a una entidad (jugador o enemigo).
void apply_damage(int* target_hp, int damage_dealt);

#endif // COMBAT_H
// --- FIN DEL MÓDULO COMBATE ---