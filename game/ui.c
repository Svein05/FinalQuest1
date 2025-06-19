#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#include "data_types.h"
#include "ui.h"
#include "../tdas/extra.h"
#include "player.h"
#include "../tdas/extra.h"

void display_title()
{
    printf("\x1b[36m╔════════════════════════════════════════════╗\x1b[0m\n");
    puts("\x1b[36m║\x1b[0m              FinalQuest 1                  \x1b[36m║\x1b[0m");
    printf("\x1b[36m╚════════════════════════════════════════════╝\x1b[0m\n\n");
}

void welcome_program(){
    printf("\x1b[36m╔══════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m            FinalQuest 1              \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╚══════════════════════════════════════╝\x1b[0m\n\n");

    choice_class_menu();
}

void welcome_zero(Player* player) {
    display_title();
    printf("\x1b[36m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m                      \x1b[33mINICIO DEL JUEGO\x1b[0m                        \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╟──────────────────────────────────────────────────────────────╢\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m ¡Bienvenido, \x1b[32m%-48s\x1b[0m\x1b[36m║\x1b[0m\n", player->name);
    printf("\x1b[36m║\x1b[0m - Explora los escenarios y enfrentate a enemigos aleatorios. \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m - Cada partida es diferente: Tu suerte sera vital.           \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m - ¡Tus decisiones influyen en tu destino!                    \x1b[36m║\x1b[0m\n");   
    printf("\x1b[36m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
    printf("\n\x1b[33m¡Prepárate para la aventura!\x1b[0m\n\n");
    waitForKeyPress();
}

// Esta función espera medio segundo y muestra tres puntos de carga, para darle mas color a la carga del juego. xdd
void wait_three_points() {
    for (int i = 0; i < 3; i++) {
        Sleep(1000); // Esperar medio segundo
        printf(".");
    }
    Sleep(1500); // Esperar medio segundo
    printf("\n");
}

void mostrarInstrucciones() {
    printf("Instrucciones:\n");
    printf("1. Mueve con comandos W/A/S/D\n");
    printf("2. Agarra ítems y sobrevive\n");
    printf("3. No mueras... idealmente.\n\n");
}

void mostrarGameOver() {
    printf("\nGAME OVER\n");
    printf("Mejor suerte para la próxima :(\n");
}

void mostrarVictoria() {
    printf("\n¡Ganaste!\n");
    printf("Eres el rey!!\n");
}

void choice_class_menu() {
    printf("\x1b[36m╔══════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m \x1b[33m     BIENVENIDO A TU AVENTURA        \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╟──────────────────────────────────────╢\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m \x1b[33mELIGE TU CLASE:\x1b[0m                      \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m 1. \x1b[32mGuerrero\x1b[0m                          \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m 2. \x1b[34mTanque\x1b[0m                            \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m 3. \x1b[31mAsesino\x1b[0m                           \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╚══════════════════════════════════════╝\x1b[0m\n");
}

void initializePlayer_menu(Player* player) {
    clearScreen();
    display_title();
    printf("\x1b[36m╔════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m        \x1b[33m¡Héroe creado exitosamente!\x1b[0m         \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╠════════════════════════════════════════════╣\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m Clase: %-36s\x1b[36m║\x1b[0m\n", player->name);
    printf("\x1b[36m║\x1b[0m Vida: \x1b[32m%-3d\x1b[0m   Ataque: \x1b[31m%-3d\x1b[0m   Defensa: \x1b[34m%-3d\x1b[0m     \x1b[36m║\x1b[0m\n", player->maxHP, player->attack, player->defense);
    printf("\x1b[36m║\x1b[0m Oro inicial: \x1b[33m%-30d\x1b[0m\x1b[36m║\x1b[0m\n", player->gold);
    printf("\x1b[36m╚════════════════════════════════════════════╝\x1b[0m\n");
}

// Imprime un escenario con bordes y formato uniforme
void display_scenario(const Scenario* scenario) {
    display_title();

    int width = 42; // igual que display_title
    printf("\x1b[36m╔════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m \x1b[33mESCENARIO: %-32s\x1b[36m║\x1b[0m\n", scenario->name);
    printf("\x1b[36m╟────────────────────────────────────────────╢\x1b[0m\n");
    print_scenario_description(scenario->description, width);
    printf("\x1b[36m╚════════════════════════════════════════════╝\x1b[0m\n");
}

// Formatea y muestra la descripción del escenario dentro de los bordes
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

void display_player_summary(const Player* player) {
    printf("\n\x1b[36m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m \x1b[33mRESUMEN DEL JUGADOR\x1b[0m%42s\x1b[36m║\x1b[0m\n", "");
    printf("\x1b[36m╟──────────────────────────────────────────────────────────────╢\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m Clase: %-20s Enemigos derrotados: %-4d        \x1b[36m║\x1b[0m\n", player->name, player->enemiesDefeated);
    printf("\x1b[36m║\x1b[0m Vida: \x1b[32m%3d/%-3d\x1b[0m  Atk: \x1b[31m%-3d\x1b[0m  Def: \x1b[34m%-3d\x1b[0m  Oro: \x1b[33m%-5d\x1b[0m                \x1b[36m║\x1b[0m\n", player->currentHP, player->maxHP, player->attack, player->defense, player->gold);
    printf("\x1b[36m║\x1b[0m Arma equipada: %-20s (+%-2d Atk)                \x1b[36m║\x1b[0m\n", player->equippedWeapon.name, player->equippedWeapon.damage);
    printf("\x1b[36m║\x1b[0m Armadura equipada: %-17s (+%-2d Def)              \x1b[36m║\x1b[0m\n", player->equippedArmor.name, player->equippedArmor.defense);
    printf("\x1b[36m╟──────────────────────────────────────────────────────────────╢\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m Slots disponibles de inventario: %-2d %25s\x1b[36m║\x1b[0m\n", INVENTORY_SLOTS - player->inventoryCount, "");
    printf("\x1b[36m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
}