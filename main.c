#include <stdio.h>
#include <stdlib.h>

#include "tdas/map.h"
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/hashmap.h"

#include "game/player.h"
#include "game/combat.h"
#include "game/shop.h"
#include "game/scenario.h"
#include "game/data_loader.h"

#pragma region MAIN
int main() {
    // Logica del Juego
    // Utilizando funciones de /game/
    // Crear ramas
    // feature/<funcion>
    // bugfix/<error>
    // Update (fusionar con la rama main)

    List* game_list = cargar_mapa();
    Map* enemigos_mapa = cargar_enemigos(); // POR ID
    Map* items_mapa = cargar_items(); // POR ID
    Jugador* jugador = iniciar_jugador();

    Mapa* mapa_actual = list_first(game_list);
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
            
            // TIENDA
            case 2:
                gestionar_tienda(&jugador, items_mapa);
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