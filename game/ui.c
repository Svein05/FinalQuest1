#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>

#include "data_types.h"
#include "ui.h"
#include "player.h"
#include "../tdas/extra.h"
#include "../tdas/extra.h"
#include "../tdas/map.h"


void ui_menu_title() {
    printf("\x1b[36m╔════════════════════════════════════════════╗\x1b[0m\n");
    puts("\x1b[36m║\x1b[0m              FinalQuest 1                  \x1b[36m║\x1b[0m");
    printf("\x1b[36m╚════════════════════════════════════════════╝\x1b[0m\n\n");
}

void ui_menu_welcome() {
    printf("\x1b[36m╔══════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m            FinalQuest 1              \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╚══════════════════════════════════════╝\x1b[0m\n\n");

    ui_choice_class();
}

/**
 * @brief Espera la cantidad de milisegundos indicada, pero si el usuario presiona Enter, termina la espera inmediatamente.
 * @param ms Milisegundos a esperar (máximo).
 * @return 1 si se presionó Enter, 0 si no.
 */
int ui_sleep_skip(int ms) {
    int elapsed = 0;
    int interval = 30; // ms entre chequeos
    while (elapsed < ms) {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 13) return 1; // Enter
        }
        Sleep(interval);
        elapsed += interval;
    }
    return 0;
}

void ui_wait_dots() {
    int skip = 0;
    for (int i = 0; i < 3; i++) {
        if (!skip && _kbhit()) {
            int ch = _getch();
            if (ch == 13) skip = 1;
        }
        if (!skip) skip = ui_sleep_skip(1000);
        printf(".");
        fflush(stdout);
    }
    if (!skip) skip = ui_sleep_skip(1500);
    printf("\n");
}

void ui_load_animation(const char* mensaje) {
    int steps = 5;
    int percent[] = {20, 40, 60, 80, 100};
    int skip = 0;
    for (int i = 1; i <= steps; i++) {
        printf("%s [", mensaje);
        for (int j = 1; j <= steps; j++) {
            if (j <= i) printf("■");
            else printf("□");
        }
        printf("] %d%%\r", percent[i-1]);
        fflush(stdout);
        if (!skip) skip = ui_sleep_skip(350);
    }
    printf("%s [■■■■■] 100%%\n", mensaje);
    fflush(stdout);
}

/**
 * @brief texto de lore con animación de letra por letra y salto de línea automático.
 * @param texto Texto a mostrar animado.
 * @param line_width Ancho máximo de línea antes de salto.
 * @param delay_ms Milisegundos de retardo por carácter
**/
void print_lore_text_animated_wrapped(const char* texto, int line_width, int delay_ms) {
    int len = strlen(texto);
    int col = 0;
    int skip = 0;
    for (int i = 0; i < len; i++) {
        if (!skip && _kbhit()) {
            int ch = _getch();
            if (ch == 13) skip = 1; // Enter
        }
        putchar(texto[i]);
        fflush(stdout);
        col++;
        if (col >= line_width && texto[i] == ' ') {
            putchar('\n');
            printf("  ");
            col = 0;
        }
        if (!skip) Sleep(delay_ms);
    }
    putchar('\n');
}

/**
 * @brief Muestra el menú de game over y pregunta si el usuario quiere reintentar.
 * @return 1 si el usuario quiere reintentar, 0 si quiere salir.
**/
int ui_gameover_retry() {
    clearScreen();
    printf("\x1b[40m\x1b[90m");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠖⠶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡶⠤⣤⣀⡀⢠⠏⠀⡄⠀⢹⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⣠⠀⠀⡉⠹⠏⠀⠀⠙⣆⣿⣿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣿⣀⠘⠳⡄⠘⡜⣄⡘⡜⡄⢌⢿⠛⠶⢤⣄⡀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠶⢤⡔⠹⡜⣜⣞⣜⣎⢮⢣⡀⣰⣿⣿⠇⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠁⠱⡹⣼⣾⣾⣌⣧⢳⣳⣯⣿⠏⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣼⠇⠀⠀⠐⣿⣿⡟⠈⠉⠛⠿⠾⠏⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠛⠉⠉⠉⠉⠉⠉⠉⠉⠙⠻⠷⢶⣶⣦⣴⣟⠀⠀⠀⣾⢧⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣼⣧⣀⣟⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠛⠿⢿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠁⠀⠀⠈⠿⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢷⣿⡻⢶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠁⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⣿⣦⡉⠛⢷⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣴⠋⠹⣿⣯⢙⠺⣿⡷⡄⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⢸⠀⠀⢷⣿⣿⣟⢟⣿⣾⣆⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⠀⠀⠀⠀⢠⣤⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠁⠀⢠⡟⢎⠻⣷⣕⠼⢿⡆⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠃⠀⠀⠀⢀⣾⣾⣿⣿⣦⠀⠀⠀⢠⣄⣀⡀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠈⠓⣌⢻⡳⣼⣧⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠀⠀⠀⠀⢀⣾⣽⣿⣬⣿⣿⠀⠀⢀⡿⢠⣹⠇⠀⠀⣼⣯⢿⣷⣦⡀⠀⠀⠀⠀⠀⢠⣿⠀⠀⢐⢌⠳⣝⣿⡟⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠀⠀⠀⢀⣾⢉⣿⣿⣿⠿⠋⠀⠀⣼⠇⣛⡿⠀⠀⣼⠃⢹⠿⣧⣽⣷⡄⠀⠀⠀⠀⣸⡷⡄⠀⠈⠳⡑⣾⣿⣲⠆⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠇⠀⠀⠀⢀⡞⢀⡟⣿⢹⣷⠀⠀⠀⢠⡏⠀⣿⠃⠀⣸⠇⢡⣿⣿⣏⣬⣾⠃⠀⠀⠀⢀⣿⢄⠙⢄⠀⣀⣼⢿⣟⣿⡇⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⠀⠀⠀⠀⢼⣇⡾⠀⣿⡰⣿⠀⠀⠀⡼⠀⣼⠃⠀⢀⡏⠀⣿⡟⠛⠛⠋⠀⠀⠀⠀⠀⢸⠇⠀⠳⣬⣾⣻⣿⣿⣿⣿⡇⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠀⠀⠀⠀⠀⠀⠈⠁⠀⠛⠿⠿⠀⠀⠸⢷⣼⠏⠀⠀⣾⣠⣼⡟⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⠰⣠⣾⣿⣿⠛⢧⡘⢦⣽⡇⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠋⠛⠿⠁⠀⠀⠀⠀⠀⠀⠀⢀⣾⡇⣾⣿⣿⠉⣀⠑⢄⠙⠦⣿⠁⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⡾⠋⣻⡛⢻⡇⠀⠱⣌⢷⣄⠱⢤⡏⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⠔⠀⡟⠙⢮⣿⣄⠱⣜⢦⡙⢦⣼⡇⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⢿⣇⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣄⠠⠟⡀⠀⢰⣧⣀⢌⠻⣿⡧⣌⠣⡉⠲⣿⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⣼⠃⠘⠿⠶⣶⡏⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢦⡀⠈⢢⣼⠁⠈⢦⡑⣿⣧⡈⠳⣌⢲⡏⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⣰⠇⠈⠢⡀⠀⢻⣗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣄⠀⠙⣶⣼⣟⠂⠀⣄⠹⣝⣿⣟⢧⡈⣹⠇⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢰⡟⣄⠀⠀⠈⠢⡘⠻⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠈⠳⣴⡟⢹⣿⢳⣄⣮⣳⣼⣿⡈⠳⣍⡿⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⢠⡿⠁⠈⠢⣄⠀⣀⠀⠀⠀⠀⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⡀⠓⢄⠸⣷⣯⣧⠘⢯⣻⣿⣟⣇⠙⢄⣸⡇⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⣾⠃⠀⠀⠀⠈⠳⣌⠳⢄⡈⠢⡀⠙⠢⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠳⣄⠀⠀⠙⢦⡈⣿⣿⡟⢧⡰⣄⠻⣿⢯⣫⡙⢦⣿⠁⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⢀⣠⣤⣤⣼⣏⣀⣤⣤⣤⣤⣀⠈⠁⠀⣁⣦⠬⠶⠶⠾⣦⣤⣄⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⢌⠑⠄⠀⠀⣩⣿⡿⠁⠀⣕⢌⠳⡈⠳⣝⢭⢺⡟⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠉⠁⠀⣀⣰⣯⣀⡀⠀⢠⠟⠉⠉⠉⠿⣧⠀⠀⠀⠀⠀⠀⢹⡌⠳⠄⠑⢦⡀⣀⡴⠖⠒⠻⠶⣵⣄⡁⠀⣿⢿⠉⠳⣔⣜⢮⡳⣝⢦⠘⢦⣿⣃⣀⣀⣀⠀⠀⠀⠀⠀\n");
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║ Has sido derrotado. ¿Qué deseas hacer? ║\n");
    printf("╟────────────────────────────────────────╢\n");
    printf("  [1] Volver a jugar desde el inicio      \n");
    printf("  [2] Salir del juego                     \n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\x1b[0m\n");
    printf("Tu elección: ");
    char input[10];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        int choice = atoi(input);
        if (choice == 1) return 1;
    }
    return 0;
}

