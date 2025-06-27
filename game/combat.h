#ifndef COMBAT_H
#define COMBAT_H

#include <stdbool.h>
#include "data_types.h"
#include "player.h"

// --- DECLARACIONES DE FUNCIONES DEL MÓDULO COMBATE ---

/**
 * @brief El bucle de combate por turnos entre el jugador y un enemigo común.
 * Permite al jugador atacar o usar ítems, y al enemigo atacar en su turno.
 * Aplica efectos temporales y determina victoria o derrota.
 * @param player Puntero al jugador.
 * @param enemy Puntero al enemigo.
 * @return true si el jugador gana, false si pierde.
 */
bool combat_manage_turn(Player* player, Enemy* enemy);

/**
 * @brief El combate especial contra el jefe final, con fases y ataques únicos.
 * Incluye animaciones, cambios de fase y ataques especiales del boss.
 * @param player Puntero al jugador.
 * @param boss Puntero al jefe final.
 * @return true si el jugador gana, false si pierde.
 */
bool combat_final_boss(Player* player, Enemy* boss);

#endif // COMBAT_H