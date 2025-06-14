#include <stdio.h>
#include <stdlib.h>

#include "tdas/map.h"
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/stack.h"
#include "tdas/hashmap.h"

#include "game/player.h"
#include "game/combat.h"
#include "game/shop.h"
#include "game/scenario.h"
#include "game/data_loader.h"


#include"game/data_types.h"

#pragma region MAIN
int main() {
    // Logica del Juego
    // Utilizando funciones de /game/
    // Crear ramas
    // feature/<funcion>
    // bugfix/<error>
    // Update (fusionar con la rama main)
    
    Stack* game_map = load_map(); // Pregeneramos el mapa en una pila. 
    List* enemies_list = load_enemies(); // rellenamos una lista enlazada de enemigos, en base a ID del 0 al N
    Map* items_mapa = load_items(); // ??
    Jugador* jugador = iniciar_jugador();

    Mapa* mapa_actual = stack_top(game_map);
    while (jugador->hp > 0 && mapa_actual != NULL)
    {
        int tipo_escenario = obtener_tipo_escenario(mapa_actual);
        switch (tipo_escenario)
        {
            // COMBATE
            case 1:
                Enemigo* enemigo = obtener_enemigo(mapa_actual, enemigos_mapa);
                int estado_combate = gestor_turnos(&jugador, enemigo);

                if (estado_combate) {
                    jugador->oro += enemigo->dificultad;
                } else {
                    mapa_actual = NULL;
                }

                break;
            
            // ALEATORIO
            case 3:
                gestionar_evento_aleatorio(&jugador);
                break;
            
            // JEFE FINAL
            case 4:
                Enemigo* jefe_final = obtener_enemigo(mapa_actual, enemigos_mapa);
                int estado_combate = gestor_turnos(&jugador, jefe_final);

                if (estado_combate) {
                    // Victoria
                } else {
                    // Derrota
                }
                mapa_actual = NULL;
        }

        if (jugador->hp > 0 && mapa_actual != NULL && tipo_escenario != 4) {
            mapa_actual = list_next(game_list);
        }
    }

    liberar_game_data(game_list, items_mapa, enemigos_mapa);

    return 0;
}
#pragma endregion

// primer parte: tienda