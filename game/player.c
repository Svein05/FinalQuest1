#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "player.h"
#include "data_types.h" // Para Player, Item, y las nuevas constantes
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
    item->cost = 0;
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

    // Inicializar los slots del inventario como vacíos
    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        player->inventory[i].id = ITEM_ID_EMPTY; // Marcar como slot vacío
        initializeEmptyItem(&player->inventory[i]); // Asegurarse de que todos los campos estén limpios
    }

    printf("Jugador '%s' inicializado con HP: %d, Atk: %d, Def: %d, Oro: %d.\n",
           player->name, player->currentHP, player->attack, player->defense, player->gold);
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
        printf("'%s' ha sido removido del inventario.\n", player->inventory[found_index].name); // Nombre del item que se movió
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
        printf("Se ha desequipado %s. (-%d Atk)\n", old_weapon.name, old_weapon.damage);

        // Intenta devolver el arma vieja al inventario
        if (player_add_item_to_inventory(player, old_weapon)) {
            printf("%s ha vuelto a tu inventario.\n", old_weapon.name);
        } else {
            printf("Tu inventario esta lleno, %s se ha perdido!\n", old_weapon.name);
        }
    }

    // Equipa la nueva arma
    player->equippedWeapon = weapon; // Copia la nueva arma al slot de equipado
    player->attack += player->equippedWeapon.damage; // Añade el bono de ataque de la nueva arma
    printf("Has equipado %s. (+%d Atk)\n", player->equippedWeapon.name, player->equippedWeapon.damage);

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
        printf("Se ha desequipado %s. (-%d Def)\n", old_armor.name, old_armor.defense);

        // Intenta devolver la armadura vieja al inventario
        if (player_add_item_to_inventory(player, old_armor)) {
            printf("%s ha vuelto a tu inventario.\n", old_armor.name);
        } else {
            printf("Tu inventario esta lleno, %s se ha perdido!\n", old_armor.name);
        }
    }

    // Equipa la nueva armadura
    player->equippedArmor = armor; // Copia la nueva armadura al slot de equipado
    player->defense += player->equippedArmor.defense; // Añade el bono de defensa de la nueva armadura
    printf("Has equipado %s. (+%d Def)\n", player->equippedArmor.name, player->equippedArmor.defense);

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

    // --- Lógica de reemplazo automático de equipo si es mejor ---
    if (item.type == 1) { // Es un arma
        if (item.damage > player->equippedWeapon.damage) {
            printf("¡Has encontrado un arma mejor! Equipada automaticamente.\n");
            player_equip_weapon(player, item, false); // false porque es un ítem nuevo, no del inventario
            return true;
        }
    } else if (item.type == 2) { // Es una armadura
        if (item.defense > player->equippedArmor.defense) {
            printf("¡Has encontrado una armadura mejor! Equipada automaticamente.\n");
            player_equip_armor(player, item, false); // false porque es un ítem nuevo
            return true;
        }
    }

    // Si no es un equipo mejor (o si es consumible), intenta añadirlo al inventario
    if (player->inventoryCount >= INVENTORY_SLOTS) {
        printf("Inventario lleno. No se puede añadir %s.\n", item.name);
        return false;
    }

    // Copiar el ítem completo al siguiente slot disponible del inventario.
    // Como name y rarity son char[], la copia por valor de la struct Item
    // también copia estas cadenas, lo cual es seguro y no requiere strdup aquí.
    player->inventory[player->inventoryCount] = item;
    player->inventoryCount++;
    printf("%s ha sido añadido al inventario.\n", item.name);
    return true;
}

/**
 * @brief Muestra un menú detallado del jugador con sus estadísticas, oro y equipo actual.
 * @param player Puntero a la estructura del Jugador.
 */
