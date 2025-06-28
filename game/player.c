#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

#include "player.h"
#include "data_types.h"
#include "ui.h"
#include "data_loader.h"
#include "../tdas/map.h"
#include "../tdas/list.h"

/**
 * @brief Inicializa un Item como vacío (no equipado/no existente).
 * Esto es útil para los slots de equipo cuando no hay nada equipado.
 * @param item Puntero al Item a inicializar.
 */
static void initializeEmptyItem(Item* item) {
    item->id = ITEM_ID_EMPTY; // ID especial para ítems vacíos
    strncpy(item->name, "Ninguno", sizeof(item->name) - 1);
    item->name[sizeof(item->name) - 1] = '\0';
    item->type = 0; // Tipo 0 puede significar "ninguno"
    strncpy(item->rarity, "N/A", sizeof(item->rarity) - 1);
    item->rarity[sizeof(item->rarity) - 1] = '\0';
    item->damage = 0;
    item->defense = 0;
    item->heal = 0;
    item->price = 0;
    item->difficulty = 0;
    item->effectDuration = 0;
}

/**
 * Inicializa completamente la estructura del jugador con valores base y configuración inicial
 * @param player Puntero a la estructura Player a inicializar
 * @param name Nombre del jugador (se copia de forma segura)
 * @param hp Vida máxima y actual inicial del jugador
 * @param atk Valor de ataque base del jugador
 * @param def Valor de defensa base del jugador
 * @param gold Cantidad inicial de oro del jugador
 */
void initializePlayer(Player* player, const char* name, int hp, int atk, int def, int gold) {
    // Validar que el puntero del jugador no sea nulo
    if (player == NULL) {
        printf("Error: No se puede inicializar un jugador nulo.\n");
        return;
    }

    // Copiar el nombre del jugador de forma segura, asegurando terminación nula
    strncpy(player->name, name, sizeof(player->name) - 1);
    player->name[sizeof(player->name) - 1] = '\0';

    // Configurar estadísticas básicas del jugador
    player->maxHP = hp;    
    player->currentHP = hp;
    player->attack = atk;  
    player->defense = def; 
    player->gold = gold;
    player->inventoryCount = 0;

    // Inicializar slots de equipo como ítems vacíos (sin equipo equipado)
    initializeEmptyItem(&player->equippedWeapon);
    initializeEmptyItem(&player->equippedArmor);

    // Resetear todos los efectos temporales
    player->tempAttackBoost = 0;
    player->tempDefenseBoost = 0;
    player->attackBoostTurns = 0;
    player->defenseBoostTurns = 0;
    
    // Inicializar contador de logros
    player->enemiesDefeated = 0;

    // Limpiar todos los slots del inventario
    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        player->inventory[i].id = ITEM_ID_EMPTY;        // Marcar slot como vacío
        initializeEmptyItem(&player->inventory[i]);     // Limpiar completamente el slot
    }

    // Mostrar la inicialización del jugador en la interfaz
    ui_player_init(player);
}

/**
 * Remueve un ítem específico del inventario del jugador mediante su ID único
 * @param player Puntero al jugador del cual se removerá el ítem
 * @param item_id ID único del ítem a eliminar del inventario
 * @return true si el ítem fue encontrado y removido exitosamente, false si no se encontró
 */
bool player_remove_item_from_inventory(Player* player, int item_id) {
    // Validar parámetros de entrada (jugador válido e ID no vacío)
    if (player == NULL || item_id == ITEM_ID_EMPTY) return false;

    // Buscar el índice del ítem con el ID especificado
    int found_index = -1;
    for (int i = 0; i < player->inventoryCount; i++) {
        if (player->inventory[i].id == item_id) {
            found_index = i;  // Guardar la posición donde se encontró
            break;           // Salir del bucle al encontrar el ítem
        }
    }

    // Procesar la eliminación si se encontró el ítem
    if (found_index != -1) {
        // Compactar el inventario moviendo todos los ítems posteriores una posición hacia atrás
        for (int i = found_index; i < player->inventoryCount - 1; i++) {
            player->inventory[i] = player->inventory[i+1];  // Mover ítem siguiente a la posición actual
        }
        
        // Decrementar el contador total de ítems en el inventario
        player->inventoryCount--;
        return true;  // Eliminación exitosa
    }
    
    // El ítem con el ID especificado no se encontró en el inventario
    return false;
}

