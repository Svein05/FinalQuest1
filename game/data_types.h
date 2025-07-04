#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#define MAX_NAME_LENGTH 48
#define MAX_RARITY_LENGTH 20
#define MAX_DESCRIPTION_LENGTH 256
#define INVENTORY_SLOTS 10
#define ITEM_ID_EMPTY 0

// --- ESTRUCTURAS DE DATOS ---

// Struct de items
typedef struct {
    int id;                                
    char name[MAX_NAME_LENGTH];          
    int type; // Tipo del item (1. Arma, 2. Armadura, 3. Consumible)
    char rarity[MAX_RARITY_LENGTH];
    int damage;
    int defense;
    int heal;           // Solo para Pociones
    int price;
    int difficulty;     // Enlazar a Mapa - Tienda
    int effectDuration;  
    char class[16];     // Clase a la que pertenece el item (Guerrero, Tanque, Asesino)
} Item;

// Struct de Player
typedef struct {
    char name[MAX_NAME_LENGTH];         
    int classID;
    int maxHP;                         
    int currentHP;                      
    int attack;                         
    int defense;                       
    int gold;                           
    Item inventory[INVENTORY_SLOTS];    
    int inventoryCount;
    Item equippedWeapon;                
    Item equippedArmor;                  
    int tempAttackBoost;  
    int tempDefenseBoost;   
    int attackBoostTurns;  
    int defenseBoostTurns;
    int enemiesDefeated; 
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
    char description[MAX_DESCRIPTION_LENGTH];           // Descripción breve del escenario
} Scenario;

#endif