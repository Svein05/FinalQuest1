#ifndef SCENARIO_H
#define SCENARIO_H

#include <stdbool.h>    // Para usar el tipo de dato 'bool'
#include "data_types.h" // Incluimos data_types.h para las definiciones de Player, Enemy, Item, Scenario
#include "../tdas/stack.h"
#include "../tdas/queue.h"

// --- DEFINICIONES DE TIPOS DE ESCENARIO ---
// Estos valores corresponden a los tipos de escenario en la estructura Scenario.
// 1: Combate
// 2: Tienda (solo la inicial)
// 3: Evento Aleatorio (puede ser combate, mercader o bonus)
// 4: Jefe Final
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
void scenario_manage_event(Player* player, Item* allItems, int numItems, Enemy* allEnemies, int numEnemies, Scenario *scenario);

void poblarGameMap(Stack* game_map, Scenario* escenarios, int numScenarios);
bool FINALBOSS(Player* player, Enemy* allEnemies, int numEnemies);

#endif // SCENARIO_H