/**
 * @brief Equipa un arma al jugador, actualizando su ataque.
 * Si ya hay un arma equipada, la anterior va al inventario (si hay espacio).
 * @param player Puntero al jugador.
 * @param weapon El arma a equipar (se copia por valor).
 * @param from_inventory Indica si el arma viene del inventario (true) o es nueva (false).
 */
void player_equip_weapon(Player* player, Item weapon, bool from_inventory) {
    // Validar que el jugador no sea nulo y que el ítem sea realmente un arma (tipo 1)
    if (player == NULL || weapon.type != 1) {
        printf("Error: Arma inválida o jugador nulo.\n");
        return;
    }

    // Hacer una copia del arma actualmente equipada antes de cambiarla
    Item old_weapon = player->equippedWeapon;

    // Desequipar el arma anterior si hay una equipada (no es un slot vacío)
    if (old_weapon.id != ITEM_ID_EMPTY) {
        // Restar el bono de ataque del arma anterior de las estadísticas del jugador
        player->attack -= old_weapon.damage;
    }

    // Equipar la nueva arma copiándola al slot de arma equipada
    player->equippedWeapon = weapon;
    
    // Añadir el bono de ataque de la nueva arma a las estadísticas del jugador
    player->attack += player->equippedWeapon.damage;
    
    // Mostrar mensaje de confirmación con color amarillo indicando el bonus obtenido
    printf("\033[1;33mHas equipado %s. (+%d Atk)\033[0m\n", player->equippedWeapon.name, player->equippedWeapon.damage);

    // Si el arma proviene del inventario, removerla de ahí para evitar duplicados
    if (from_inventory) {
        player_remove_item_from_inventory(player, weapon.id);
    }
}

/**
 * @brief Equipa una armadura al jugador, actualizando su defensa.
 * @param player Puntero al jugador.
 * @param armor La armadura a equipar (se copia por valor).
 * @param from_inventory Indica si la armadura viene del inventario (true) o es nueva (false).
 */
void player_equip_armor(Player* player, Item armor, bool from_inventory) {
    // Validar que el jugador no sea nulo y que el ítem sea realmente una armadura (tipo 2)
    if (player == NULL || armor.type != 2) {
        printf("Error: Armadura inválida o jugador nulo.\n");
        return;
    }

    // Hacer una copia de la armadura actualmente equipada antes de cambiarla
    Item old_armor = player->equippedArmor;

    // Desequipar la armadura anterior si hay una equipada (no es un slot vacío)
    if (old_armor.id != ITEM_ID_EMPTY) {
        // Restar el bono de defensa de la armadura anterior de las estadísticas del jugador
        player->defense -= old_armor.defense;
    }

    // Equipar la nueva armadura copiándola al slot de armadura equipada
    player->equippedArmor = armor;
    
    // Añadir el bono de defensa de la nueva armadura a las estadísticas del jugador
    player->defense += player->equippedArmor.defense;
    
    // Mostrar mensaje de confirmación con color azul indicando el bonus obtenido
    printf("\033[1;34mHas equipado %s. (+%d Def)\033[0m\n", player->equippedArmor.name, player->equippedArmor.defense);

    // Si la armadura proviene del inventario, removerla de ahí para evitar duplicados
    if (from_inventory) {
        player_remove_item_from_inventory(player, armor.id);
    }
}

