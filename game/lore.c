#include "lore.h"
#include <stdlib.h>

void init_lore_tracker(LoreTracker* tracker, int tipo, int cantidad) {
    tracker->tipo = tipo;
    tracker->cantidad = cantidad;
    tracker->usados = calloc(cantidad, sizeof(int));
}

void free_lore_tracker(LoreTracker* tracker) {
    free(tracker->usados);
}

int get_random_unused_lore(LoreTracker* tracker) {
    int disponibles = 0;
    for (int i = 0; i < tracker->cantidad; i++) if (!tracker->usados[i]) disponibles++;
    if (disponibles == 0) return -1;
    int elegido = rand() % disponibles;
    for (int i = 0, c = 0; i < tracker->cantidad; i++) {
        if (!tracker->usados[i]) {
            if (c == elegido) return i;
            c++;
        }
    }
    return -1;
}

void mark_lore_used(LoreTracker* tracker, int idx) {
    tracker->usados[idx] = 1;
}

Map* lore_init_all(const char* path, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo) {
    extern Map* load_lore_map(const char* path); // Declaración externa
    Map* lore_map = load_lore_map(path);
    if (!lore_map) return NULL;
    int cantidad_ambiental = 0, cantidad_profundo1 = 0, cantidad_profundo2 = 0;
    int tipo_ambiental = 0, tipo_profundo1 = 1, tipo_profundo2 = 2;
    MapPair* pair_ambiental = map_search(lore_map, &tipo_ambiental);
    MapPair* pair_profundo1 = map_search(lore_map, &tipo_profundo1);
    MapPair* pair_profundo2 = map_search(lore_map, &tipo_profundo2);
    if (pair_ambiental && pair_ambiental->value) cantidad_ambiental = list_size((List*)pair_ambiental->value);
    if (pair_profundo1 && pair_profundo1->value) cantidad_profundo1 = list_size((List*)pair_profundo1->value);
    if (pair_profundo2 && pair_profundo2->value) cantidad_profundo2 = list_size((List*)pair_profundo2->value);
    // Inicializa tracker ambiental (tipo 0)
    init_lore_tracker(tracker_ambiental, tipo_ambiental, cantidad_ambiental);
    // Inicializa tracker profundo para tipo 1 (historia) y tipo 2 (final)
    // Si hay lore tipo 2, inicializa tracker_profundo para tipo 2, si no, para tipo 1
    if (cantidad_profundo2 > 0) {
        init_lore_tracker(tracker_profundo, tipo_profundo2, cantidad_profundo2);
    } else {
        init_lore_tracker(tracker_profundo, tipo_profundo1, cantidad_profundo1);
    }
    return lore_map;
}

void lore_free_all(Map* lore_map, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo) {
    free_lore_tracker(tracker_ambiental);
    free_lore_tracker(tracker_profundo);
    free(lore_map);
}
