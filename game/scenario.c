#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   
#include <stdbool.h>  
#include <time.h>     

#include "scenario.h"   
#include "data_types.h" 
#include "combat.h"     
#include "player.h"     
#include "shop.h"       
#include "../tdas/map.h" 
#include "../tdas/extra.h" 
#include "../tdas/queue.h"
#include "lore.h" 

// --- FUNCIONES DE LIBERACIÓN DE MEMORIA ---
#define NUM_EVENT_TYPES 4 
#define MAX_DIFFICULTY 3    

/**
 * Genera un enemigo aleatorio basado en la dificultad del escenario actual
 * @param currentScenarioDifficulty Nivel de dificultad del escenario (1-3)
 * @param enemy_array Array con todos los enemigos disponibles
 * @param numEnemies Número total de enemigos en el array
 * @return Puntero al enemigo generado o NULL si hay error
 */
Enemy* spawnRandomEnemy(int currentScenarioDifficulty, Enemy* enemy_array, int numEnemies) {
    // Validar parámetros de entrada
    if (enemy_array == NULL || numEnemies <= 0) {
        printf("Error: No hay enemigos disponibles para spawn.\n");
        return NULL;
    }
    
    // Asignar memoria para array temporal de enemigos filtrados
    Enemy* filteredEnemies = malloc(sizeof(Enemy) * numEnemies);
    if (filteredEnemies == NULL) {
        printf("Error: No se pudo asignar memoria para enemigos filtrados.\n");
        return NULL;
    }
    
    // Filtrar enemigos que coincidan con la dificultad actual
    int count = 0;
    for (int i = 0; i < numEnemies; i++) {
        if (enemy_array[i].difficulty == currentScenarioDifficulty) {
            filteredEnemies[count++] = enemy_array[i];
        }
    }
    
    // Verificar que se encontraron enemigos válidos
    if (count == 0) {
        printf("Error: No hay enemigos disponibles con la dificultad %d.\n", currentScenarioDifficulty);
        free(filteredEnemies);
        return NULL;
    }
    
    // Seleccionar un índice aleatorio de los enemigos filtrados
    int randomIndex = rand() % count;
    
    // Asignar memoria para el enemigo que será devuelto
    Enemy* spawnedEnemy = malloc(sizeof(Enemy));
    if (spawnedEnemy == NULL) {
        printf("Error: No se pudo asignar memoria para el enemigo spawn.\n");
        free(filteredEnemies);
        return NULL;
    }
    
    // Copiar los datos del enemigo seleccionado
    *spawnedEnemy = filteredEnemies[randomIndex];
    
    // Inicializar HP actual del enemigo (siempre con HP completo)
    if (currentScenarioDifficulty == 4) {
        // Para el boss final (dificultad 4), asegurar que tenga HP completo
        spawnedEnemy->currentHP = spawnedEnemy->HP;
    } else {
        // HP completo para todos los demás enemigos también
        spawnedEnemy->currentHP = spawnedEnemy->HP;
    }
    
    // Liberar memoria temporal del array filtrado
    free(filteredEnemies);
    return spawnedEnemy; 
}

void poblarGameMap(Queue* game_map, Scenario* escenarios, int numScenarios) {
    // Validar que todos los parámetros sean válidos
    if (!game_map || !escenarios || numScenarios <= 0) {
        fprintf(stderr, "Error: Parámetros inválidos para poblarGameMap\n");
        return;
    }

    // Inicializar semilla para números aleatorios
    srand(time(NULL));

    // Crear arrays temporales para clasificar escenarios por dificultad (máximo 10 por categoría)
    Scenario* dificultad1[10] = {NULL};
    Scenario* dificultad2[10] = {NULL}; 
    Scenario* dificultad3[10] = {NULL}; 
    int count1 = 0;  // Contador de escenarios de dificultad 1
    int count2 = 0;  // Contador de escenarios de dificultad 2
    int count3 = 0;  // Contador de escenarios de dificultad 3
    
    // Recorrer todos los escenarios y clasificarlos por dificultad
    for (int i = 0; i < numScenarios; i++) {
        // Validar que la dificultad esté en el rango válido (1-3)
        if (escenarios[i].difficulty < 1 || escenarios[i].difficulty > 3) {
            fprintf(stderr, "Advertencia: Escenario con dificultad inválida %d\n", 
                    escenarios[i].difficulty);
            continue;
        }

        // Agregar el escenario al array correspondiente según su dificultad
        switch (escenarios[i].difficulty) {
            case 1: dificultad1[count1++] = &escenarios[i]; break;
            case 2: dificultad2[count2++] = &escenarios[i]; break;
            case 3: dificultad3[count3++] = &escenarios[i]; break;
        }
    }

    // Agregar escenarios al mapa de juego en orden progresivo de dificultad (1 → 2 → 3)
    int pushed = 0;  // Contador de escenarios agregados exitosamente
    
    // Agregar un escenario aleatorio de dificultad 1 si hay disponibles
    if (count1 > 0) {
        Scenario* s = dificultad1[rand() % count1];
        queue_insert(game_map, s);
        pushed++;
    }
    
    // Agregar un escenario aleatorio de dificultad 2 si hay disponibles
    if (count2 > 0) {
        Scenario* s = dificultad2[rand() % count2];
        queue_insert(game_map, s);
        pushed++;
    }
    
    // Agregar un escenario aleatorio de dificultad 3 si hay disponibles
    if (count3 > 0) {
        Scenario* s = dificultad3[rand() % count3];
        queue_insert(game_map, s);
        pushed++;
    }

    // Verificar que se haya agregado al menos un escenario
    if (pushed == 0) {
        fprintf(stderr, "Error: No se pudo agregar ningún escenario al mapa\n");
    }
}

