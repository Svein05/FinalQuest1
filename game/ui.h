#ifndef UI_H
#define UI_H

#include <stdio.h>
#include "data_types.h"
#include "../tdas/extra.h"
#include "player.h"
#include <windows.h>

// Funciones de impresión para el usuario
void welcome_program();
void welcome_zero(Player* player);
void mostrarInstrucciones();
void mostrarGameOver();
void mostrarVictoria();
void wait_three_points();
void choice_class_menu();
void initializePlayer_menu(Player *player);
// Imprime un escenario con bordes y formato uniforme
void display_scenario(const Scenario* scenario);
// Formatea y muestra la descripción del escenario dentro de los bordes
void print_scenario_description(const char* description, int width);
void display_player_summary(const Player* player);

#endif // UI_H