void ui_choice_class() {
    printf("\x1b[36m╔══════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m \x1b[33m     BIENVENIDO A TU AVENTURA        \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╟──────────────────────────────────────╢\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m \x1b[33mELIGE TU CLASE:\x1b[0m                      \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m 1. \x1b[32mGuerrero\x1b[0m                          \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m 2. \x1b[34mTanque\x1b[0m                            \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m 3. \x1b[31mAsesino\x1b[0m                           \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╚══════════════════════════════════════╝\x1b[0m\n");
}

void ui_player_init(Player* player) {
    clearScreen();
    ui_menu_title();
    printf("\x1b[36m╔════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m        \x1b[33m¡Héroe creado exitosamente!\x1b[0m         \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╠════════════════════════════════════════════╣\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m Clase: %-36s\x1b[36m║\x1b[0m\n", player->name);
    printf("\x1b[36m║\x1b[0m Vida: \x1b[32m%-3d\x1b[0m   Ataque: \x1b[31m%-3d\x1b[0m   Defensa: \x1b[34m%-3d\x1b[0m     \x1b[36m║\x1b[0m\n", player->maxHP, player->attack, player->defense);
    printf("\x1b[36m║\x1b[0m Oro inicial: \x1b[33m%-30d\x1b[0m\x1b[36m║\x1b[0m\n", player->gold);
    printf("\x1b[36m╚════════════════════════════════════════════╝\x1b[0m\n");
}

/**
 * Formatea y muestra la descripción del escenario dentro de los bordes
 * Imprime la descripción de un escenario con saltos de línea y formato de cuadro.
 * @param texto Texto de la descripción.
 * @param line_width Ancho máximo de línea.
**/
void print_scenario_description(const char *texto, int line_width) 
{
    // Tomamo el largo de la cadena
    int len = strlen(texto);
    int i = 0;

    // Hacemos un bucle hasta que la variable alcance al largo de la cadena
    while (i < len) 
    {
        // Usamos LINE_WIDTH como el ancho que tendra el texto
        // Indicado por el cuadro y sus limites
        int j = i + line_width;

        // Si el texto restante es menor al ancho, imprime y termina
        if (j >= len) 
        {
            printf("\x1b[36m║\x1b[0m %-*s \x1b[36m║\x1b[0m\n", line_width, texto + i);
            break;
        }

        // Busca el ultimo espacio antes de pasar el limite
        int espacio = j;
        while (espacio > i && texto[espacio] != ' ') espacio--;

        // Si no hay espacio se corta al limite
        if (espacio == i) espacio = j;

        // Se imprime la linea
        char buffer[line_width + 1];
        strncpy(buffer, texto + i, espacio - i);
        buffer[espacio - i] = '\0';
        // Elimina saltos de línea y espacios finales
        int end = strlen(buffer) - 1;
        while (end >= 0 && (buffer[end] == ' ' || buffer[end] == '\n' || buffer[end] == '\r')) {
            buffer[end] = '\0';
            end--;
        }
        printf("\x1b[36m║\x1b[0m %-*.*s \x1b[36m║\x1b[0m\n", line_width, line_width, buffer);

        // Salta los espacios consecutivos
        i = espacio;
        while (isspace(texto[i])) i++;
    }
}

// Imprime un escenario con bordes y formato uniforme
void ui_scenario(const Scenario* scenario) {
    ui_menu_title();

    int width = 42;
    printf("\x1b[36m╔════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m \x1b[33mESCENARIO: %-32s\x1b[36m║\x1b[0m\n", scenario->name);
    printf("\x1b[36m╟────────────────────────────────────────────╢\x1b[0m\n");
    print_scenario_description(scenario->description, width);
    printf("\x1b[36m╚════════════════════════════════════════════╝\x1b[0m\n");
}