// --- Variables de control para eventos aleatorios ---
static int merchant_count = 0;
static int last_event_type = -1;
static int forced_merchant = 0; // Para forzar aparición de mercader
static int scenario_event_count = 0; // Cuenta eventos en el escenario

// --- Variable global para reinicio tras derrota ---
int gameover_retry_flag = 0;

static int choose_event(int *merchant_count, int last_event_type, int forced_merchant, int scenario_event_count) {
    // Si el mercader no ha salido 2 veces, forzamos su aparición (nunca dos veces seguidas)
    if (*merchant_count < 2 && last_event_type != 1) {
        // Forzar mercader cada 3 eventos si no ha salido suficiente
        if ((scenario_event_count % 3 == 2) || (forced_merchant < 2 && rand() % 4 == 0)) {
            return 1;
        }
    }
    // Probabilidades: 0-69 combate, 70-84 bonus, 85-99 lore
    int roll = rand() % 100;
    int event_type = -1;
    if (roll < 70) event_type = 0; // Combate
    else if (roll < 85) event_type = 2; // Bonus
    else event_type = 3; // Lore

    // Si el evento es igual al anterior y NO es combate, se elige otro
    if (event_type == last_event_type && event_type != 0) {
        if (*merchant_count < 2 && last_event_type != 1) return 1; // Mercader
        // Alternar entre bonus y lore si bonus/lore fue el anterior
        event_type = (event_type == 2) ? 3 : 2;
    }
    return event_type;
}