bool player_add_item_to_inventory(Player* player, Item item) {
    // Validar que el jugador no sea nulo antes de proceder
    if (player == NULL) {
        printf("Error: Jugador nulo al intentar añadir ítem.\n");
        return false;
    }

    // Procesar según el tipo de ítem encontrado (arma, armadura o consumible)

    if (item.type == 1) { // Arma
        // Comparar estadísticas: solo equipar si es mejor que la actual
        if (item.damage > player->equippedWeapon.damage) {
            printf("\033[1;32m¡Has cambiado a un arma mejor!\033[0m\n");
            player_equip_weapon(player, item, false);  // false = no viene del inventario
            return true;  // Equipamiento exitoso
        } else {
            // El arma actual es igual o mejor, rechazar el ítem
            printf("Tu arma equipada es mejor que este item.\n");
            return false;  // No se añadió al inventario
        }
    } else if (item.type == 2) { // Armadura
        // Comparar estadísticas: solo equipar si es mejor que la actual
        if (item.defense > player->equippedArmor.defense) {
            printf("\033[1;32m¡Has cambiado a una armadura mejor!\033[0m\n");
            player_equip_armor(player, item, false);  // false = no viene del inventario
            return true;  // Equipamiento exitoso
        } else {
            // La armadura actual es igual o mejor, rechazar el ítem
            printf("Tu armadura equipada es mejor que este item.\n");
            return false;  // No se añadió al inventario
        }
    } else if (item.type == 3) { // Consumible
        // Verificar si hay espacio disponible en el inventario
        if (player->inventoryCount >= INVENTORY_SLOTS) {
            printf("Inventario lleno. No se puede añadir %s.\n", item.name);
            return false;  // Fallo por falta de espacio
        }
        
        // Hay espacio disponible, añadir el consumible al inventario
        player->inventory[player->inventoryCount] = item;  // Copiar ítem al siguiente slot libre
        player->inventoryCount++;  // Incrementar contador de ítems en inventario
        
        // Mostrar confirmación visual del ítem añadido con color cian
        printf("\033[1;36m%s ha sido añadido al inventario.\033[0m\n", item.name);
        return true;  // Añadido exitosamente al inventario
    }
    
    // Tipo de ítem no reconocido o no válido
    return false;
}

void player_use_consumable(Player* player, int itemIndexInInventory) {
    // Verificar parámetros válidos
    if (player == NULL || itemIndexInInventory < 0 || itemIndexInInventory >= player->inventoryCount) {
        printf("Error: Indice de item invalido en el inventario.\n");
        return;
    }

    // Obtener el ítem seleccionado del inventario
    Item* itemToUse = &player->inventory[itemIndexInInventory];

    // Verificar que el ítem sea consumible
    if (itemToUse->type != 3) { // No es una poción (consumible)
        printf("%s no es un item consumible y no se puede usar de esta manera.\n", itemToUse->name);
        return;
    }

    // Guardar el nombre del ítem antes de removerlo del inventario
    char nombreConsumido[64];
    strncpy(nombreConsumido, itemToUse->name, sizeof(nombreConsumido) - 1);
    nombreConsumido[sizeof(nombreConsumido) - 1] = '\0';

    printf("Usando %s...\n", itemToUse->name);

    // Aplicar efectos de curación si el ítem tiene propiedades curativas
    if (itemToUse->heal > 0) {
        player->currentHP += itemToUse->heal;
        // Evitar que la salud exceda el máximo
        if (player->currentHP > player->maxHP) {
            player->currentHP = player->maxHP;
        }
        printf("\033[1;32mHas recuperado %d HP. HP actual: %d/%d.\033[0m\n", itemToUse->heal, player->currentHP, player->maxHP);
    }

    // Aplicar boost temporal de ataque si el ítem lo proporciona
    if (itemToUse->damage > 0) {
        player->tempAttackBoost += itemToUse->damage;
        player->attackBoostTurns = itemToUse->effectDuration;
        printf("\033[1;33mTu ataque ha aumentado en %d por %d turnos.\033[0m\n", itemToUse->damage, itemToUse->effectDuration);
    }
    
    // Aplicar boost temporal de defensa si el ítem lo proporciona
    if (itemToUse->defense > 0) {
        player->tempDefenseBoost += itemToUse->defense;
        player->defenseBoostTurns = itemToUse->effectDuration;
        printf("\033[1;34mTu defensa ha aumentado en %d por %d turnos.\033[0m\n", itemToUse->defense, itemToUse->effectDuration);
    }

    // Remover el ítem consumido del inventario y confirmar al jugador
    player_remove_item_from_inventory(player, itemToUse->id);
    printf("\033[1;34m%s ha sido consumido\033[0m\n", nombreConsumido);
}

