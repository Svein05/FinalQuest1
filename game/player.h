#ifndef PLAYER_H
#define PLAYER_H

#include "tdas/list.h"

typedef struct {
    char* nombre;
    List* inventario;
    int hp;
    int damage;
    int defense;
    int oro;
    int clase;
} Jugador;

#endif