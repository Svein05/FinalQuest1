#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h> // Para Sleep()

#include "player.h"
#include "data_types.h"
#include "ui.h"
#include "data_loader.h"
#include "../tdas/map.h"
#include "../tdas/list.h"
// Puedes necesitar includes adicionales para debug o IO si usas system("cls") etc.

// --- FUNCIONES AUXILIARES INTERNAS ---

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


// --- IMPLEMENTACIÓN DE FUNCIONES DEL MÓDULO PLAYER ---

/**
 * @brief Inicializa la estructura del jugador con sus estadísticas base y equipo vacío.
 * @param player Puntero a la estructura Player a inicializar.
 * @param name Nombre del jugador.
 * @param hp Vida máxima inicial del jugador.
 * @param atk Ataque inicial del jugador.
 * @param def Defensa inicial del jugador.
 * @param gold Oro inicial del jugador.
 */
void initializePlayer(Player* player, const char* name, int hp, int atk, int def, int gold) {
    if (player == NULL) {
        printf("Error: No se puede inicializar un jugador nulo.\n");
        return;
    }

    strncpy(player->name, name, sizeof(player->name) - 1);
    player->name[sizeof(player->name) - 1] = '\0';

    player->maxHP = hp;
    player->currentHP = hp;
    player->attack = atk;
    player->defense = def;
    player->gold = gold;

    player->inventoryCount = 0;

    // --- CAMBIO AQUÍ: Inicializar los slots de equipo como ítems vacíos ---
    initializeEmptyItem(&player->equippedWeapon);
    initializeEmptyItem(&player->equippedArmor);

    player->tempAttackBoost = 0;
    player->tempDefenseBoost = 0;
    player->attackBoostTurns = 0;
    player->defenseBoostTurns = 0;
    player->enemiesDefeated = 0; // Inicializar enemigos derrotados en 0

    // Inicializar los slots del inventario como vacíos
    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        player->inventory[i].id = ITEM_ID_EMPTY; // Marcar como slot vacío
        initializeEmptyItem(&player->inventory[i]); // Asegurarse de que todos los campos estén limpios
    }

    ui_player_init(player);
}

/**
 * @brief Remueve un ítem específico del inventario del jugador por su ID.
 * @param player Puntero al jugador.
 * @param item_id El ID del ítem a remover.
 * @return true si el ítem fue removido, false si no se encontró.
 */
bool player_remove_item_from_inventory(Player* player, int item_id) {
    if (player == NULL || item_id == ITEM_ID_EMPTY) return false;

    int found_index = -1;
    for (int i = 0; i < player->inventoryCount; i++) {
        if (player->inventory[i].id == item_id) {
            found_index = i;
            break;
        }
    }

    if (found_index != -1) {
        // Mover los ítems siguientes para rellenar el hueco
        for (int i = found_index; i < player->inventoryCount - 1; i++) {
            player->inventory[i] = player->inventory[i+1];
        }
        player->inventoryCount--;
        // Opcional: limpiar el último slot si es necesario, aunque inventoryCount ya lo manejará
        // initializeEmptyItem(&player->inventory[player->inventoryCount]);
        return true;
    }
    return false; // Ítem no encontrado
}

/**
 * @brief Equipa un arma al jugador, actualizando su ataque.
 * Si ya hay un arma equipada, la anterior va al inventario (si hay espacio).
 * @param player Puntero al jugador.
 * @param weapon El arma a equipar (se copia por valor).
 * @param from_inventory Indica si el arma viene del inventario (true) o es nueva (false).
 */
void player_equip_weapon(Player* player, Item weapon, bool from_inventory) {
    if (player == NULL || weapon.type != 1) { // weapon.type == 1 para armas
        printf("Error: Arma inválida o jugador nulo.\n");
        return;
    }

    Item old_weapon = player->equippedWeapon; // Guarda el arma vieja (copia por valor)

    // Primero, desequipa el arma anterior si existe y no es un ítem vacío
    if (old_weapon.id != ITEM_ID_EMPTY) {
        player->attack -= old_weapon.damage; // Quita el bono de ataque del arma vieja
        // NO devolver el arma vieja al inventario, simplemente desaparece
    }

    // Equipa la nueva arma
    player->equippedWeapon = weapon; // Copia la nueva arma al slot de equipado
    player->attack += player->equippedWeapon.damage; // Añade el bono de ataque de la nueva arma
    printf("\033[1;33mHas equipado %s. (+%d Atk)\033[0m\n", player->equippedWeapon.name, player->equippedWeapon.damage);

    // Si el arma fue equipada desde el inventario, la removemos de ahí
    if (from_inventory) {
        player_remove_item_from_inventory(player, weapon.id);
    }
}

