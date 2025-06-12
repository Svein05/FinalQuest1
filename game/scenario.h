#ifndef ESCENARIO_H
#define ESCENARIO_H


#include <stdio.h>

typedef struct Enemy {
    int ID;
    char* nombre;
    int HP;
    int Damage;
    int Defense;
    int Dificultad;
    struct Enemy* next;
} Enemy;

typedef struct Mapa {
    int ID;
    char* nombre;
    char* descripcion;
    int dificultad;
    Enemy* enemigos;
    struct Mapa* next;
} Mapa;

// Funciones para mapas
Mapa* crearMapa(int id, const char* nombre, const char* descripcion, int dificultad);


void insertarMapa(Mapa** lista, Mapa* nuevoMapa);

Mapa* cargarMapasDesdeCSV(FILE* archivo);

void liberarMapas(Mapa* lista);


#endif
