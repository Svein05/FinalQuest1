#ifndef UI_H
#define UI_H

#include <stdio.h>
#include "data_types.h"
#include "../tdas/extra.h"
#include "player.h"
#include <windows.h>
#include "../tdas/map.h"

// ----- Funciones Generales

void ui_menu_welcome();
void ui_menu_title();
void ui_wait_dots();
void ui_load_animation();
int ui_gameover_retry();
int ui_sleep_skip(int ms);
void ui_bonus();

// ------ Funciones de combate

void ui_combat_text();
void ui_combat_banner(const char* player_name, const char* enemy_name);
void ui_entrance_boss(const char* boss_name);
void ui_boss_victory();
void ui_boss_defeat(const char* boss_name);
void ui_boss_phase2();
void ui_boss_phase3();


// ------ Funciones de muestreo para el Jugador ------

void ui_choice_class();
void ui_player_init(Player *player);
void ui_player_summary(const Player* player);


// ------ Funciones de muestreo para SHOP ------

void ui_shop();
void ui_shop_welcome(int gold);
void ui_shop_items(Map* itemMap);
void ui_shop_menu(bool hay_items);
void ui_shop_buy(int gold);
void ui_msg_error(const char* msg);


// ------ Funciones de muestreo para los Escenarios ------

void ui_scenario(const Scenario* scenario);
void ui_lore_zero(Map* lore_map, int tipo);
void ui_lore_event(const char* lore);

#endif // UI_H