/**
 * @brief Equipa una armadura al jugador, actualizando su defensa.
 * Si ya hay una armadura equipada, la anterior va al inventario (si hay espacio).
 * @param player Puntero al jugador.
 * @param armor La armadura a equipar (se copia por valor).
 * @param from_inventory Indica si la armadura viene del inventario (true) o es nueva (false).
 */
void player_equip_armor(Player* player, Item armor, bool from_inventory) {
    if (player == NULL || armor.type != 2) { // armor.type == 2 para armaduras
        printf("Error: Armadura inválida o jugador nulo.\n");
        return;
    }

    Item old_armor = player->equippedArmor; // Guarda la armadura vieja (copia por valor)

    // Primero, desequipa la armadura anterior si existe y no es un ítem vacío
    if (old_armor.id != ITEM_ID_EMPTY) {
        player->defense -= old_armor.defense; // Quita el bono de defensa de la armadura vieja
        // NO devolver la armadura vieja al inventario, simplemente desaparece
    }

    // Equipa la nueva armadura
    player->equippedArmor = armor; // Copia la nueva armadura al slot de equipado
    player->defense += player->equippedArmor.defense; // Añade el bono de defensa de la nueva armadura
    printf("\033[1;34mHas equipado %s. (+%d Def)\033[0m\n", player->equippedArmor.name, player->equippedArmor.defense);

    // Si la armadura fue equipada desde el inventario, la removemos de ahí
    if (from_inventory) {
        player_remove_item_from_inventory(player, armor.id);
    }
}

/**
 * @brief Añade un ítem al inventario del jugador.
 * Si el ítem es equipable (arma/armadura) y mejora el equipo actual, lo equipa automáticamente.
 * Si no es equipable o no mejora el equipo, se añade al inventario si hay espacio.
 * @param player Puntero al jugador.
 * @param item El ítem a añadir/considerar (se copia por valor).
 * @return true si el ítem se añadió/equipó correctamente, false si el inventario está lleno y no se pudo equipar.
 */
bool player_add_item_to_inventory(Player* player, Item item) {
    if (player == NULL) {
        printf("Error: Jugador nulo al intentar añadir ítem.\n");
        return false;
    }

    // Solo consumibles pueden ir al inventario
    if (item.type == 1) { // Arma
        if (item.damage > player->equippedWeapon.damage) {
            printf("\033[1;32m¡Has cambiado a un arma mejor!\033[0m\n");
            player_equip_weapon(player, item, false);
            return true;
        } else {
            printf("Tu arma equipada es mejor que este item.\n");
            return false;
        }
    } else if (item.type == 2) { // Armadura
        if (item.defense > player->equippedArmor.defense) {
            printf("\033[1;32m¡Has cambiado a una armadura mejor!\033[0m\n");
            player_equip_armor(player, item, false);
            return true;
        } else {
            printf("Tu armadura equipada es mejor que este item.\n");
            return false; 
        }
    } else if (item.type == 3) { // Consumible
        if (player->inventoryCount >= INVENTORY_SLOTS) {
            printf("Inventario lleno. No se puede añadir %s.\n", item.name);
            return false;
        }
        player->inventory[player->inventoryCount] = item;
        player->inventoryCount++;
        printf("\033[1;36m%s ha sido añadido al inventario.\033[0m\n", item.name);
        return true;
    }
    return false;
}

// --- Funciones adicionales (ya estaban en player.c) ---

/**
 * @brief Función para usar un consumible (ej. poción) desde el inventario del jugador.
 * @param player Puntero al jugador.
 * @param itemIndexInInventory El índice (0-basado) del ítem a usar en el inventario.
 */