void player_update_temporary_boosts(Player* player) {
    if (player == NULL) return;

    // Actualizar boost de ataque
    if (player->attackBoostTurns > 0) {
        player->attackBoostTurns--;
        if (player->attackBoostTurns == 0) {
            player->tempAttackBoost = 0; // El boost de ataque termina
            printf("El efecto de aumento de ataque ha terminado.\n");
        }
    }

    // Actualizar boost de defensa
    if (player->defenseBoostTurns > 0) {
        player->defenseBoostTurns--;
        if (player->defenseBoostTurns == 0) {
            player->tempDefenseBoost = 0; // El boost de defensa termina
            printf("El efecto de aumento de defensa ha terminado.\n");
        }
    }
}

/**
 * @brief Asigna los valores de clase al jugador según la opción elegida.
 * @param player Puntero al jugador.
 * @param clase Opción de clase (1=Guerrero, 2=Tanque, 3=Asesino).
 */
void player_assign_class(Player* player, int clase) {
    switch (clase) {
        case 1: // Guerrero
            // Guerrero: balance entre vida, ataque y defensa
            initializePlayer(player, "Guerrero", 350, 35, 25, 200);
            break;
        case 2: // Tanque
            // Tanque: máxima vida y defensa, ataque bajo
            initializePlayer(player, "Tanque", 450, 22, 40, 200);
            break;
        case 3: // Asesino
            // Asesino: ataque muy alto, vida y defensa bajas
            initializePlayer(player, "Asesino", 260, 50, 12, 200);
            break;
    }
}

/**
 * @brief Pregunta al usuario por la clase y asigna los valores al jugador.
 * @param player Puntero al jugador.
 */
void player_choose_and_assign_class(Player* player) {
    ui_menu_welcome();
    int clase = 0;
    while (clase < 1 || clase > 3) {
        printf("Ingresa el número de tu clase: ");
        char input[10];
        fgets(input, sizeof(input), stdin);
        clase = atoi(input);
    }
    player->classID = clase;
    player_assign_class(player, clase);
}

// Comparador seguro para Map de strings
static int string_equals(void* a, void* b) {
    return strcmp((const char*)a, (const char*)b) == 0;
}

