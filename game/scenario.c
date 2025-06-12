#include "escenario.h"
#include <stdlib.h>
#include <string.h>

Mapa* crearMapa(int id, const char* nombre, const char* descripcion, int dificultad) {
    Mapa* nuevo = (Mapa*)malloc(sizeof(Mapa));
    if (!nuevo) return NULL;

    nuevo->ID = id;
    nuevo->nombre = strdup(nombre);
    nuevo->descripcion = strdup(descripcion);
    nuevo->dificultad = dificultad;
    nuevo->enemigos = NULL;
    nuevo->next = NULL;
    return nuevo;
}

void insertarMapa(Mapa** lista, Mapa* nuevoMapa) {
    if (*lista == NULL) {
        *lista = nuevoMapa;
    } else {
        Mapa* temp = *lista;
        while (temp->next != NULL) temp = temp->next;
        temp->next = nuevoMapa;
    }
}

Mapa* cargarMapasDesdeCSV(FILE* archivo) {
    char** campos;
    Mapa* listaMapas = NULL;

    // Saltar header
    leer_linea_csv(archivo, ',');

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        int id = atoi(campos[0]);
        char* nombre = campos[1];
        char* descripcion = campos[2];
        int dificultad = atoi(campos[3]);

        Mapa* nuevoMapa = crearMapa(id, nombre, descripcion, dificultad);
        insertarMapa(&listaMapas, nuevoMapa);
    }
    return listaMapas;
}
