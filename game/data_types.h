#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#define MAX_NAME_LENGTH 16
#define MAX_RARITY_LENGTH 20
#define MAX_DESCRIPTION_LENGTH 256
#define INVENTORY_SLOTS 10
#define ITEM_ID_EMPTY 0

// --- ESTRUCTURAS DE DATOS ---

// Struct de items
typedef struct {
    int id;                                
    char name[MAX_NAME_LENGTH];          
    int type;                               // Tipo del item (1. Arma, 2. Armadura, 3. Accesorio, 4. Consumible)
    char rarity[MAX_RARITY_LENGTH];         // Rareza del Item 
    int damage;                             
    int defense;        
    int heal;           // (Solo para Pociones)
    int price;          // Valor del Item
    int difficulty;     // Enlazar a Mapa - Tienda
    int effectDuration;  
    char class[16];     // Clase a la que pertenece el item (Guerrero, Tanque, Asesino)
} Item;

// Struct de Player
typedef struct {
    char name[MAX_NAME_LENGTH];         
    int maxHP;                         
    int currentHP;                      
    int attack;                         
    int defense;                       
    int gold;                           
    Item inventory[INVENTORY_SLOTS];    
    int inventoryCount;                 // Cantidad de Items en Inventario
    Item equippedWeapon;                
    Item equippedArmor;                 

    // Estos campos gestionan los efectos TEMPORALES ACTUALMENTE APLICADOS al jugador.
    // Una poción podría aumentar solo ataque, solo defensa, o ambos. 
    int tempAttackBoost;    // Cantidad de ataque temporal ACTIVA en el jugador
    int tempDefenseBoost;   // Cantidad de defensa temporal ACTIVA en el jugador
    int attackBoostTurns;   // Turnos restantes para el aumento de ataque
    int defenseBoostTurns;  // Turnos restantes para el aumento de defensa
} Player;

// Struct de Enemy
typedef struct {
    int id;                    
    char name[MAX_NAME_LENGTH]; 
    int HP;       
    int currentHP;     
    int attack;                 
    int defense;               
    int difficulty; // Dificultad del enemigo (1, 2 o 3)
} Enemy;

// Struct de Escenario
typedef struct {
    int id;                                             
    int difficulty;                                     // Dificultad del escenario (1, 2 o 3)
    char name[MAX_NAME_LENGTH];                        
    char description[MAX_DESCRIPTION_LENGTH];           // Descripción breve del lugar
} Scenario;

#endif