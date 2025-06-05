#ifndef SCENARIO_H
#define SCENARIO_H

typedef struct{
    int ID;
    char* nombre;
    char* descripcion;
    int dificultad;
    int tipo; // 1. TIENDA 2. COMBATE 3. EVENTO_ALEATORIO 4. BOSS FINAL
} Mapa;


#endif