void displayPlayerMenu(Player* player) {
    if (player == NULL) return;

    printf("\n--- ESTADO DEL JUGADOR: %s ---\n", player->name);
    printf("Vida: %d/%d\n", player->currentHP, player->maxHP);
    printf("Ataque: %d (Base: %d", player->attack + player->tempAttackBoost, player->attack);
    if (player->tempAttackBoost > 0) {
        printf(", Boost: +%d por %d turnos", player->tempAttackBoost, player->attackBoostTurns);
    }
    printf(")\n");

    printf("Defensa: %d (Base: %d", player->defense + player->tempDefenseBoost, player->defense);
    if (player->tempDefenseBoost > 0) {
        printf(", Boost: +%d por %d turnos", player->tempDefenseBoost, player->defenseBoostTurns);
    }
    printf(")\n");

    printf("Oro: %d\n", player->gold);

    printf("--- EQUIPO ---\n");
    printf("Arma Equipada: %s (Daño: %d)\n",
           (player->equippedWeapon.id != ITEM_ID_EMPTY) ? player->equippedWeapon.name : "Nada",
           player->equippedWeapon.damage);
    printf("Armadura Equipada: %s (Defensa: %d)\n",
           (player->equippedArmor.id != ITEM_ID_EMPTY) ? player->equippedArmor.name : "Nada",
           player->equippedArmor.defense);

    printf("--- INVENTARIO ---\n");
    if (player->inventoryCount == 0) {
        printf("Inventario vacio.\n");
    } else {
        for (int i = 0; i < player->inventoryCount; i++) {
            Item currentItem = player->inventory[i];
            // Solo mostrar ítems que NO son el arma o armadura equipada, y que no están vacíos
            if (currentItem.id != ITEM_ID_EMPTY &&
                currentItem.id != player->equippedWeapon.id && // Asume que un ítem equipado no tiene un duplicado en inventario por ID
                currentItem.id != player->equippedArmor.id) {
                printf("%d. %s (Tipo: %d, Rareza: %s, Costo: %d",
                       i + 1, currentItem.name, currentItem.type, currentItem.rarity, currentItem.cost);
                if (currentItem.type == 1) printf(", Daño: %d)\n", currentItem.damage);
                else if (currentItem.type == 2) printf(", Defensa: %d)\n", currentItem.defense);
                else if (currentItem.type == 3) {
                    printf(", Cura: %d", currentItem.heal);
                    if (currentItem.damage > 0 || currentItem.defense > 0) {
                        printf(", Boost: +%d Atk, +%d Def por %d turnos",
                               currentItem.damage, currentItem.defense, currentItem.effectDuration);
                    }
                    printf(")\n");
                } else printf(")\n"); // Tipo desconocido
            }
        }
    }
    printf("---------------------------\n");
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

    printf("Usando %s...\n", itemToUse->name);

    // Aplicar curación (si tiene)
    if (itemToUse->heal > 0) {
        player->currentHP += itemToUse->heal;
        if (player->currentHP > player->maxHP) {
            player->currentHP = player->maxHP;
        }
        printf("Has recuperado %d HP. HP actual: %d/%d.\n", itemToUse->heal, player->currentHP, player->maxHP);
    }

    // Aplicar boosts temporales (si tiene)
    if (itemToUse->damage > 0) {
        player->tempAttackBoost += itemToUse->damage;
        // Establecer la duración. Si ya hay un boost activo, puedes decidir si se "stackean" los turnos
        // o si simplemente se reinicia la duración. Aquí, la reinicia.
        player->attackBoostTurns = itemToUse->effectDuration;
        printf("Tu ataque ha aumentado en %d por %d turnos.\n", itemToUse->damage, itemToUse->effectDuration);
    }
    if (itemToUse->defense > 0) {
        player->tempDefenseBoost += itemToUse->defense;
        player->defenseBoostTurns = itemToUse->effectDuration;
        printf("Tu defensa ha aumentado en %d por %d turnos.\n", itemToUse->defense, itemToUse->effectDuration);
    }

    // Remover el ítem consumido del inventario
    // Mover los items subsiguientes para llenar el espacio
    player_remove_item_from_inventory(player, itemToUse->id);
    printf("%s ha sido consumido y eliminado del inventario.\n", itemToUse->name);
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
