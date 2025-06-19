#include "extra.h"
#include "windows.h"
#include <string.h> // Para strdup, strlen, strcpy, etc.
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>


#define MAX_LINE_LENGTH 4096
#define MAX_FIELDS      128

char** read_csv_line(FILE* file, char separator) {
    char line[MAX_LINE_LENGTH];
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
        return NULL;
    }

    // Eliminar saltos de línea
    line[strcspn(line, "\r\n")] = '\0';

    char** fields = malloc(MAX_FIELDS * sizeof(char*));
    if (!fields) return NULL;

    int field_count = 0;
    char* current = line;
    int in_quotes = 0;

    while (*current && field_count < MAX_FIELDS - 1) {
        // Saltar espacios iniciales
        while (*current == ' ') current++;

        // Determinar inicio del campo
        char* start = current;
        if (*current == '"') {
            in_quotes = 1;
            start = ++current;  // Saltar comilla inicial
        }

        // Buscar fin del campo
        char* end = current;
        while (*current) {
            if (in_quotes) {
                if (*current == '"' && *(current + 1) == '"') {
                    current += 2;  // Saltar comillas escapadas
                } else if (*current == '"') {
                    break;  // Fin de campo entrecomillado
                } else {
                    current++;
                }
            } else {
                if (*current == separator) break;
                current++;
            }
        }

        // Guardar posición final
        end = current;

        // Procesar fin de campo
        if (in_quotes && *current == '"') {
            *end = '\0';  // Terminar campo
            current++;    // Saltar comilla final
            if (*current == separator) current++;  // Saltar separador
            in_quotes = 0;
        } else if (!in_quotes && *current == separator) {
            *end = '\0';  // Terminar campo
            current++;    // Saltar separador
        } else if (*current == '\0') {
            *end = '\0';  // Último campo
        }

        // Copiar campo (manejando comillas escapadas)
        char* field = malloc(strlen(start) + 1);
        if (!field) {
            for (int i = 0; i < field_count; i++) free(fields[i]);
            free(fields);
            return NULL;
        }

        char* dest = field;
        char* src = start;
        while (*src) {
            if (*src == '"' && *(src + 1) == '"') {
                *dest++ = '"';
                src += 2;
            } else {
                *dest++ = *src++;
            }
        }
        *dest = '\0';

        fields[field_count++] = field;
    }

    fields[field_count] = NULL;
    return fields;
}

List *split_string(const char *str, const char *delim) {
  List *result = list_create();
  char *token = strtok((char *)str, delim);

  while (token != NULL) {
    // Eliminar espacios en blanco al inicio del token
    while (*token == ' ') {
      token++;
    }

    // Eliminar espacios en blanco al final del token
    char *end = token + strlen(token) - 1;
    while (*end == ' ' && end > token) {
      *end = '\0';
      end--;
    }

    // Copiar el token en un nuevo string
    char *new_token = strdup(token);

    // Agregar el nuevo string a la lista
    list_pushBack(result, new_token);

    // Obtener el siguiente token
    token = strtok(NULL, delim);
  }

  return result;
}

// Función para limpiar la pantalla
void clearScreen() {
    char* shell = getenv("SHELL");
    char* term = getenv("TERM");
    if ((shell && strstr(shell, "bash")) || (term && strstr(term, "xterm"))) {
        system("clear");
    } else {
        system("cls");
    }
}

void waitForKeyPress() {
    printf("Presione Enter para continuar...");
    while (getchar() != '\n');
}

// Animación de carga bonita para consola (barra de progreso)
void pretty_loading_animation(const char* mensaje) {
    int steps = 5;
    int percent[] = {20, 40, 60, 80, 100};
    for (int i = 1; i <= steps; i++) {
        printf("%s [", mensaje);
        for (int j = 1; j <= steps; j++) {
            if (j <= i) printf("■");
            else printf("□");
        }
        printf("] %d%%\r", percent[i-1]);
        fflush(stdout);
        Sleep(350); // velocidad de la animación
    }
    printf("%s [■■■■■] 100%%\n", mensaje);
    fflush(stdout);
}
