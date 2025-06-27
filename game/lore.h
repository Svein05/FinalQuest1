#ifndef LORE_H
#define LORE_H

#include "../tdas/map.h"
#include "../tdas/list.h"

// Estructura para el tracker de lore
typedef struct {
    int tipo;      // Tipo de lore (ambiental o profundo)
    int* usados;   // Array para marcar fragmentos ya usados
    int cantidad;  // Cantidad total de fragmentos
} LoreTracker;

/**
 * @brief Inicializa un LoreTracker con tipo y cantidad de fragmentos.
 * @param tracker Puntero al tracker a inicializar.
 * @param tipo Tipo de lore (ambiental o profundo).
 * @param cantidad Número total de fragmentos de ese tipo.
 */
void init_lore_tracker(LoreTracker* tracker, int tipo, int cantidad);

/**
 * @brief Libera la memoria reservada por un LoreTracker.
 * @param tracker Puntero al tracker a liberar.
 */
void free_lore_tracker(LoreTracker* tracker);

/**
 * @brief Devuelve el índice de un fragmento de lore no usado al azar.
 * @param tracker Puntero al tracker a consultar.
 * @return Índice de fragmento no usado, o -1 si no quedan disponibles.
 */
int get_random_unused_lore(LoreTracker* tracker);

/**
 * @brief Marca un fragmento de lore como usado.
 * @param tracker Puntero al tracker.
 * @param idx Índice del fragmento a marcar como usado.
 */
void mark_lore_used(LoreTracker* tracker, int idx);

/**
 * @brief Inicializa el mapa de lore y los trackers de lore ambiental y profundo.
 * @param path Ruta al archivo de datos de lore.
 * @param tracker_ambiental Puntero al tracker de lore ambiental.
 * @param tracker_profundo Puntero al tracker de lore profundo.
 * @return Puntero al mapa de lore cargado.
 */
Map* lore_init_all(const char* path, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo);

/**
 * @brief Libera la memoria de los trackers y del mapa de lore.
 * @param lore_map Puntero al mapa de lore a liberar.
 * @param tracker_ambiental Puntero al tracker de lore ambiental.
 * @param tracker_profundo Puntero al tracker de lore profundo.
 */
void lore_free_all(Map* lore_map, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo);

#endif // LORE_H
