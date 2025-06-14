#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#define MAX_NAME_LENGTH 50
#define MAX_RARITY_LENGTH 20
#define MAX_DESCRIPTION_LENGTH 256
#define INVENTORY_SLOTS 10
#define ITEM_ID_EMPTY 0

// --- ESTRUCTURAS DE DATOS ---

// Struct de items
typedef struct {
    int id;                                 // ID unico del Item
    char name[MAX_NAME_LENGTH];             // Nombre del Item
    int type;                               // Tipo del item (1. Consumible, 2. Arma, 3. Armadura)
    char rarity[MAX_RARITY_LENGTH];         // Rareza del Item (Ilustrativo)
    int damage;                             // Daño (Permanente si es Arma, Temporal si es Pocion)
    int defense;        // Defensa (Permanente si es Armadura, Temporal si es Pocion)
    int heal;           // Curacion (Solo para Pociones)
    int cost;           // Costo para comprar Item
    int difficulty;     // Enlazar a Mapa - Tienda
    int effectDuration;  // Duracion de Turnos para Efectos de Pociones
} Item;

// Struct de Player
typedef struct {
    char name[MAX_NAME_LENGTH];         // Nombre del Jugador
    int maxHP;                          // Maxima Vida
    int currentHP;                      // Vida Actual
    int attack;                         // Ataque o Daño
    int defense;                        // Defensa (Reduccion de Daño)
    int gold;                           // Oro para Utilizar
    Item inventory[INVENTORY_SLOTS];    // Arreglo de Items (Inventario)
    Item equippedWeapon;                // Puntero a el Arma (Item)
    Item equippedArmor;                 // Puntero a la Armadura (Item)
    int inventoryCount;                 // Cantidad de Items en Inventario

    // Estos campos gestionan los efectos TEMPORALES ACTUALMENTE APLICADOS al jugador.
    // Una poción podría aumentar solo ataque, solo defensa, o ambos.
    int tempAttackBoost;    // Cantidad de ataque temporal ACTIVA en el jugador
    int tempDefenseBoost;   // Cantidad de defensa temporal ACTIVA en el jugador
    int attackBoostTurns;   // Turnos restantes para el aumento de ataque
    int defenseBoostTurns;  // Turnos restantes para el aumento de defensa
} Player;

// Struct de Enemy
typedef struct {
    int id;                     // ID unico
    char name[MAX_NAME_LENGTH]; // Nombre del Enemigo
    int currentHP;              // Vida Actual
    int attack;                 // Puntos de Ataque
    int defense;                // Puntos de Defensa
    int goldReward;             // Oro de Recompensa
    int difficulty;             // Dificultad
} Enemy;

// Struct de Escenario
typedef struct ScenarioNode {
    int id;                                             // Identificador único del escenario
    int difficulty;                                     // Dificultad del escenario (1, 2 o 3)
    char description[MAX_DESCRIPTION_LENGTH];           // Descripción breve del lugar
    struct ScenarioNode* next;                          // Puntero al siguiente escenario en el mapa lineal
    Enemy* boss;                                        // Enemigo enlazado al Escenario (OPCIONAL)

    int type;                   // Tipos de Escenario
    // 1: Combate
    // 2: Tienda (solo la inicial)
    // 3: Evento Aleatorio (combate, mercader o bonus)
    // 4: Jefe
} ScenarioNode;

#endif