void scenario_manage_event(Player* player, Item* allItems, int numItems, Enemy* allEnemies, int numEnemies, Scenario *scenario, Map* lore_map, LoreTracker* tracker_ambiental, LoreTracker* tracker_profundo) {
    // Validar que todos los parámetros necesarios estén presentes
    if (player == NULL || allItems == NULL || numItems == 0 || allEnemies == NULL || numEnemies == 0) {
        printf("Error: Datos incompletos para gestionar evento.\n");
        return;
    }

    // Limpiar pantalla para mostrar el evento
    clearScreen();  

    // Obtener la dificultad del escenario actual y preparar variables de evento
    int currentScenarioDifficulty = scenario->difficulty;
    int event_type = -1;
    scenario_event_count++;  // Incrementar contador de eventos del escenario
    
    // Elegir tipo de evento usando la función de selección
    event_type = choose_event(&merchant_count, last_event_type, forced_merchant, scenario_event_count);

    // Aplicar límites y restricciones para el mercader
    if (event_type == 1) {
        // Verificar si el mercader ya apareció 2 veces o fue el último evento
        if (merchant_count >= 2 || last_event_type == 1) {
            // Elegir otro tipo de evento: priorizar combate, luego bonus/lore
            event_type = (rand() % 2) ? 0 : ((rand() % 2) ? 2 : 3);
        } else {
            // Permitir mercader e incrementar contadores
            merchant_count++;
            forced_merchant++;
        }
    }
    
    // Resetear contador de mercader forzado si no es mercader
    if (event_type != 1) forced_merchant = 0;
    
    // Controlar que el contador de mercader no exceda 2
    if (event_type != 1) merchant_count = (merchant_count > 2) ? 2 : merchant_count;

    // Evitar que se repita el mismo tipo de evento consecutivamente
    if (event_type == last_event_type) {
        if (event_type == 0) event_type = (rand() % 2) ? 2 : 3;  // Si es combate, cambiar a bonus/lore
        else event_type = 0;  // Si es otro tipo, cambiar a combate
    }
    last_event_type = event_type;  // Actualizar el último tipo de evento

    // --- Procesar el evento según su tipo ---

    if (event_type == 0) { // EVENTO DE COMBATE
        // Generar enemigo aleatorio apropiado para la dificultad
        Enemy* randomEnemy = spawnRandomEnemy(currentScenarioDifficulty, allEnemies, numEnemies);
        ui_combat_text();
        
        // Crear copia del enemigo para el combate
        Enemy combatEnemy = *randomEnemy;
        
        // Ejecutar el sistema de combate por turnos
        bool combatWon = combat_manage_turn(player, &combatEnemy);
        
        if (combatWon) {
            // Calcular recompensa de oro si ganó el combate
            int base = rand() % 51 + 50;  // Base aleatoria entre 50-100
            int multiplier = 133 + (rand() % 3) * 33;  // Multiplicador entre 133-199
            int won_gold = combatEnemy.difficulty * base * multiplier / 100;
            
            // Mostrar mensaje de victoria y recompensa
            printf("\x1b[33m═══════════════════════════════════════════════════════════════\x1b[0m\n");
            printf("\x1b[33m🏅  %s ha caído en combate. ¡Recompensa: %d oro!\x1b[0m\n", combatEnemy.name, won_gold);
            printf("\x1b[33m═══════════════════════════════════════════════════════════════\x1b[0m\n");
            player->gold += won_gold; 
        } else {
            // Si perdió el combate, configurar muerte del jugador
            player->currentHP = 0;
            
            // Mostrar menú de reinicio o salida
            if (ui_gameover_retry()) gameover_retry_flag = 1;
            if (!gameover_retry_flag) return; // Salir inmediatamente si elige no reiniciar
        }
        
        // Mostrar lore ambiental después del combate
        show_random_lore_no_repeat(lore_map, tracker_ambiental, 0);
        
    } else if (event_type == 1) { // EVENTO DE MERCADER
        // Mostrar encuentro con merchant
        ui_shop();
        
        // Inicializar inventario aleatorio del mercader
        Map* itemMap = shop_initialize_random_merchant(allItems, numItems, currentScenarioDifficulty, player);
        
        if (itemMap != NULL) {
            // Permitir al jugador interactuar con la tienda
            shop_interact(player, itemMap);
            map_destroy(itemMap);  // Limpiar memoria del inventario temporal
        } else {
            printf("El mercader no tenia nada que vender o hubo un error.\n");
        }
        
        // Mostrar lore ambiental (corto) después de la compra
        show_random_lore_no_repeat(lore_map, tracker_ambiental, 0);
        
    } else if (event_type == 2) { // EVENTO DE BONIFICACIÓN
        // Mostrar ecuentro con bonus
        ui_bonus();
        
        // Determinar tipo de bonificación: 40% oro, 30% stats, 30% item
        int bonus_type = rand() % 10;
        
        if (bonus_type < 4) { // BONIFICACIÓN DE ORO (40% probabilidad)
            int gold_found = (rand() % 100) + 50;  // Entre 50-149 oro
            player->gold += gold_found;
            printf("Encontraste \x1b[33m%d oro\x1b[0m!\n", gold_found);
            
        } else if (bonus_type < 7) { // BONIFICACIÓN DE ESTADÍSTICAS (30% probabilidad)
            int stat_choice = rand() % 2;  // Elegir entre ataque o defensa
            
            if (stat_choice == 0) {
                // Incrementar ataque del jugador
                int atk_boost = (rand() % 20) + 1;  // Entre 1-20 puntos
                player->attack += atk_boost;
                printf("Te sientes mas fuerte! \x1b[31mTu ataque aumento en %d\x1b[0m.\n", atk_boost);
            } else {
                // Incrementar defensa del jugador
                int def_boost = (rand() % 40) + 1;  // Entre 1-40 puntos
                player->defense += def_boost;
                printf("Tu piel se ha endurecido! \x1b[34mTu defensa aumento en %d\x1b[0m.\n", def_boost);
            }
            
        } else { // BONIFICACIÓN DE ÍTEM (30% probabilidad)
            if (numItems > 0) {
                // Seleccionar ítem aleatorio del catálogo
                Item randomItem = allItems[rand() % numItems];
                
                // Intentar agregarlo al inventario del jugador
                if (player_add_item_to_inventory(player, randomItem)) {
                    printf("Encontraste un %s!\n", randomItem.name);
                } 
            } else {
                printf("No se encontraron ítems para dar como bonificación.\n");
            }
        }
        
        // Mostrar lore ambiental
        show_random_lore_no_repeat(lore_map, tracker_ambiental, 0);
        waitForKeyPress();
        
    } else if (event_type == 3) { // EVENTO DE HISTORIA/LORE
        // Mostrar introducción del evento de memoria
        printf("Recuerdos vienen hacia ti");
        ui_wait_dots();
        clearScreen();
        
        // Mostrar lore profundo (más detallado que el ambiental)
        show_random_lore_no_repeat(lore_map, tracker_profundo, 1);
        waitForKeyPress();
    }
    
    // Indicar fin del evento
    printf("--- FIN DE EVENTO ---\n");
}