void player_use_consumable(Player* player, int itemIndexInInventory) {
    if (player == NULL || itemIndexInInventory < 0 || itemIndexInInventory >= player->inventoryCount) {
        printf("Error: Indice de item invalido en el inventario.\n");
        return;
    }

    Item* itemToUse = &player->inventory[itemIndexInInventory];

    if (itemToUse->type != 3) { // No es una poción (consumible)
        printf("%s no es un item consumible y no se puede usar de esta manera.\n", itemToUse->name);
        return;
    }

    // Guardar el nombre antes de remover el ítem
    char nombreConsumido[64];
    strncpy(nombreConsumido, itemToUse->name, sizeof(nombreConsumido) - 1);
    nombreConsumido[sizeof(nombreConsumido) - 1] = '\0';

    printf("Usando %s...\n", itemToUse->name);

    // Aplicar curación (si tiene)
    if (itemToUse->heal > 0) {
        player->currentHP += itemToUse->heal;
        if (player->currentHP > player->maxHP) {
            player->currentHP = player->maxHP;
        }
        printf("\033[1;32mHas recuperado %d HP. HP actual: %d/%d.\033[0m\n", itemToUse->heal, player->currentHP, player->maxHP);
    }

    // Aplicar boosts temporales (si tiene)
    if (itemToUse->damage > 0) {
        player->tempAttackBoost += itemToUse->damage;
        player->attackBoostTurns = itemToUse->effectDuration;
        printf("\033[1;33mTu ataque ha aumentado en %d por %d turnos.\033[0m\n", itemToUse->damage, itemToUse->effectDuration);
    }
    if (itemToUse->defense > 0) {
        player->tempDefenseBoost += itemToUse->defense;
        player->defenseBoostTurns = itemToUse->effectDuration;
        printf("\033[1;34mTu defensa ha aumentado en %d por %d turnos.\033[0m\n", itemToUse->defense, itemToUse->effectDuration);
    }

    // Remover el ítem consumido del inventario
    player_remove_item_from_inventory(player, itemToUse->id);
    printf("\033[1;34m%s ha sido consumido\033[0m\n", nombreConsumido);
}

/**
 * @brief Función para actualizar los efectos temporales del jugador al final de un turno.
 * @param player Puntero al jugador.
 */
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
            initializePlayer(player, "Guerrero", 100, 10, 5, 200);
            break;
        case 2: // Tanque
            initializePlayer(player, "Tanque", 130, 7, 12, 200);
            break;
        case 3: // Asesino
            initializePlayer(player, "Asesino", 999, 999, 999, 999);
            break;
        default:
            initializePlayer(player, "Aventurero", 100, 10, 5, 200);
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

// Añade ítems al jugador de forma silenciosa (sin mensajes) y guarda resumen
void player_add_initial_class_items(Player* player, const char* initial_items_csv) {
    ui_load_animation("Cargando datos del juego");
    Map* clase_a_items = load_initial_items_map(initial_items_csv);
    if (!clase_a_items) return;
    char* clase = NULL;
    if (player->classID == 1) clase = "Guerrero";
    else if (player->classID == 2) clase = "Tanque";
    else if (player->classID == 3) clase = "Asesino";
    MapPair* pair = map_search(clase_a_items, clase);
    List* lista = (List*)pair->value;
    printf("\033[1;36m══════════════════════════════════════════════\033[0m\n");
    printf("\033[1;32m¡Has recibido tu equipo inicial!\033[0m\n");
    printf("\033[1;36m──────────────────────────────────────────────\033[0m\n");
    for (Item* item = list_first(lista); item; item = list_next(lista)) {
        if (item->type == 1) { // Arma
            player->equippedWeapon = *item;
            player->attack += item->damage;
            printf("\033[1;33m- %s (+%d Atk, equipada)\033[0m\n", item->name, item->damage);
        } else if (item->type == 2) { // Armadura
            player->equippedArmor = *item;
            player->defense += item->defense;
            printf("\033[1;34m- %s (+%d Def, equipada)\033[0m\n", item->name, item->defense);
        } else {
            player->inventory[player->inventoryCount++] = *item;
            printf("\033[1;36m- %s (añadido al inventario)\033[0m\n", item->name);
        }
        Sleep(500);
    }
    printf("\033[1;36m══════════════════════════════════════════════\033[0m\n");
    // Liberar memoria del Map y listas
    map_first(clase_a_items);
    MapPair* p;
    while ((p = map_next(clase_a_items))) {
        List* l = (List*)p->value;
        for (Item* item = list_first(l); item; item = list_next(l)) {
            free(item);
        }
        list_clean(l);
        free(p->key);
    }
    map_destroy(clase_a_items);

    printf("Los items se equiparan automaticamente.\n");
    waitForKeyPress();
}

/**
 * @brief Muestra el inventario del jugador con formato visual, ocultando stats en 0.
 * @param player Puntero al jugador.
 * @param show_index Si es true, muestra el índice para selección.
 * @param show_use_option Si es true, muestra la opción de usar/cancelar.
 */
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
