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

#endif // UI_H
