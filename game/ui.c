#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>

#include "data_types.h"
#include "ui.h"
#include "../tdas/extra.h"
#include "player.h"
#include "../tdas/extra.h"
#include "../tdas/map.h"

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
    printf("\x1b[36m║\x1b[0m Arma equipada: %-24s (+%-2d Atk)%12s\x1b[36m║\x1b[0m\n", player->equippedWeapon.name, player->equippedWeapon.damage, "");
    printf("\x1b[36m║\x1b[0m Armadura equipada: %-20s (+%2d Def)%12s\x1b[36m║\x1b[0m\n", player->equippedArmor.name, player->equippedArmor.defense, "");
    printf("\x1b[36m╟──────────────────────────────────────────────────────────────╢\x1b[0m\n");
    printf("\x1b[36m║\x1b[0m Slots disponibles de inventario: %-2d %25s\x1b[36m║\x1b[0m\n", INVENTORY_SLOTS - player->inventoryCount, "");
    printf("\x1b[36m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
}

void display_combat_text() {
    int combate_disenio = rand() % 3;
    
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
        Sleep(500);
        clearScreen();
        Sleep(500); 
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

void display_mercader_text(){

}

void display_bonus_text(){
    
}

void display_combat_banner(const char* player_name, const char* enemy_name) {
    printf("\x1b[35m╔══════════════════════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[35m║ ¡COMBATE INICIADO! %10s vs %-27s ║\x1b[0m\n", player_name, enemy_name);
    printf("\x1b[35m╚══════════════════════════════════════════════════════════════╝\x1b[0m\n");
}

void display_intro_lore_and_ascii(const char* lore_inicial) {
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
    print_lore_text_animated_wrapped(lore_inicial, 45, 18);
    printf("\x1b[36m╚─────────────────────────────────────────────────────╝\x1b[0m\n");
    waitForKeyPress();
}

// Imprime texto animado tipo videojuego antiguo, con salto de línea automático cada 'line_width' caracteres
void print_lore_text_animated_wrapped(const char* texto, int line_width, int delay_ms) {
    int len = strlen(texto);
    int col = 0;
    for (int i = 0; i < len; i++) {
        putchar(texto[i]);
        fflush(stdout);
        Sleep(delay_ms);
        col++;
        if (col >= line_width && texto[i] == ' ') {
            putchar('\n');
            printf("  ");
            col = 0;
        }
    }
    putchar('\n');
}

void display_lore_event(const char* lore) {
    Sleep(1000);
    printf("\x1b[35m╔──────────────────────────────────────────────────────────────╗\x1b[0m\n");
    printf("  ");
    print_lore_text_animated_wrapped(lore, 54, 18); // 18 ms por caracter
    printf("\x1b[35m╚──────────────────────────────────────────────────────────────╝\x1b[0m\n");
}

// --- Lógica de LoreTracker (implementación) ---

void init_lore_tracker(LoreTracker* tracker, int tipo, int cantidad) {
    tracker->tipo = tipo;
    tracker->cantidad = cantidad;
    tracker->usados = calloc(cantidad, sizeof(int));
}

void free_lore_tracker(LoreTracker* tracker) {
    free(tracker->usados);
}

int get_random_unused_lore(LoreTracker* tracker) {
    int disponibles = 0;
    for (int i = 0; i < tracker->cantidad; i++) if (!tracker->usados[i]) disponibles++;
    if (disponibles == 0) return -1;
    int elegido = rand() % disponibles;
    for (int i = 0, c = 0; i < tracker->cantidad; i++) {
        if (!tracker->usados[i]) {
            if (c == elegido) return i;
            c++;
        }
    }
    return -1;
}

void mark_lore_used(LoreTracker* tracker, int idx) {
    tracker->usados[idx] = 1;
}

// --- Funciones de impresión de tienda ---
void display_merchant_appearance(int merchantItemCount, int maxDifficulty) {
    printf("\033[1;33m"); // Amarillo brillante
    printf("╔═════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║\033[1;36m  ¡Un mercader misterioso ha aparecido con \033[1;32m%d\033[1;36m ítem%s de dificultad hasta \033[1;31m%d\033[1;36m!  \033[1;33m  ║\n",
           merchantItemCount, merchantItemCount == 1 ? "" : "s", maxDifficulty);
    printf("╚═════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\033[0m"); // Resetear colores
}

void display_shop_welcome(int gold) {
    printf("\033[1;35m╔════════════════════════════════════════════════════════════╗\n");
    printf("║                  Bienvenido a la tienda!                   ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║                  Tienes \033[1;33m%d\033[1;35m oro.                           ║\n", gold);
    printf("╚════════════════════════════════════════════════════════════╝\n\033[0m");
}

void display_shop_items(Map* itemMap) {
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

void display_shop_item_detail(Item* item, int id) {
    printf("║   [\033[1;33m%d\033[0m] \033[1;37m%-20s\033[0m (\033[1;34m%-6s\033[0m) - Costo: \033[1;33m%-4d oro\033[0m. ",
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
    printf("%*s║\n", 60 - (int)strlen(item->name) - 35, ""); // Ajusta el padding
}

void display_shop_menu() {
    printf("\033[1;36m╔════════════════════════════════════════════════════════════╗\n");
    printf("║                  ¿Qué deseas hacer?                        ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ \033[1;32m1. Comprar Item\033[1;36m                                            ║\n");
    printf("║ \033[1;31m2. Salir de la tienda\033[1;36m                                      ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\033[0mTu eleccion: ");
}

void display_shop_buy_success(int gold) {
    printf("\033[1;32m¡Compra exitosa! Tienes %d oro restante.\033[0m\n", gold);
}

void display_shop_exit() {
    printf("\033[1;35mGracias por tu visita! Vuelve pronto.\033[0m\n");
}

void display_shop_invalid_option() {
    printf("\033[1;31mOpcion invalida. Por favor, elige 1 o 2.\033[0m\n");
}

void display_shop_error(const char* msg) {
    printf("\033[1;31m%s\033[0m\n", msg);
}

void display_shop_input(const char* msg) {
    printf("\033[1;36m%s\033[0m", msg);
}

// === FUNCIONES DEL BOSS FINAL ===

void display_final_boss_entrance(const char* boss_name) {
    clearScreen();
    printf("\x1b[31m");
    printf("╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                           ║\n");
    printf("║                          ¡BOSS FINAL APARECE!                             ║\n");
    printf("║                                                                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n");
    printf("\x1b[0m\n");
    
    // ASCII Art del boss
    printf("\x1b[91m");
    printf("                            ░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("                          ░░██████████████████████░░\n");
    printf("                        ░░████████████████████████░░\n");
    printf("                      ░░██████████████████████████░░\n");
    printf("                      ░░██████████████████████████░░\n");
    printf("                      ░░██████████████████████████░░\n");
    printf("                      ░░██████░░░░░░░░░░░░██████░░\n");
    printf("                      ░░██████░░  ████  ░░██████░░\n");
    printf("                      ░░██████░░  ████  ░░██████░░\n");
    printf("                      ░░██████░░░░░░░░░░░░██████░░\n");
    printf("                      ░░██████████████████████████░░\n");
    printf("                      ░░██████████████████████████░░\n");
    printf("                      ░░██████████░░░░██████████░░\n");
    printf("                      ░░██████████░░░░██████████░░\n");
    printf("                      ░░██████████████████████████░░\n");
    printf("                        ░░████████████████████░░\n");
    printf("                          ░░██████████████░░\n");
    printf("\x1b[0m\n");
    
    printf("\x1b[91m");
    printf("    ╔══════════════════════════════════════════════════════════════════╗\n");
    printf("    ║   \"¡Has llegado hasta aquí, mortal! Pero tu viaje termina aquí.\" ║\n");
    printf("    ║              \"¡Prepárate para enfrentar tu destino!\"             ║\n");
    printf("    ╚══════════════════════════════════════════════════════════════════╝\n");
    printf("\x1b[0m\n");
    
    printf("La oscuridad se intensifica");
    wait_three_points();
    printf("\x1b[31m¡EL COMBATE FINAL COMIENZA!\x1b[0m\n\n");
    waitForKeyPress();
}

void display_final_boss_victory() {
    clearScreen();
    printf("\x1b[93m");
    printf("╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                           ║\n");
    printf("║                             ¡VICTORIA ÉPICA!                              ║\n");
    printf("║                                                                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n");
    printf("\x1b[0m\n");
    
    // ASCII Art de victoria
    printf("\x1b[93m");
    printf("                              🏆 CAMPEÓN 🏆\n\n");
    printf("                           ░░░░░░░░░░░░░░░░░░░░\n");
    printf("                         ░░██████████████████░░\n");
    printf("                       ░░████████████████████░░\n");
    printf("                       ░░████████████████████░░\n");
    printf("                       ░░████░░░░░░░░░░░░████░░\n");
    printf("                       ░░████░░ ██████ ░░████░░\n");
    printf("                       ░░████░░ ██████ ░░████░░\n");
    printf("                       ░░████░░░░░░░░░░░░████░░\n");
    printf("                       ░░████████████████████░░\n");
    printf("                       ░░████████░░░░████████░░\n");
    printf("                       ░░████████░░░░████████░░\n");
    printf("                       ░░████████████████████░░\n");
    printf("                         ░░██████████████░░\n");
    printf("                           ░░████████░░\n");
    printf("\x1b[0m\n");
    
    printf("\x1b[96m");
    printf("    ╔══════════════════════════════════════════════════════════════════╗\n");
    printf("    ║          Has derrotado al Devorador de Mundos y salvado          ║\n");
    printf("    ║                 el reino de la oscuridad eterna.                 ║\n");
    printf("    ║                                                                  ║\n");
    printf("    ║                    ¡Eres el héroe definitivo!                    ║\n");
    printf("    ╚══════════════════════════════════════════════════════════════════╝\n");
    printf("\x1b[0m\n");
    
    printf("Tu leyenda será recordada por siempre");
    wait_three_points();
    printf("\n\x1b[93m¡JUEGO COMPLETADO!\x1b[0m\n\n");
    waitForKeyPress();
}

void display_final_boss_defeat(const char* boss_name) {
    clearScreen();
    printf("\x1b[31m");
    printf("╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                             DERROTA FINAL                                 ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n");
    printf("\x1b[0m\n");
    
    printf("\x1b[91m");
    printf("    ╔══════════════════════════════════════════════════════════════════╗\n");
    printf("    ║          \"La oscuridad consume todo... incluso a ti.\"            ║\n");
    printf("    ║             El reino permanece en tinieblas eternas.             ║\n");
    printf("    ╚══════════════════════════════════════════════════════════════════╝\n");
    printf("\x1b[0m\n");
    
    printf("\x1b[90m¿Tendrás lo necesario para intentarlo de nuevo?\x1b[0m\n\n");
    waitForKeyPress();
}

int menu_gameover_retry() {
    printf("\n\x1b[41m═══════════════════════════════════════════════════════════════\x1b[0m\n");
    printf("\x1b[41m  ☠️  Has sido derrotado. ¿Qué deseas hacer?                \x1b[0m\n");
    printf("\x1b[41m═══════════════════════════════════════════════════════════════\x1b[0m\n");
    printf("  [1] Volver a jugar desde el inicio\n");
    printf("  [2] Salir del juego\n");
    printf("Tu elección: ");
    char input[10];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        int choice = atoi(input);
        if (choice == 1) return 1;
    }
    return 0;
}