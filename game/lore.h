#ifndef LORE_H
#define LORE_H

#include "../tdas/map.h"
#include "../tdas/list.h"

// Estructura para el tracker de lore
typedef struct {
    int tipo;
    int* usados;
    int cantidad;
} LoreTracker;

void init_lore_tracker(LoreTracker* tracker, int tipo, int cantidad);
void free_lore_tracker(LoreTracker* tracker);
int get_random_unused_lore(LoreTracker* tracker);
void mark_lore_used(LoreTracker* tracker, int idx);
// Inicializa lore_map y trackers, retorna el Map* y deja trackers listos
Map* lore_init_all(const char* path, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo);
// Libera lore_map y trackers
void lore_free_all(Map* lore_map, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo);

#endif // LORE_H
