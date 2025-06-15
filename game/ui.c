#include <stdio.h>

#include "data_types.h"
#include "ui.h"
#include "../tdas/extra.h"
#include "player.h"
#include <windows.h>
void welcome_zero(Player* player) {
    printf("--- INICIO DEL JUEGO ---\n");
            printf("¡Bienvenido, %s! Tu aventura comienza ahora.\n", player->name);
            printf("Explora el mapa y enfrenta los desafíos que te esperan.\n");
            
            waitForKeyPress(); // Esperar a que el jugador presione una tecla antes de continuar
            clearScreen();
            printf("\n--- ESCENARIO 0 ---\n");
            printf("Estas en: El inicio del todo\n");
// Esperar medio segundo para dar tiempo a leer el mensaje
            printf("...\n");

            printf("\n");
            printf("\n");
            printf("¡Es peligroso que vayas solo! Toma esto.\n");
}

// Esta función espera medio segundo y muestra tres puntos de carga, para darle mas color a la carga del juego. xdd
void wait_three_points() {
    printf("Cargando");
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