bool FINALBOSS(Player* player, Enemy* allEnemies, int numEnemies, Map* lore_map, LoreTracker* tracker_profundo) {
    // Validar que todos los parámetros sean válidos para el enfrentamiento final
    if (!player || !allEnemies || numEnemies <= 0) {
        printf("Error: Parámetros inválidos para el boss final.\n");
        return false;
    }

    // Buscar y generar el boss final con dificultad 4
    Enemy* finalBoss = spawnRandomEnemy(4, allEnemies, numEnemies);
    if (!finalBoss) {
        printf("Error: No se pudo encontrar el boss final.\n");
        return false;
    }

    // Mostrar la cinematica de entrada épica del boss final
    ui_entrance_boss(finalBoss->name);

    // Ejecutar el combate final usando el sistema especial para jefes
    bool victory = combat_final_boss(player, finalBoss);

    // Procesar el resultado del combate final
    if (victory) {
        // El jugador derrotó al boss final - VICTORIA ÉPICA
        ui_boss_victory();
        
        // Otorgar recompensas épicas por completar el juego
        int epic_gold = 5000;  // Recompensa fija de oro épica
        player->gold += epic_gold;
        player->enemiesDefeated++;  // Incrementar contador de enemigos derrotados
        
        // Mostrar tabla de recompensas épicas con formato especial
        printf("\x1b[93m╔═══════════════════════════════════════════════════════════════╗\x1b[0m\n");
        printf("\x1b[93m║                      RECOMPENSAS ÉPICAS                       ║\x1b[0m\n");
        printf("\x1b[93m╠═══════════════════════════════════════════════════════════════╣\x1b[0m\n");
        printf("\x1b[93m║  • Oro del Tesoro Final: %d                                 ║\x1b[0m\n", epic_gold);
        printf("\x1b[93m║  • Título: 'Devorador de Devoradores'                         ║\x1b[0m\n");
        printf("\x1b[93m║  • Leyenda Eterna: Tu nombre será recordado por siempre       ║\x1b[0m\n");
        printf("\x1b[93m╚═══════════════════════════════════════════════════════════════╝\x1b[0m\n");
        
        // Liberar memoria del boss derrotado
        free(finalBoss);
        
        // Limpiar pantalla y mostrar lore final épico
        clearScreen();
        show_random_lore_no_repeat(lore_map, tracker_profundo, 2);  // Tipo 2 = lore final
        return true;  // Retornar victoria
        
    } else {
        // El jugador fue derrotado por el boss final
        ui_boss_defeat(finalBoss->name);
        
        // Ofrecer opción de reintentar o salir del juego
        if (ui_gameover_retry()) gameover_retry_flag = 1;
        
        // Liberar memoria del boss
        free(finalBoss);
        return false;  // Retornar derrota
    }
}

/**
 * Muestra un fragmento de lore aleatorio sin repetir del tipo especificado
 * @param lore_map Mapa que contiene las listas de lore organizadas por tipo
 * @param tracker Tracker que mantiene registro de qué lore ya se ha mostrado
 * @param tipo Tipo de lore a mostrar (0=ambiental, 1=profundo, 2=final)
 */
void show_random_lore_no_repeat(Map* lore_map, LoreTracker* tracker, int tipo) {
    // Usar el tipo como clave para buscar en el mapa de lore
    int key = tipo;
    MapPair* pair = map_search(lore_map, &key);
    
    // Verificar que existe la lista de lore para este tipo
    if (!pair || !pair->value) return;
    
    // Obtener la lista de fragmentos de lore del tipo especificado
    List* lista = (List*)pair->value;
    int n = list_size(lista);
    
    // Si la lista está vacía, no hay nada que mostrar
    if (n == 0) return;
    
    // Obtener un índice aleatorio de lore que no se haya mostrado antes
    int idx = get_random_unused_lore(tracker);
    
    // Si ya se mostraron todos los fragmentos, reiniciar el tracker
    if (idx == -1) {
        // Liberar el tracker actual y reinicializarlo
        free_lore_tracker(tracker);
        init_lore_tracker(tracker, tipo, n);
        
        // Obtener un nuevo índice aleatorio después del reinicio
        idx = get_random_unused_lore(tracker);
    }
    
    // Navegar por la lista hasta llegar al fragmento seleccionado
    void* node = list_first(lista);
    for (int i = 0; i < idx; i++) node = list_next(lista);
    
    // Extraer el texto del fragmento de lore
    char* lore = (char*)node;
    
    // Marcar este fragmento como ya usado en el tracker
    mark_lore_used(tracker, idx);
    
    // Mostrar el fragmento de lore usando la interfaz de usuario
    ui_lore_event(lore);
}