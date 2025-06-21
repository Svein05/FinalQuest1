#ifndef UI_H
#define UI_H

#include <stdio.h>
#include "data_types.h"
#include "../tdas/extra.h"
#include "player.h"
#include <windows.h>
#include "../tdas/map.h"

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
void display_title();
void display_player_summary(const Player* player);
void display_combat_text();
void display_combat_banner(const char* player_name, const char* enemy_name);
void display_intro_lore_and_ascii(const char* lore_inicial);
void print_lore_text_animated(const char* texto, int delay_ms);
void print_lore_text_animated_wrapped(const char* texto, int line_width, int delay_ms);
void display_lore_event(const char* lore);

typedef struct {
    int tipo;
    int* usados;
    int cantidad;
} LoreTracker;
void init_lore_tracker(LoreTracker* tracker, int tipo, int cantidad);
void free_lore_tracker(LoreTracker* tracker);
int get_random_unused_lore(LoreTracker* tracker);
void mark_lore_used(LoreTracker* tracker, int idx);

// Declaraciones de las funciones display para ui.h
void display_merchant_appearance(int merchantItemCount, int maxDifficulty);
void display_shop_welcome(int gold);
void display_shop_items(Map* itemMap);
void display_shop_item_detail(Item* item, int id);
void display_shop_menu();
void display_shop_buy_success(int gold);
void display_shop_exit();
void display_shop_invalid_option();
void display_shop_error(const char* msg);
void display_shop_input(const char* msg);

#endif // UI_H
