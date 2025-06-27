#ifndef SCENARIO_H
#define SCENARIO_H

#include <stdbool.h>    // Para usar el tipo de dato 'bool'
#include "data_types.h" // Incluimos data_types.h para las definiciones de Player, Enemy, Item, Scenario
#include "../tdas/queue.h"
#include "../tdas/map.h"
#include "ui.h"
#include "lore.h"

#define SCENARIO_TYPE_COMBAT 1
#define SCENARIO_TYPE_SHOP 2
#define SCENARIO_TYPE_EVENT 3
#define SCENARIO_TYPE_BOSS 4

/**
 * @brief Obtiene el enemigo específico para un nodo de escenario de combate.
 * Este enemigo puede ser aleatorio según la dificultad del escenario,
 * o un enemigo predefinido si el escenario lo especifica.
 *
 * @param Scenario Puntero al nodo de escenario actual.
 * @param allEnemies Arreglo de todos los enemigos disponibles en el juego.
 * @param numEnemies Número total de enemigos en allEnemies.
 * @return Un puntero al enemigo que debe aparecer en este escenario.
 */
Enemy* getEnemyForScenario(Scenario* Scenario, Enemy* allEnemies, int numEnemies);

/**
 * @brief Gestiona un evento aleatorio cuando el jugador entra a un escenario de tipo EVENTO.
 * Puede resultar en un combate (con enemigo aleatorio), un encuentro con un mercader,
 * o una bonificación (oro, vida, estadísticas).
 *
 * @param player Puntero al jugador actual.
 * @param allItems Arreglo de todos los ítems disponibles en el juego.
 * @param numItems Número total de ítems en allItems.
 * @param allEnemies Arreglo de todos los enemigos disponibles en el juego.
 * @param numEnemies Número total de enemigos en allEnemies.
 */
void scenario_manage_event(Player* player, Item* allItems, int numItems, Enemy* allEnemies, int numEnemies, Scenario *scenario, Map* lore_map, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo);

/**
 * @brief Llena la cola del mapa de juego con los escenarios definidos.
 * @param game_map Puntero a la cola donde se almacenarán los escenarios.
 * @param escenarios Arreglo de escenarios a poblar.
 * @param numScenarios Número total de escenarios en el arreglo.
 */
void poblarGameMap(Queue* game_map, Scenario* escenarios, int numScenarios);

/**
 * @brief Ejecuta el evento del jefe final, gestionando el combate y la narrativa.
 * @param player Puntero al jugador actual.
 * @param allEnemies Arreglo de todos los enemigos disponibles en el juego.
 * @param numEnemies Número total de enemigos en allEnemies.
 * @param lore_map Mapa de fragmentos de lore.
 * @param tracker_profundo Tracker de lore profundo para el jefe final.
 * @return true si el jugador vence al jefe final, false si es derrotado.
 */
bool FINALBOSS(Player* player, Enemy* allEnemies, int numEnemies, Map* lore_map, LoreTracker* tracker_profundo);

/**
 * @brief Muestra un fragmento de lore aleatorio sin repetir, según el tipo indicado.
 * @param lore_map Mapa de fragmentos de lore.
 * @param tracker Tracker de uso de fragmentos de lore.
 * @param tipo Tipo de lore a mostrar (ambiental o profundo).
 */
void show_random_lore_no_repeat(Map* lore_map, LoreTracker* tracker, int tipo);

#endif // SCENARIO_H