void ui_player_summary(const Player* player) {
    printf("\n\x1b[36m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m \x1b[33mRESUMEN DEL JUGADOR\x1b[0m%42s\x1b[36m║\x1b[0m\n", "");
    printf("\x1b[36m╟──────────────────────────────────────────────────────────────╢\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m Clase: %-20s Enemigos derrotados: %-4d        \x1b[36m║\x1b[0m\n", player->name, player->enemiesDefeated);
    printf("\x1b[36m║\x1b[0m Vida: \x1b[32m%4d/%-4d\x1b[0m  Atk: \x1b[31m%-4d\x1b[0m  Def: \x1b[34m%-4d\x1b[0m  Oro: \x1b[33m%-5d\x1b[0m            \x1b[36m║\x1b[0m\n", player->currentHP, player->maxHP, player->attack, player->defense, player->gold);
    printf("\x1b[36m║\x1b[0m Arma equipada: %-24s (+%-2d Atk)%12s\x1b[36m║\x1b[0m\n", player->equippedWeapon.name, player->equippedWeapon.damage, "");
    printf("\x1b[36m║\x1b[0m Armadura equipada: %-20s (+%2d Def)%12s\x1b[36m║\x1b[0m\n", player->equippedArmor.name, player->equippedArmor.defense, "");
    printf("\x1b[36m╟──────────────────────────────────────────────────────────────╢\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m Slots disponibles de inventario: %-2d %25s\x1b[36m║\x1b[0m\n", INVENTORY_SLOTS - player->inventoryCount, "");
    printf("\x1b[36m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
}

void ui_combat_text() {
    int combate_disenio = rand() % 3;
    int skip = 0;
    for (int i = 0 ; i < 2 ; i++){
        clearScreen();
        if (combate_disenio == 0) {
            // Diseño 1: Clásico de peligro
            printf("\x1b[31m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
            printf("\x1b[31m║                  ¡ENEMIGO INESPERADO APARECE!                ║\x1b[0m\n");
            printf("\x1b[31m╠══════════════════════════════════════════════════════════════╣\x1b[0m\n");
            printf("\x1b[31m║        ¡Prepárate para la batalla, valiente aventurero!      ║\x1b[0m\n");
            printf("\x1b[31m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
        } else if (combate_disenio == 1) {
            // Diseño 4: Alerta máxima
            printf("\x1b[31m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
            printf("\x1b[31m║                    ¡PELIGRO! ¡PELIGRO!                       ║\x1b[0m\n");
            printf("\x1b[31m╠══════════════════════════════════════════════════════════════╣\x1b[0m\n");
            printf("\x1b[31m║               ¡Un enemigo bloquea tu avance!                 ║\x1b[0m\n");
            printf("\x1b[31m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
        } else {
            // Diseño 5: Estilo épico
            printf("\x1b[31m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
            printf("\x1b[31m║              ¡UNA BATALLA COMENZARA, PREPARATE!              ║\x1b[0m\n");
            printf("\x1b[31m╠══════════════════════════════════════════════════════════════╣\x1b[0m\n");
            printf("\x1b[31m║            ¡Demuestra tu valor contra el enemigo!            ║\x1b[0m\n");
            printf("\x1b[31m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
        }
        fflush(stdout);
        if (!skip) skip = ui_sleep_skip(500);
        clearScreen();
        if (!skip) skip = ui_sleep_skip(500);
    }
    if (combate_disenio == 0) {
        // Diseño 1: Clásico de peligro
        printf("\x1b[31m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
        printf("\x1b[31m║                  ¡ENEMIGO INESPERADO APARECE!                ║\x1b[0m\n");
        printf("\x1b[31m╠══════════════════════════════════════════════════════════════╣\x1b[0m\n");
        printf("\x1b[31m║        ¡Prepárate para la batalla, valiente aventurero!      ║\x1b[0m\n");
        printf("\x1b[31m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
    } else if (combate_disenio == 1) {
        // Diseño 4: Alerta máxima
        printf("\x1b[31m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
        printf("\x1b[31m║                    ¡PELIGRO! ¡PELIGRO!                       ║\x1b[0m\n");
        printf("\x1b[31m╠══════════════════════════════════════════════════════════════╣\x1b[0m\n");
        printf("\x1b[31m║               ¡Un enemigo bloquea tu avance!                 ║\x1b[0m\n");
        printf("\x1b[31m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
    } else {
        // Diseño 5: Estilo épico
        printf("\x1b[31m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
        printf("\x1b[31m║              ¡UNA BATALLA COMENZARA, PREPARATE!              ║\x1b[0m\n");
        printf("\x1b[31m╠══════════════════════════════════════════════════════════════╣\x1b[0m\n");
        printf("\x1b[31m║            ¡Demuestra tu valor contra el enemigo!            ║\x1b[0m\n");
        printf("\x1b[31m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
    }
}

void ui_combat_banner(const char* player_name, const char* enemy_name) {
    printf("\x1b[35m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[35m║ ¡COMBATE INICIADO! %10s vs %-27s ║\x1b[0m\n", player_name, enemy_name);
    printf("\x1b[35m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
}

void ui_lore_zero(Map* lore_map, int tipo) {
    clearScreen();
    printf("\n\x1b[36m▒█▀▀▀ ░▀░ █▀▀▄ █▀▀█ █░░ ▒█▀▀█ █░░█ █▀▀ █▀▀ ▀▀█▀▀   ▄█░\x1b[0m\n");
    printf("\x1b[36m▒█▀▀▀ ▀█▀ █░░█ █▄▄█ █░░ ▒█░▒█ █░░█ █▀▀ ▀▀█ ░░█░░   ░█░ \x1b[0m\n");
    printf("\x1b[36m▒█░░░ ▀▀▀ ▀░░▀ ▀░░▀ ▀▀▀ ░▀▀█▄ ░▀▀▀ ▀▀▀ ▀▀▀ ░░▀░░   ▄█▄\x1b[0m\n\n");
    puts("           __...--~~~~~-._   _.-~~~~~--...__");
    puts("         //      Aqui     `V'      Tu       \\\\");
    puts("        //     Empieza     |     Aventura    \\\\");
    puts("       //__...--~~~~~~-._  |  _.-~~~~~~--...__\\\\");
    puts("      //__.....----~~~~._\\ | /_.~~~~----.....__\\\\");
    puts("     ====================\\\\|//====================");
    puts("                         `---`");
    printf("\x1b[36m╔─────────────────────────────────────────────────────╗\x1b[0m\n");
    printf("  ");
    // Obtener el texto de lore correspondiente al tipo (ej: tipo -1 para portada)
    MapPair* pair = map_search(lore_map, &tipo);
    const char* lore_inicial = NULL;
    if (pair && pair->value) {
        List* lista = (List*)pair->value;
        lore_inicial = list_first(lista);
    }
    print_lore_text_animated_wrapped(lore_inicial ? lore_inicial : "¡Bienvenido a la aventura RPG!", 45, 18);
    printf("\x1b[36m╚─────────────────────────────────────────────────────╝\x1b[0m\n");
    waitForKeyPress();
}

void ui_lore_event(const char* lore) {
    printf("\x1b[35m╔──────────────────────────────────────────────────────────────╗\x1b[0m\n");
    printf("  ");
    print_lore_text_animated_wrapped(lore, 54, 18); // 18 ms por caracter
    printf("\x1b[35m╚──────────────────────────────────────────────────────────────╝\x1b[0m\n");
}

void ui_shop_welcome(int gold) {
    printf("\033[1;35m╔════════════════════════════════════════════════════════════╗\n");
    printf("║ Bienvenido a la tienda! Tienes \033[1;33m%-5d de oro\033[1;35m                ║\n", gold);
    printf("╚════════════════════════════════════════════════════════════╝\n\033[0m");
}

void ui_shop_items(Map* itemMap) {
    const int ancho = 82;
    printf("\033[1;36m╔");
    for (int i = 0; i < ancho - 2; i++) printf("═");
    printf("╗\033[0m\n");
    printf("   \033[1;36m%-*s\033[0m\n", ancho - 3, "Items disponibles:");
    MapPair* pair = map_first(itemMap);
    if (!pair) {
        printf("   \033[1;31m(No hay ítems en venta en este momento.)\033[0m\n");
    } else {
        while (pair) {
            Item* item = (Item*)pair->value;
            int id = *(int*)pair->key;
            printf("   [\033[1;33m%d\033[0m] \033[1;37m%-20s\033[0m (\033[1;34m%-6s\033[0m) - Costo: \033[1;33m%-4d oro\033[0m. ",
                   id, item->name, item->rarity, item->price);
            if (item->type == 1) {
                printf("\033[1;31mDaño: %-3d.\033[0m", item->damage);
            } else if (item->type == 2) {
                printf("\033[1;32mDefensa: %-3d.\033[0m", item->defense);
            } else if (item->type == 3) {
                if (item->heal > 0) printf("\033[1;32mCura: %d HP. \033[0m", item->heal);
                if (item->damage > 0) printf("\033[1;31mDaño Boost: +%d Atk \033[0m", item->damage);
                if (item->defense > 0) printf("\033[1;32mDefensa Boost: +%d Def \033[0m", item->defense);
                if (item->damage > 0 || item->defense > 0) printf("por %d turnos. ", item->effectDuration);
            }
            printf("\n");
            pair = map_next(itemMap);
        }
    }
    printf("\033[1;36m╚");
    for (int i = 0; i < ancho - 2; i++) printf("═");
    printf("╝\033[0m\n");
}

void ui_shop_menu(bool hay_items) {
    if (hay_items) {
        printf("\033[1;36m╔════════════════════════════════════════════════════════════╗\n");
        printf("║                  ¿Qué deseas hacer?                        ║\n");
        printf("╟────────────────────────────────────────────────────────────╢\n");
        printf("║ \033[1;32m1. Comprar Item\033[1;36m                                            ║\n");
        printf("║ \033[1;31m2. Salir de la tienda\033[1;36m                                      ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n");
        printf("\033[0mTu eleccion: ");
    }
    else {
        printf("\033[1;36m╔════════════════════════════════════════════════════════════╗\n");
        printf("║                  No hay ítems disponibles.                 ║\n");
        printf("╠════════════════════════════════════════════════════════════╣\n");
        printf("║ \033[1;31m1. Salir de la tienda\033[1;36m                                      ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n");
        printf("\033[0mTu eleccion: ");
    }
}

void ui_shop_buy(int gold) {
    printf("\033[1;32m¡Compra exitosa!\033[0m\n");
    waitForKeyPress();
    clearScreen();
    printf("\x1b[33mTienes %d oro restante.\x1b[0m\n", gold);
    printf("\x1b[90m──────────────────────────────────────────────────────────────\x1b[0m\n");
}

void ui_msg_error(const char* msg) {
    printf("\033[1;31m%s\033[0m\n", msg);
}

// === FUNCIONES DEL BOSS FINAL ===

void ui_boss_dialogue() {
    const char* frases[] = {
        "\x1b[\x1b[40m\x1b[31m  ??? : Así que tú eres el héroe que ha llegado hasta aquí...   \x1b[0m",
        "\x1b[\x1b[40m\x1b[31m  ??? : No tienes idea del poder al que te enfrentas.           \x1b[0m",
        "\x1b[\x1b[40m\x1b[31m  ??? : ¡Prepárate para ser devorado por la oscuridad!          \x1b[0m"
    };
    int num = sizeof(frases)/sizeof(frases[0]);
    int skip = 0;
    printf("\x1b[\x1b[40m\x1b[31m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    for (int i = 0; i < num; i++) {
        if (!skip && _kbhit()) {
            int ch = _getch();
            if (ch == 13) skip = 1;
        }
        print_lore_text_animated_wrapped(frases[i], 85, 18);
        if (!skip) skip = ui_sleep_skip(900);
    }
    printf("\x1b[\x1b[40m\x1b[31m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
    if (!skip) ui_sleep_skip(700);
}

void ui_boss_alert() {
    const char* mensajes[] = {
        "\x1b[91m  ¡Una presencia abrumadora se siente cerca...!\x1b[0m",
        "\x1b[91m  El aire se vuelve denso y oscuro.\x1b[0m",
        "\x1b[91m  ¡Tus instintos te gritan que te prepares para lo peor!\x1b[0m",
        "\x1b[91m  Algo gigantesco se aproxima...\x1b[0m"
    };
    int num = sizeof(mensajes)/sizeof(mensajes[0]);
    int skip = 0;
    printf("\x1b[31m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    for (int i = 0; i < num; i++) {
        if (!skip && _kbhit()) {
            int ch = _getch();
            if (ch == 13) skip = 1;
        }
        print_lore_text_animated_wrapped(mensajes[i], 62, 18);
        if (!skip) skip = ui_sleep_skip(700);
    }
    printf("\x1b[31m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
    if (!skip) ui_sleep_skip(700);
    waitForPress("\x1b[1m\x1b[31mPresiona ENTER para presenciar tu final...\x1b[0m");
    clearScreen();
}

void ui_entrance_boss(const char* boss_name) {
    clearScreen();

    ui_boss_alert();

    printf("\x1b[\x1b[40m\x1b[31m");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⢟⢡⣿⣿⣿⣿⠶⡙⣿⡿⣿⣯⢛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⢝⣴⣿⠟⣿⣼⣭⣴⣶⣾⡇⡇⣿⣿⣷⣶⡏⡇⣟⣻⠿⣜⢭⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⣫⡝⣾⢞⣯⣷⣗⢻⣻⣿⣿⣿⣿⠓⢠⣿⣿⣿⡟⠍⢃⣿⣿⣿⡶⣸⡟⢿⣮⣽⣻⣿⣿⡟⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢻⢳⠟⣫⡥⡑⣹⣿⣿⠄⣣⣿⣿⣿⡇⣴⣿⣿⣿⣿⠇⣠⣿⣛⣿⣿⠃⢡⣼⣷⣟⠏⢷⢿⣿⣿⡙⢦⣟⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣴⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⠋⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣝⣾⡳⣕⢚⠗⡹⣰⢿⣿⣿⣾⣿⡿⠻⡡⣾⣮⣍⣻⣿⣿⣼⣿⣿⣿⣿⣇⣾⣿⣿⡿⠇⠰⣤⡻⣿⣿⣷⡈⢻⣷⣌⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣷⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡉⣉⠛⠙⠀⢀⡜⢁⣿⣿⣿⣿⣿⣿⠐⠇⢻⢋⣿⣿⣟⢿⣿⣿⢿⣿⣿⢿⣿⣍⠉⢑⣄⣴⣶⣿⣷⣝⠿⣿⣷⢠⢻⣿⣷⡌⣙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣻⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⡭⣢⣿⣿⣿⣇⣧⠘⣧⢊⣰⣷⣿⡿⠿⠟⠛⠹⠉⠁⠀⠈⣈⠄⠀⠀⠀⠀⠀⠀⠉⠀⠈⠑⢌⡻⣷⣦⣝⣿⣿⣿⣿⣾⣷⡈⢻⡇⡇⢿⣿⣿⡙⣷⣮⣙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣏⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢟⡽⣾⢏⣴⣿⣿⣿⣿⣿⣦⣄⣱⠾⡟⠉⠀⠀⠀⠐⠃⠆⠰⢿⣥⣆⣅⣄⠀⠀⠀⠀⠀⣀⣀⣀⡀⠀⠀⠈⣼⣿⣿⢸⣿⣿⣿⣿⣿⣷⡀⠑⣆⢹⣿⣿⣏⣈⠙⢿⣷⣬⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣣⣼⢟⣿⢇⣼⣿⣿⠿⢛⣿⣿⡿⣣⠄⠀⠀⠀⠀⠀⠀⢀⠘⠀⢀⠀⠻⣿⣿⣿⡄⠀⠀⢀⣣⣿⣿⣿⣧⡄⠀⢀⣿⣿⡟⣼⣿⣿⣿⣿⣿⣿⡇⠀⣼⢸⣿⣿⣿⢠⡇⡜⠿⣿⣿⡜⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣧⣹⣿⣿⣿⣿⣿⣿⣿⣿⡟⢹⣾⢟⣵⣿⢣⡿⣛⣭⡞⣱⣿⣿⠿⠳⡍⠀⠀⠀⠀⣤⣼⣶⡎⠀⠀⠈⠀⠐⢝⢿⣯⡀⠀⠁⣸⣿⣿⣿⣿⣿⡿⢀⣾⣿⣿⢳⣿⣿⣿⣿⣿⣿⢻⣿⠀⣛⠨⣿⣿⣿⡇⢳⠹⡄⢻⣿⣿⡸⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⡀⠀⣿⣿⡏⠗⣻⡽⢫⣾⠿⢋⣡⢾⣧⠹⡀⠀⠠⣤⣿⣿⡟⠁⡀⠁⠸⠀⠀⠀⢡⣿⣿⣶⠠⠧⠰⢰⢂⠮⠹⠴⠟⢿⣿⣿⣶⣝⣛⡛⢿⣿⣿⣼⣿⡇⢱⠀⣿⣿⣿⣿⠹⣆⢣⠘⣿⣿⣧⢲⣮⣙⢿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣟⣟⣿⠩⢻⣿⣿⣿⣇⣏⠃⢰⣿⣿⢰⣿⢟⣵⣿⢧⣺⡿⣻⣿⣿⣇⣏⠀⠀⣩⣹⣴⢂⠃⠅⠀⡄⡀⠀⢀⣬⣿⣿⣿⣿⣦⣃⠃⢎⠞⢎⣦⡫⢚⢿⣿⣿⣿⣿⣿⣶⡿⣿⣿⣿⣷⢸⡧⣿⣿⣿⣿⡇⣜⡈⡂⢿⣿⣿⡆⣿⣿⡎⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⡿⣟⣼⣿⣿⣿⣿⡟⣼⡹⠀⣾⣿⡏⣾⢿⠂⢠⣷⣿⢏⣾⣿⡿⡁⡤⠈⣈⣭⣶⣿⠋⠋⢀⢠⡀⠸⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⡠⣨⡈⠉⠐⢦⣀⡻⠿⠿⠟⣿⢻⣟⣈⠻⠿⠍⣿⣇⣿⣿⣿⣿⣿⢻⣧⢋⢸⣿⣿⣿⠸⣿⣿⡜⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⢻⣿⣿⣿⣿⣿⣿⢣⣿⢧⣀⣿⣿⢣⡇⡏⡌⢸⣿⡟⣿⣿⡟⣴⢡⡇⠀⠹⣿⣿⡟⢠⠠⢏⣘⡙⠄⣰⣮⠃⣽⡿⠁⣙⢿⢿⣿⣿⣷⣯⡆⠀⠀⡀⠀⠉⢀⣼⣿⣿⣿⣿⣿⢟⣡⣾⣿⠟⠁⠉⡭⣛⣿⡟⡿⢸⡇⣿⣿⣿⣇⢿⣿⣷⢹⣿⣿⣿⣿\n");
    printf("⣿⣿⡯⣿⣿⣿⣿⣿⡏⣾⡿⡌⢹⣿⣿⢸⣧⢡⠡⣿⣿⡝⣿⣿⣃⣸⡏⣡⠀⠉⠉⠈⠀⠈⢠⡇⢸⣿⡀⠿⠟⠁⣿⠇⠂⣿⡇⢀⣾⡁⢟⠹⠷⠀⠀⢠⣴⠠⣹⣿⣿⣿⣿⣿⣵⣿⣿⠟⠁⢀⡔⣬⣴⣿⠏⢣⣾⣿⣷⠿⠿⣿⣿⡸⣿⣿⣆⢿⣿⣿⣿\n");
    printf("⣿⣿⣹⣿⣿⣿⣿⣿⢸⣿⣿⡿⣿⣿⣿⣦⣄⠺⢴⣿⣿⢘⡛⢃⡀⢙⢿⣝⣦⣄⡀⠀⠄⡆⡈⣁⠐⣷⠀⢹⡇⢼⣿⡰⢿⡏⣡⣝⡛⡧⢼⡞⣶⢠⢀⢸⢣⣰⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⡔⣈⣼⣿⡿⣧⣾⣿⡿⠋⠁⠂⢀⣴⡾⠇⣿⣿⣿⡜⣿⣿⣿\n");
    printf("⣿⣿⡟⣿⣿⣿⣿⣧⢿⠩⢠⠀⠌⠻⢿⣿⣿⣿⣶⣬⣉⠃⢹⣭⣿⣯⣆⢿⣿⣿⠀⠤⠈⡤⠃⠸⡀⢋⡤⣉⣵⢪⣩⡔⢞⡅⡹⣿⡳⣿⠇⣬⡍⣘⡘⢇⢣⣿⣿⣿⣿⣿⣿⠹⠁⠀⠀⣀⣾⣿⣿⢟⢱⣿⠟⠋⠀⣔⣴⣶⡿⢏⣵⣦⢛⡿⠿⢷⢹⣿⣿\n");
    printf("⣿⣿⣷⠻⣿⣿⣿⣿⢱⡝⢦⣇⠐⡀⠀⠉⠻⢿⣿⣿⣿⣷⡤⣏⣿⣿⣸⠀⠂⠀⢀⡅⢠⢰⢱⠆⠇⣹⡷⡡⣾⢔⢕⣅⡿⢃⠁⡻⢁⣾⣤⡹⠀⢯⡏⣄⣿⣿⣿⣿⣿⣿⣿⠀⢶⡓⣾⣿⣿⣿⢫⣾⠞⠁⠀⣠⣾⣿⡿⣯⡵⠟⢃⠔⢉⣼⡴⢋⣾⣿⣿\n");
    printf("⣿⢳⣾⣿⣿⣿⣿⡇⡛⠁⠤⠙⢷⣦⡀⢄⠀⠀⠉⠻⣿⣿⢶⣻⣿⣿⣿⡆⠀⠀⠀⣂⠀⠉⠄⢀⡾⣮⣾⣾⣷⣷⣿⣾⣶⣭⣮⣒⠔⡩⢟⣞⣠⡟⣜⣾⣿⣿⣿⣿⣿⣿⡿⠰⠘⢿⣿⣿⣟⣵⣿⡟⠀⠨⣾⣿⡿⣫⠾⠋⡀⢀⣱⣶⠿⢫⢸⣿⣿⣿⣿\n");
    printf("⣿⢸⣿⣿⣿⣿⣿⣿⣎⠢⠀⠄⠀⠙⢿⣶⣅⢀⣁⠀⢤⠙⣲⣿⣿⣿⡟⣇⠀⠀⢈⣽⢰⣢⣽⣷⣿⡿⠿⠿⠿⡟⢛⡛⢿⢿⣿⣿⣿⣿⣾⣿⢏⣜⣾⣿⣿⣿⣿⣿⣿⣿⡷⠰⠶⠊⢿⣿⣾⣿⣿⡏⠒⠁⢙⣿⣿⣿⠀⣾⣧⣾⠟⣡⠚⢀⣾⣿⣿⣿⣿\n");
    printf("⣭⣾⣿⣿⣿⣿⣿⣿⣿⣷⣄⠂⡱⣄⠐⠙⢿⣿⣿⣦⠄⣰⣿⣿⣿⣿⣿⡹⡀⠀⠈⠑⡱⠟⢉⠑⠈⠐⠁⠀⠁⠁⠀⠉⠈⠀⠉⠙⠹⠻⡿⡣⣪⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠠⢀⢤⣾⣿⣿⣿⣿⡆⣉⠙⣾⣿⣿⡏⢆⡘⢫⠑⣷⠟⣴⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣜⢾⡗⣼⡇⠙⠻⠏⡰⣿⣽⣿⣿⣿⣿⣷⣣⠀⠀⠀⢘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣪⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣎⢳⣀⣾⣿⣿⣿⣿⣿⣥⣀⣽⣿⣿⣿⣧⢨⣱⣿⣧⢡⣾⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢱⣿⠁⠀⠀⣴⡿⣻⣿⣿⣿⣿⣿⣿⣷⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣼⣿⣿⣿⣿⣿⠿⠿⠿⠿⣿⣿⣿⣅⣱⣿⣿⣿⡎⠿⠿⠿⣿⣿⣿⣟⣻\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣾⡇⠀⢀⢪⣡⢶⣯⣿⣿⣿⣿⣿⣿⣿⣿⣾⣥⣄⣀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⣶⣿⣿⡟⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠟⣋⣭⣴⣶⣶⣾⠿⠿⠷⠶⠮⢍⣙⣫⣭⣽⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣿⢈⠁⢆⣹⢾⣷⡿⣉⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠏⢉⣰⣾⣿⣿⢿⡏⠉⠀⠀⠆⣉⣱⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("\x1b[0m\n");
    
    ui_boss_dialogue();
    waitForPress("\x1b[1m\x1b[31mPresiona ENTER para derrotarlo...\x1b[0m");
}

void ui_boss_phase2() {
    const char* frases[] = {
        "\x1b[\x1b[40m\x1b[31m  ??? : !Tu no puedes DERROTARME!.                              \x1b[0m",
        "\x1b[\x1b[40m\x1b[31m  ??? : No eres nada para mi.                                   \x1b[0m",
    };
    int num = sizeof(frases)/sizeof(frases[0]);
    int skip = 0;
    printf("\x1b[\x1b[40m\x1b[31m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    for (int i = 0; i < num; i++) {
        if (!skip && _kbhit()) {
            int ch = _getch();
            if (ch == 13) skip = 1;
        }
        print_lore_text_animated_wrapped(frases[i], 85, 18);
        if (!skip) skip = ui_sleep_skip(700);
    }
    printf("\x1b[\x1b[40m\x1b[31m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
    if (!skip) ui_sleep_skip(700);
    waitForPress("\x1b[1m\x1b[31mPresiona ENTER...\x1b[0m");
    clearScreen();

    printf("\x1b[\x1b[40m\x1b[31m");
    printf("⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣿⣿⣿⣿⣿⣿⣛⡛⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣹⣽⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣷⣦⣌⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣯⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⡹⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⣴⣿⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣌⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⣾⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣿⣿⡬⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣿⣿⡈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠟⣿⣉⣭⣭⣭⡿⣿⣻⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⣿⡏⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣿⣿⣧⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⣿⣿⣿⡿⢋⣤⢶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢹⣷⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠛⠻⠿⠿⢿⣿⣿⣟⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⣿⣿⠏⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⡏⢹⣿⣿⣿⡿⠟⠛⠛⠿⣿⣿⣿⣿⣿⠀⠐⠛⠛⠃⠀⢢⠀⢹⣿⡟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⣿⡏⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣹⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⢸⡟⣿⠀⣿⡿⠋⠀⠂⠀⠀⠀⠹⣿⡖⣿⣿⠀⠀⠀⠀⠀⠀⢸⠿⠀⣿⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⡏⢠⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⢳⣻⣶⡟⠀⠀⠀⠀⠀⢸⠃⠀⣿⠧⠛⢿⣄⡀⠀⠀⣀⢀⠾⠀⢸⣿⣶⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⠁⠋⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠹⣻⡇⠀⠀⠀⠀⠀⠘⠀⣰⡏⠀⠀⠀⠻⣿⣶⣤⣉⣉⣠⣴⣿⣿⣿⢁⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⡇⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠱⢾⡄⠀⠀⠀⠀⠀⣠⣿⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⡍⢡⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⠀⢰⠋⠉⠀⠀⠀⠀⠈⣿⣿⣿⡿⠿⢿⣿⣿⣿⡿⣡⣿⡟⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⢾⣿⣶⣀⣀⣶⣿⣿⣿⣦⣀⣤⢦⣤⣿⣿⣿⣿⣿⠟⢋⡿⢇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⡿⠃⡄⠀⠀⠀⠰⠀⠀⣠⡯⣽⡛⠀⠀⡀⠈⠻⣿⡧⣾⠏⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡌⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣿⠃⢸⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⡇⠸⣿⣦⡀⠀⣀⣠⣾⠟⠃⢿⣧⠀⠀⠁⠘⠀⠘⣇⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⡀⠘⢿⡿⣿⣿⣿⣿⣿⣿⠻⣿⣿⣿⡟⢃⣡⡧⠀⣾⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⣿⣿⣿⣿⣿⡶⢈⢛⣿⣿⣿⡿⠋⢀⡆⢸⣿⡀⠀⠦⠄⠀⣸⡇⣴⣿⣿⣿⣿⣿⣿⣿⣿⣛⣿⣷⣶⣷⣶⣾⣍⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠀⠈⠓⠿⡿⣿⡟⣻⢩⣯⣽⣷⠙⠃⠈⠁⢠⠴⡞⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢀⠸⣿⣿⣿⣿⠃⡼⢻⣿⣿⣟⣣⣀⡈⠁⢸⣿⣿⣿⣶⣾⢯⣿⢻⣿⣿⣿⣿⣿⣿⣿⢳⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡌⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠁⠑⡓⠛⠃⠉⣈⠉⠀⠀⠀⠀⠀⣀⣾⣾⡐⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⠸⠆⢻⣿⣿⡟⢰⣷⠀⠪⢝⡻⢿⣿⣿⣿⣿⣿⣿⢿⣩⡷⢂⣼⣿⣿⣿⣿⣿⣿⡟⠉⠋⠁⠈⢿⣿⠃⠀⠈⠙⢿⣿⣿⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣀⠀⠀⢳⣀⠀⡀⢀⠀⣀⣠⣖⢺⣟⣛⢸⣿⠁⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⠀⠀⢸⣿⣿⣧⠘⣿⣇⢀⠀⠁⠘⠐⠗⠾⠿⠿⠧⣼⣿⠇⣾⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⣠⣀⣀⣹⣷⡀⠀⠀⠀⠀⢻⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠐⣍⣧⣽⣬⣧⣼⣿⣿⣿⣿⣿⡿⠟⠀⡛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⢸⢃⣸⣿⣿⣿⣧⠸⣿⣿⣤⣀⣆⠠⢠⠤⠤⣤⣶⣼⡟⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⡌⡹⠋⠉⠽⠿⣿⣿⡄⠺⠣⠀⣾⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠹⣾⣿⣿⣿⣿⣿⣿⣿⠟⠋⠀⣠⡞⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⠘⣸⣿⣿⣿⣿⣿⣆⠻⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⢉⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡁⠀⠀⠀⠀⠈⠙⠃⠀⣇⡐⠃⣼⣿⣿⣿⣿⢿⣷⣦⣍⣻⡛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⡯⣝⣿⣿⣷⣶⣶⠛⣿⣿⣧⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣿⣟⣻⣟⠛⠛⠿\n");
    printf("⢰⣿⣿⣿⣿⣿⣿⣿⣷⠀⢩⣟⡛⠿⠿⠛⢉⣠⡔⠒⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⡄⢠⠀⠀⠀⠀⢸⠟⠉⠈⣿⣿⣿⣿⠇⣘⣻⣻⣿⢻⣿⣷⡿⠿⡛⢿⣟⣿⣿⣿⡿⣛⣻⣿⡇⠉⠀⠀⠉⠁⢠⣿⡏⢹⣿⣷⣾⣿⣍⢻⣿⣿⣿⣿⣿⡿⢿⣿⣿⣿⣿⣿⣷\n");
    printf("⢨⣭⣉⣿⡿⠟⠋⠐⠺⠂⣿⣤⣏⢙⣿⣿⣿⠛⠃⠀⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⠁⠈⠀⠀⠀⢠⡾⢶⠋⡀⢹⣿⣿⣏⣿⣿⣿⣿⣿⣉⡁⠹⣿⡌⣿⣿⡿⠉⠉⠀⣀⣀⡀⠈⠁⠨⠀⠀⠀⠀⠊⠙⢃⠈⠍⠉⣿⣿⡿⠟⠛⠛⠛⢉⣉⣭⣿⣿⣿⡆⢉⠉⠁\n");
    printf("⠈⠻⢿⣟⠁⠀⠀⠀⠀⠒⠈⠙⠻⠿⣿⣿⣿⠏⠉⠉⠑⢶⣦⡉⢻⣿⣿⣿⣿⡿⠿⠿⣿⣿⡀⠀⠀⠃⢀⣾⡏⠉⠙⠀⠈⣿⣿⣇⣹⣿⣿⣿⣿⣏⠀⠂⢸⣿⣿⣼⠀⠀⠀⠀⠀⠠⠄⠀⠀⠀⣀⣀⣀⡀⠂⢀⣩⣴⣶⠿⠛⠉⠀⢠⣤⡄⠯⣾⣿⣿⣿⣿⣿⠇⠀⠻ \n");
    printf("⠀⠀⣀⠙⣿⣶⣤⣀⡈⢀⣿⣿⣶⣶⣤⣴⣾⠀⠀⠀⠀⠀⣻⣿⣤⣿⣷⣶⣿⣿⣿⣷⣷⣦⣥⠆⣠⣾⣿⠟⠓⠀⠀⡀⠀⠈⠍⠛⢉⣿⣿⣿⣿⣿⡆⠀⣶⡻⣿⡿⠙⢻⣿⣶⣿⣶⣶⣶⣤⣾⣿⣿⣿⣿⣿⠿⠛⡉⠀⠀⠀⠊⢀⣼⣿⠻⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⡀\n");
    printf("⢀⠀⢻⣇⠙⣽⠛⠿⢿⣾⣿⣿⣿⣿⣿⡏⢀⣤⣴⣾⣿⣿⣿⣿⣿⡛⠋⠉⠉⠉⠉⠛⣿⣿⣿⡁⢈⠉⢁⣀⠀⠀⠘⠒⢂⡀⠄⠉⢹⣿⠿⠟⠛⠁⠀⠀⢻⣷⡆⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⠹⠿⠿⠛⠉⠀⠐⠋⠡⠀⡀⠀⣠⣾⡟⢻⣷⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀⠁\n");
    printf("⠀⠀⠈⠛⣷⣤⣀⡀⣾⣿⣿⣿⣿⣿⣿⣧⠸⡿⠟⠛⠉⠁⢠⣿⣿⠃⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⠀⠈⣿⣿⡷⠉⢙⣩⠅⢠⣤⣤⣿⣿⠆⣠⠀⠀⡀⠀⠀⠹⣷⡀⠙⢿⣿⣿⣿⣿⣿⠏⢁⡀⠀⠀⠀⠀⠀⠀⢀⣐⣉⣴⣾⣿⠟⠀⠀⣿⣿⣧⣿⣿⣿⣫⠟⢻⣷⠀⠀\n");
    printf("⠀⠀⠀⠀⢌⠙⠻⣿⡏⠁⣀⠀⠙⠛⠋⠁⠀⠀⠀⢀⣠⣴⣿⣿⠃⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣃⣀⣀⠙⠟⢀⣀⡀⠀⣀⡸⢿⣿⣿⠇⣼⣷⣇⣰⠀⠀⠀⠀⠻⢷⡀⠈⢿⣿⠛⠛⠁⢠⣾⣿⣿⣿⡿⠻⡿⠿⠟⠛⣉⠙⢉⣀⣀⠀⢸⣿⡗⢸⣿⣿⡿⠃⡄⣿⣿⣇⠈\n");
    printf("⢸⣦⣀⠀⠀⠀⠀⠈⣷⣿⣿⣿⣷⣦⢿⣿⣶⡿⠿⠟⠛⠋⠉⢳⣧⠀⠀⠀⡠⠖⠋⣿⡿⣿⣿⠈⢍⠻⣿⠇⠘⠀⠈⠉⠀⢠⣾⣿⡏⠀⣿⣿⡿⢿⣀⡀⠀⣀⣠⣤⣧⣤⡀⠀⠀⠀⠐⠟⠛⠉⠁⠀⠀⠀⠂⠘⠓⠚⢁⠔⠀⠀⠈⢁⣼⣿⠟⡿⣿⡏⢀⣾⣇⢸⣿⣿⡄\n");
    printf("⠈⢿⠿⢿⣦⣤⡀⠺⠛⠿⢿⣿⡿⠋⠀⣀⠘⠉⠀⠀⠀⠀⠀⣸⣿⠀⢀⠎⣠⣾⢰⣿⡽⣿⣿⠀⠤⠠⣤⡆⠀⠲⠶⢶⣶⣾⣿⣿⣥⣞⡁⢹⣷⣈⣿⣷⣿⣿⣿⣿⣿⣿⣿⣷⣶⡦⠀⢠⡶⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠐⢃⣸⣶⣿⣿⣯⡿⣱⣿⡇⢼⣿⣿⢸⣿⣿⡷\n");
    printf("⠐⠢⠀⠀⠉⠉⠛⣷⣦⣄⣸⣥⣀⣠⣦⣤⣤⣤⣤⣶⣦⣾⣿⡿⠃⢀⡌⢰⣿⡿⢸⣿⡇⣿⣿⣇⣀⣀⠈⠉⠀⣀⡀⠀⢠⣿⣿⡏⢨⢹⣷⢸⣿⣿⡌⠙⠿⠿⢿⣿⣏⣿⣿⣿⣧⠀⡆⢸⣿⣄⠀⠀⠀⠀⠈⢓⣀⣤⣴⣾⣿⣿⡿⣿⠟⠁⠀⢹⣿⣿⡌⣿⣿⢸⣿⣿⡇\n");
    printf("\x1b[0m\n");

    const char* msg = "\x1b[\x1b[40m\x1b[31m El devorador, ruge y sus subditos renacen. ¡Su ataque aumenta!\x1b[0m\n";
    print_lore_text_animated_wrapped(msg, 85, 18);
    waitForPress("\x1b[1m\x1b[31mQuieres continuar? Presiona ENTER\x1b[0m");
    clearScreen();
}

void ui_boss_phase3() {
    const char* frases[] = {
        "\x1b[\x1b[40m\x1b[31m  ??? : !Ahora si, no tienes escapatoria!.                      \x1b[0m"
    };
    int num = sizeof(frases)/sizeof(frases[0]);
    int skip = 0;
    printf("\x1b[\x1b[40m\x1b[31m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    for (int i = 0; i < num; i++) {
        if (!skip && _kbhit()) {
            int ch = _getch();
            if (ch == 13) skip = 1;
        }
        print_lore_text_animated_wrapped(frases[i], 85, 18);
        if (!skip) skip = ui_sleep_skip(700);
    }
    printf("\x1b[\x1b[40m\x1b[31m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
    if (!skip) ui_sleep_skip(700);

    waitForPress("\x1b[1m\x1b[31mPresiona ENTER...\x1b[0m");
    clearScreen();
    
    const char* msg = "\x1b[\x1b[40m\x1b[31mTe ves a ti mismo, exhausto. Te rendiras?                   \x1b[0m";
    print_lore_text_animated_wrapped(msg, 85, 18);

    printf("\x1b[\x1b[40m\x1b[31m");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀                                   \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⢶⡦⢦⣤⣀                               \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣇⣸⣧⣾⣯⣻⢶⡀                             \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣷⣻⣿⣭⠟⠛⠻⢾⣸⣿⡀⠀                           \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡍⠈⠉⠀⠀⠀⠀⢉⣾⢹⠀⠀                          \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣄⠀⠀⠀⣀⣶⡿⠃⢻⣆⢀⡀⠀                        \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⠶⠶⠾⠋⠒⠀⣀⣾⣿⣿⣿⣆⠀⢀⣀⡀⠀                   \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠿⣷⣶⣶⠁⠀⠴⣱⣿⢟⣿⡿⠟⠉⠉⠉⠉⢶⣦⡀⠀                \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⠛⣿⢿⣧⣴⡾⣋⣷⠿⣻⠃⢀⣤⣶⢶⢿⣿⢿⣿⣄⠀               \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢴⡛⣿⠀⠈⣧⣿⣯⠞⠉⣡⣶⣿⣷⡟⢿⠉⢮⡀⠙⣆⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠷⣜⢷⠀⣿⣽⡟⢀⣶⣋⣽⣿⣿⣷⣌⢷⣀⣿⡿⡿⢿⢿⡹⡀⠀⠀⠀⠀⠀⠀        \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣄⠈⠻⣿⣿⣿⠦⢿⣭⣶⣿⣹⣿⣿⡟⠻⣿⢻⡹⡝⣌⢶⢷⡹⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣷⣾⠋⣧⠉⣏⡻⠋⢙⣿⣿⣿⣿⣿⡀⣿⠆⢹⡙⡝⣎⢦⢷⡽⠆⠀⠀⠀⠀⠀⠀⠀     \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣉⣿⣿⣿⠀⣿⢀⠟⠀⡴⠏⡇⢈⣿⣿⣿⣷⠸⡎⠆⢻⣙⣼⣾⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡏⠉⣿⣿⣇⡿⠋⣠⠞⡇⠀⣇⠀⠻⣻⣿⣿⣷⡿⠾⠛⠋⠉⠹⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣦⣀⣿⣿⣯⣄⡶⢹⠀⣿⠀⣿⠀⠀⢙⣿⣿⣿⣦⡀⠀⣀⡠⠖⠻⣿⡆⠀⣠⣶⢦⡀⠀⠀⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⠋⣿⣿⣿⣿⣆⠈⡄⢹⠀⢸⠀⣤⣾⣿⣿⣿⣿⣷⣉⣁⡀⠀⠀⣹⣿⡾⠟⣧⢿⣇⠀⠀⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣸⣿⣿⡿⣿⣿⣷⣄⡀⣀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⣠⠞⠁⢸⣿⡆⠀⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⢁⣟⣿⣿⣷⣿⣿⣍⠉⠛⠟⠿⠿⠿⠿⠿⠛⠿⣿⣿⣿⣿⣻⡿⠋⢀⡞⠁⠀⠀⢸⣿⣧⠀⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠻⣿⡏⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣶⣶⣶⣶⣶⢿⡟⣻⣿⣿⠟⠁⡰⠋⠀⠀⠀⠀⢸⣿⣿⡄⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣆⠙⠷⠿⣿⢏⣿⣿⣛⡷⢾⣇⣀⠼⣏⠉⠉⡉⠁⠀⠀⣿⣼⡿⠃⣠⠞⠁⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣏⠈⠳⣄⣿⣿⣷⣿⠋⡻⢿⣷⣿⣁⣀⣼⣤⣶⣶⣶⠶⣿⣿⠟⢀⡼⠁⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⢣⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠯⣕⣶⣾⣿⡻⣿⡿⣤⠃⣴⣿⠋⣿⢿⢸⣉⣉⣉⣀⣴⣿⠃⣠⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣼⠀    \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡏⢠⣌⠙⣿⣿⣿⣿⣤⣯⣶⣿⣏⣀⣿⠈⠈⡉⠙⢿⣿⡿⠁⣠⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣯⣼⣿⡄    \n");
    printf("\x1b[0m\n");

    waitForPress("\x1b[1m\x1b[31mPresiona ENTER...\x1b[0m");
    clearScreen();
}

void ui_boss_victory() {
    clearScreen();
    
    // ASCII Art de victoria
    printf("\x1b[40m\x1b[96m");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢀⣀⣠⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡜⣩⡟⠉⠀⠀⢈⠉⠲⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⣱⠋⠁⠀⣀⠀⣼⣀⠀⠃⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣳⠏⠀⠀⢰⣿⣤⣏⣿⡶⡇⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⠃⠀⠀⠀⠈⣿⣿⣿⡿⣰⣧⣤⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⠆       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣄⠰⣆⠀⠀⠀⣀⡴⠋⠀⠀⠀⠀⢀⣀⣿⣷⣾⣟⣃⡹⠋⠀⠀⠀⠀⠀⠀⠀⢀⣠⣼⠟⠋⠁⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡹⣟⠺⢭⡔⠋⠉⠀⠀⠀⠀⠀⢀⣼⣯⣿⡿⣅⣤⣿⣤⣄⠀⠀⠀⠀⠀⢀⣴⣾⠟⠃⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢾⡽⢦⣄⣀⠀⠀⠀⠀⢰⣾⣿⡿⣿⣯⣽⡷⣿⣽⣿⣿⢧⡄⠀⣠⣴⡿⠟⠁⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠒⣶⣤⣀⣀⣀⡀⠾⣿⣿⣿⢶⣬⣯⣿⣿⣿⣿⣿⣿⣤⣾⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠀⠀⢠⣿⣿⣦⣝⡋⣿⡌⠘⢿⣿⣿⣿⣿⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣧⣉⢳⣿⣽⣤⣽⣿⢿⠟⢿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣶⣾⣯⣿⣿⣿⣿⣿⣿⣯⣸⠀⡾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡄⠀⠀⠀⢸⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡾⣺⣅⠀⠀⢀⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾⠇⢹⣻⣷⣀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⣤⣿⣿⣿⣽⡟⠋⣿⣿⣟⣻⢻⣿⣻⣿⡿⡍⠿⠛⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⠀⣠⣾⡿⣿⣿⣿⡿⢿⣦⣿⠋⢛⠿⢾⢹⠿⣿⣿⣮⣦⡀⠙⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾⠁⣠⡾⠟⣹⣾⣿⣟⣿⡿⠟⠛⣿⡷⠿⣿⠾⠷⠶⠟⣿⣻⣿⣿⣧⡈⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⠀⢀⡴⢋⣤⣾⢋⣴⣾⢟⢃⡾⠛⠁⠀⠀⢸⡟⢻⡷⡏⠀⠀⠀⠀⢻⡟⠛⡋⠹⣝⠊⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⠀⠀⣴⠏⣴⠿⣿⣾⠿⢻⣷⠶⠋⠀⠀⠀⠀⠀⢸⡇⣰⣻⣤⠤⠤⠤⠤⣀⣳⠀⣇⢀⣼⣦⠘⣧⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⠀⠀⣠⠞⠁⣼⣿⠿⣛⣅⡼⠋⠁⢠⡀⠀⠀⠀⠀⠀⢸⢡⣿⠟⠛⢙⣿⣖⣤⣌⠉⣧⣟⠉⠀⣹⣴⣾⡆⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⠀⢀⡼⠁⢀⡴⠋⢉⡿⠟⠁⠀⠀⠀⣘⣷⠦⣄⣀⣀⣤⣿⣿⣥⠖⠋⠁⠀⠀⠉⠓⠯⣿⣿⣤⣴⣿⣼⠛⠁⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⠀⣴⢟⣡⠖⢩⣴⠖⠉⠀⠀⠀⠀⠀⠘⠿⣾⠤⠴⠒⣉⣽⣿⣿⣄⡀⣀⣀⣀⣀⣀⢀⣀⢨⣿⠿⣅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf("      ⣴⣿⠿⠷⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠺⠿⢿⣿⣿⣿⣿⡟⠿⠟⠿⠛⠛⠿⢿⣿⡿⠿⠿⠿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀       \n");
    printf(" ╔═════════════════════════════════════════════════════════╗ \n");
    printf(" ║    Has derrotado al Devorador de Mundos y salvado       ║ \n");
    printf(" ║           el reino de la oscuridad eterna.              ║ \n");
    printf(" ║                                                         ║ \n");
    printf(" ║              ¡Eres el héroe definitivo!                 ║ \n");
    printf(" ╚═════════════════════════════════════════════════════════╝ \n");
    printf("\x1b[0m\n");
    
    printf("\x1b[93m¡JUEGO COMPLETADO!\x1b[0m\n\n");
    waitForPress("Presione ENTER para finalizar...");
}

void ui_boss_defeat(const char* boss_name) {
    clearScreen();

    const char* frases[] = {
        "\x1b[\x1b[40m\x1b[31m  ??? : Eres debil...                   \x1b[0m"
    };
    int num = sizeof(frases)/sizeof(frases[0]);
    int skip = 0;
    printf("\x1b[\x1b[40m\x1b[31m╔══════════════════════════════════════╗\x1b[0m\n");
    for (int i = 0; i < num; i++) {
        if (!skip && _kbhit()) {
            int ch = _getch();
            if (ch == 13) skip = 1;
        }
        print_lore_text_animated_wrapped(frases[i], 85, 18);
        if (!skip) skip = ui_sleep_skip(700);
    }
    printf("\x1b[\x1b[40m\x1b[31m╚══════════════════════════════════════╝\x1b[0m\n");
    if (!skip) ui_sleep_skip(700);

    printf("\x1b[\x1b[40m\x1b[31m");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣯⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⢺⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡏⣧⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢶⣿⣋⣟⠭⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣭⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡏⢮⣳⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡿⣦⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⠢⣽⣅⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡆⢤⣿⡇⠀⠀⠀⠀⣸⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⠸⣞⡇⠀⠀⠀⠀⡏⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡄⣿⣷⠀⠀⠀⠀⢻⡈⢣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⢸⣿⡆⠀⠀⠀⠀⢳⣬⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡈⣿⣧⠀⠀⢠⡄⣸⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⢹⣿⡀⠀⢸⢧⠟⢹⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠸⣿⡇⣠⠋⢾⣾⢸⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡖⠀⠸⣿⣶⣿⣷⡏⢰⡿⢿⠏⣸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⣴⢋⣿⣿⣿⠇⡟⠁⣏⠀⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡞⣏⢦⠇⢸⡿⢿⠋⢀⣤⣀⡘⢦⡟⢸⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⠃⢀⣴⡆⠀⠀⠈⣹⣿⡷⠆⠀⣧⠈⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠜⢁⡴⠋⡀⠙⢄⠀⣰⣿⣟⠓⠀⠀⢉⣴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⢰⡏⡠⠊⢀⡴⣇⠀⢀⡞⠉⠛⠀⡀⢀⣄⣩⠌⠙⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⢣⠶⠖⠊⢀⣈⠉⣹⡷⢀⣴⡯⠔⣛⡵⠁⣠⡏⠸⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⢹⡿⢿⠟⠀⣰⡞⠉⣿⡷⠇⠃⣠⢴⣶⣾⡋⢀⡴⣽⠁⠀⠘⣏⣀⢰⣆⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⣠⣶⣶⣅⣠⣶⠀⠒⠟⢁⡴⠋⠀⠀⠀⢹⣿⣿⡋⣧⢸⡇⡏⣀⣀⠀⠙⣿⣉⠙⢤⡄⠀⠀⠀\n");
    printf("⠀⠀⣠⣴⣺⢿⣿⣿⡛⠛⠿⠿⣯⣷⡲⣶⣟⣻⡀⠀⣠⣿⣿⣖⣸⣨⣿⠿⠛⣻⣿⣶⣾⣾⠇⠀⠻⣄⠀⠀\n");
    printf("⠀⣾⢟⠿⠿⢶⣮⡙⢏⢢⡀⢠⡌⣿⣿⡿⠟⡿⢳⣼⣿⣿⣿⣾⣿⣧⣤⣤⣤⣿⣿⣭⣿⠁⠀⠀⣀⣈⣧⠀\n");
    printf("⢺⣥⢿⠾⠿⠿⠿⡿⠚⢋⣠⠯⣿⢉⢉⠻⠾⠛⢿⣿⠻⠿⢛⢋⣤⣯⣭⠽⠶⣾⣻⢿⣻⢿⠶⢛⣻⡿⢽⠄\n");
    printf("\x1b[0m\n");
    
    printf("\x1b[90m¿Tendrás lo necesario para intentarlo de nuevo?\x1b[0m\n");
    waitForPress("\n\x1b[1m\x1b[31mPresiona ENTER...\x1b[0m");
}

void ui_bonus() {
    printf("\x1b[40m\x1b[93m");
    print_lore_text_animated_wrapped("Has encontrado un Cofre!      ", 80, 18);
    printf("\x1b[0m\n");

    ui_sleep_skip(500);

    printf("\x1b[40m\x1b[93m");
    printf("⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⣠⣾⣿⠿⢋⣡⣴⣶⣶⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⢀⣾⣿⡟⢁⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⠆⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⢀⣾⣿⠏⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢁⣴⣾⣿⠟⠋⣀⣤⣤⡀⠀⠀\n");
    printf("⠀⣼⣿⡟⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁⣴⣿⣿⠟⢁⣴⣿⣿⣿⣿⣿⡄⠀\n");
    printf("⠀⣉⠛⠃⠸⢿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢀⣾⣿⡿⠁⣰⣿⣿⣿⣿⣿⣿⣿⡧⠀\n");
    printf("⠀⣿⣿⡆⢠⣤⠀⣉⠙⠛⠿⢿⣿⣿⠀⣾⣿⣿⠃⣼⣿⣿⣿⣿⠿⠛⢉⣡⣤⠀\n");
    printf("⠀⣿⣿⡇⢸⣿⠀⣿⠿⠷⣶⠀⣈⡁⠀⠻⠿⡟⠀⠿⠟⠋⣁⣠⣴⣾⣿⣿⣿⠀\n");
    printf("⠀⣿⣿⡇⢸⣿⠀⣿⡄⢠⣿⠀⣿⡇⠀⣶⣦⡄⠀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⠀\n");
    printf("⠀⣿⣿⡇⢸⣿⠀⠿⢧⣾⣿⠀⣿⡇⠀⣿⣿⡇⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀\n");
    printf("⠀⣿⣿⡇⢸⣿⣷⣶⣤⣄⣉⠀⣿⡇⠀⣿⣿⡇⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀\n");
    printf("⠀⠉⠛⠃⢸⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣿⣿⡇⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠉⠙⠛⠿⣿⣿⣿⡇⠀⣿⣿⡇⠀⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠀⠻⢿⡇⠀⣿⠿⠛⠉⠀⠀⠀⠀⠀⠀⠀\n");
    printf("\x1b[0m\n");

    printf("\x1b[40m\x1b[93m");
    printf("Abriendo el tesoro");
    ui_wait_dots();
    printf("\x1b[0m\n");
}

void ui_shop() {
    printf("\x1b[40m\x1b[93m");
    print_lore_text_animated_wrapped("A la lejania ves una tienda                       ", 80, 18);
    printf("\x1b[0m\n");

    ui_sleep_skip(500);

    printf("\x1b[40m\x1b[93m");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡀⠙⠳⢶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠛⣷⠰⡀⣦⠬⡙⠻⢷⣦⣄⣀⣠⣤⣶⣿⣏⡼⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡏⠀⢹⣇⢳⡙⣟⠲⡂⢳⢹⡿⣯⣍⣻⣿⣿⣋⣀⡈⢷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠀⠀⠀⢻⣆⢻⡙⡗⢳⡀⢳⣷⡀⠈⠉⢹⠀⡾⢿⣭⡹⡿⢶⣦⣤⣀⣰⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠁⠀⠀⠀⠀⢿⣆⢻⠻⡖⢳⡀⢻⢿⣄⠀⠘⠀⡧⣾⢼⠀⡏⣇⠱⡤⡈⢛⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⣴⡟⠀⠀SHOP ⠀⢻⣎⢻⠛⣖⠻⡆⢧⠙⠧⣤⣄⣷⣿⣾⠀⠿⣍⣯⡽⡝⢏⢾⣷⣀⣠⡆⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⣼⠏⠀⠀⣤⣤⣼⡤⠤⡄⠀⠹⣧⠳⡘⢷⠻⡖⠳⡀⢠⠉⠉⠉⢙⣷⣤⣼⠶⢷⠷⠾⠟⠛⣿⠟⣧⡀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⢠⡾⠁⠀⠀⠀⢹⡆⢸⡀⠀⡇⠀⠀⠈⢷⡙⢞⠳⡚⢖⠛⡄⠃⣀⣴⢟⣿⣿⢛⡶⢳⢔⡰⣢⡾⠁⠀⠈⢷⡄⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠰⢫⠀⠀⠀⠀⠀⢼⡧⢼⡇⠰⡇⠀⠀⠀⠀⠹⣦⣄⣁⣈⣃⣤⢞⣯⣗⡿⢻⠼⣯⣿⣿⣿⠿⣫⢤⠖⠲⣤⡈⠻⣦⡀⠀⠀⠀\n");
    printf("⠀⠀⠀⢀⣿⣷⠀⠀⠀⠀⢸⠇⠘⡇⣀⣿⠀⠀⠀⠀⢀⠀⠈⠉⠉⠳⡶⣯⣬⣥⣬⣭⡿⠼⠟⠋⢁⠚⢣⣼⣼⡥⠊⣿⠀⠈⠛⢦⠀⠀\n");
    printf("⠀⠀⣠⡾⠛⢿⡄⠀⠀⠀⠸⠿⠿⠿⠛⠋⠀⠀⠀⠀⢸⠀⣤⣤⡀⠀⢳⠀⢦⢬⣧⡀⠀⠀⡇⠀⢈⣉⣙⣛⣛⠒⠚⠋⠀⠀⡄⠀⠀⠀\n");
    printf("⠀⣾⠋⠁⠀⠸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⣧⣾⡇⠀⢸⠀⢸⢬⣦⡇⠀⠀⡆⠀⠀⡄⠀⢹⠉⠉⢹⠀⠀⢠⠇⠀⠀⠀\n");
    printf("⣴⠟⠀⠀⠀⣴⣿⠀⠀⠀⠀⣶⠚⢻⠉⠉⡇⠀⠀⠀⢸⠀⡇⣿⡇⠀⢸⠀⢸⢸⢈⡇⠀⠀⡇⠀⠀⡇⠀⢸⠀⠀⢸⠀⠀⢸⠀⠀⠀⠀\n");
    printf("⠓⠢⣶⡿⡿⠋⢹⡆⠀⠀⠀⢻⣇⣸⣄⣤⡇⠀⠀⠀⢸⢀⣧⣿⡇⠀⢸⡀⣾⣸⣹⡇⠀⠀⡇⠀⢠⡇⠀⢸⠀⠀⡾⠀⠀⣿⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⢹⠦⠼⡇⠀⠀⠀⢸⡏⢹⡇⠀⣧⠀⠀⠀⢸⢸⣿⣿⡇⠀⢸⢃⣿⣼⣼⠃⠀⠀⣷⠀⢸⠀⠈⠿⠉⠀⡇⠀⠀⣿⣤⡀⠀⠀\n");
    printf("⠀⠀⢀⡾⠉⠀⠀⢹⠀⠀⠀⢸⣧⣴⣷⣲⡿⠀⠀⠀⢸⠈⠉⠉⠁⠀⣸⠀⠉⠉⠉⠀⠀⢀⡇⠀⡸⠀⠀⡆⠀⢀⡇⠀⢀⡏⠸⠥⣄⠀\n");
    printf("⠀⠀⠋⠀⠀⠀⠀⠘⡄⠀⠀⢈⣛⣋⣉⣁⣀⣀⣠⠤⠬⠤⠤⠤⠤⠤⠷⠤⠤⠤⠤⠤⠤⢼⣧⣤⣥⣤⣀⣀⣀⣈⣀⠀⠸⠃⠀⠀⠈⣿\n");
    printf("⠀⠀⠀⠀⠠⠤⠖⢒⣃⣉⠭⠭⡽⢿⣛⣿⣛⣯⠭⠥⠤⠤⠤⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢉⣷⠀⠀⠀⠈⠉⠹⢭⣙⠛⠓⠶⠦⠤⣬\n");
    printf("⠀⠀⠀⠀⡒⣫⠉⠡⠤⠒⢒⣊⣉⡩⠥⠥⠄⢀⣀⣀⣀⣀⣤⣤⠤⠤⠤⠤⠤⠴⠶⠶⠒⠚⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠉⠲⡄⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠤⠖⠒⠊⢉⣁⣤⡤⠶⠶⠛⠛⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣶⠇⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⣠⠶⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⡴⠶⠖⠛⠛⠉⠉⠉⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠻⠶⠤⠤⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡞⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠦⢤⣄⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠙⠓⠲⢄⣀⠀\n");
    printf("\x1b[0m\n");

    printf("\x1b[40m\x1b[93m");
    printf("Vas camino hacia ella");
    ui_wait_dots();
    printf("\x1b[0m\n");
    waitForKeyPress();
    clearScreen();
}