void player_add_initial_class_items(Player* player, const char* initial_items_csv) {
    // Mostrar animación de carga y cargar el mapa de ítems iniciales
    ui_load_animation();
    Map* clase_a_items = load_initial_items_map(initial_items_csv);
    if (!clase_a_items) return;
    
    // Determinar el nombre de la clase según el ID del jugador
    char* clase = NULL;
    if (player->classID == 1) clase = "Guerrero";
    else if (player->classID == 2) clase = "Tanque";
    else if (player->classID == 3) clase = "Asesino";
    
    // Buscar la lista de ítems correspondiente a la clase del jugador
    MapPair* pair = map_search(clase_a_items, clase);
    List* lista = (List*)pair->value;
    
    // Mostrar encabezado visual del equipo inicial
    printf("\033[1;36m══════════════════════════════════════════════\033[0m\n");
    printf("\033[1;32m¡Has recibido tu equipo inicial!\033[0m\n");
    printf("\033[1;36m──────────────────────────────────────────────\033[0m\n");
    
    // Variable para controlar si se debe saltar la animación
    int skip = 0;
    
    // Iterar por todos los ítems de la clase y equiparlos/añadirlos
    for (Item* item = list_first(lista); item; item = list_next(lista)) {
        // Permitir al jugador saltar la animación presionando Enter
        if (!skip && _kbhit()) {
            int ch = _getch();
            if (ch == 13) skip = 1;
        }
        
        // Procesar cada ítem según su tipo
        if (item->type == 1) { // Arma
            player->equippedWeapon = *item;
            player->attack += item->damage;
            printf("\033[1;33m- %s (+%d Atk, equipada)\033[0m\n", item->name, item->damage);
        } else if (item->type == 2) { // Armadura
            player->equippedArmor = *item;
            player->defense += item->defense;
            printf("\033[1;34m- %s (+%d Def, equipada)\033[0m\n", item->name, item->defense);
        } else { // Consumibles u otros ítems
            player->inventory[player->inventoryCount++] = *item;
            printf("\033[1;36m- %s (añadido al inventario)\033[0m\n", item->name);
        }
        
        // Asegurar que el texto se muestre inmediatamente
        fflush(stdout);
        
        // Pausa entre ítems si no se ha saltado la animación
        if (!skip) skip = ui_sleep_skip(500);
    }
    
    printf("\033[1;36m══════════════════════════════════════════════\033[0m\n");
    
    // Limpiar memoria: liberar todos los ítems y estructuras de datos
    map_first(clase_a_items);
    MapPair* p;
    while ((p = map_next(clase_a_items))) {
        List* l = (List*)p->value;
        // Liberar cada ítem de la lista
        for (Item* item = list_first(l); item; item = list_next(l)) {
            free(item);
        }
        // Limpiar la lista y liberar la clave
        list_clean(l);
        free(p->key);
    }
    map_destroy(clase_a_items);

    // Mensaje final y esperar confirmación del jugador
    printf("Los items se equiparan automaticamente.\n");
    waitForKeyPress();
}

void display_inventory(Player* player, bool show_index, bool show_use_option) {
    printf("\x1b[36m╔═══════════════════════════════════════════════╗\x1b[0m\n");
    printf("\x1b[36m║              \x1b[1m--- INVENTARIO ---\x1b[0m               \x1b[36m║\x1b[0m\n");
    printf("\x1b[36m╠═══════════════════════════════════════════════╣\x1b[0m\n");
    if (player->inventoryCount == 0) {
        printf("\x1b[31mTu inventario está vacío.\x1b[0m\n");
        printf("\x1b[36m╚═══════════════════════════════════════════════╝\x1b[0m\n");
        return;
    }
    for (int i = 0; i < player->inventoryCount; i++) {
        Item currentItem = player->inventory[i];
        if (show_index)
            printf("\x1b[33m%2d.\x1b[0m ", i + 1);
        else
            printf("   ");
        printf("\x1b[1m%s\x1b[0m", currentItem.name);
        bool first = true;
        printf(" (");
        if (currentItem.heal > 0) {
            printf("\x1b[32mCura: %d\x1b[0m", currentItem.heal);
            first = false;
        }
        if (currentItem.damage > 0) {
            if (!first) printf(", ");
            printf("\x1b[33mAtk+: %d\x1b[0m", currentItem.damage);
            first = false;
        }
        if (currentItem.defense > 0) {
            if (!first) printf(", ");
            printf("\x1b[34mDef+: %d\x1b[0m", currentItem.defense);
            first = false;
        }
        if (currentItem.effectDuration > 0 && (currentItem.damage > 0 || currentItem.defense > 0)) {
            if (!first) printf(", ");
            printf("Duración: %d", currentItem.effectDuration);
        }
        printf(")\n");
    }
    printf("\x1b[36m╚═══════════════════════════════════════════════╝\x1b[0m\n");
    if (show_use_option) {
        printf("Elige un item a usar (0 para cancelar): ");
    }
}
