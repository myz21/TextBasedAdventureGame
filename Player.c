#include <stdio.h>
#include <string.h>
#include <time.h> // Include time.h for timing functions
#include "Player.h"
#include "Room.h"
#include "GameFunctions.h"  // Include GameFunctions.h to access constants

void initializePlayer(Player *player) {
    strcpy(player->name, "Zeki Reis");
    player->health = 100;
    player->strength = 10;
    player->inventoryCapacity = MAX_ITEMS;
    player->positionX = 0;
    player->positionY = 0;
    player->roomIndex = 0; // Set the initial room index
    player->score = 0; // Initialize score to 0
    player->currentWeapon = NULL; // Initialize currentWeapon to NULL
    for (int i = 0; i < MAX_ITEMS; i++) {
        player->inventory[i] = NULL;
    }
}

// I CHANGED //KNIFE 
//SWORD TO K AND S
void attack(Player *player, Enemy *enemy, const char *weapon) {
    // Display debug information about the attack
    printf("Attempting to attack enemy %s at (%d, %d)\n", enemy->name, enemy->positionX, enemy->positionY);
    printf("Enemy health before attack: %d\n", enemy->health);

    // Variable to hold the damage dealt
    int damage = 0;

    // Validate and determine weapon damage
    if (weapon != NULL) {
        if (strcmp(weapon, "K") == 0) { // Knife
            damage = 20;
        } else if (strcmp(weapon, "S") == 0) { // Sword
            damage = 30;
        } else {
            printf("Invalid weapon: %s. Use 'K' for Knife or 'S' for Sword.\n", weapon);
            return; // Exit the function for invalid weapon input
        }
    } else {
        printf("No weapon specified. Use 'K' for Knife or 'S' for Sword.\n");
        return; // Exit if weapon is NULL
    }

    // Apply damage to the enemy
    enemy->health -= damage;
    printf("%s attacked %s with %s for %d damage!\n", player->name, enemy->name, weapon, damage);

    // Check if the enemy is defeated
    if (enemy->health <= 0) {
        printf("%s is defeated!\n", enemy->name);
        player->score += 1; // Increase player's score
        printf("Your current score: %d\n", player->score);
        enemy->positionX = -1; // Remove enemy from the map
        enemy->positionY = -1;
        enemy->isDefeated = 1; // Mark enemy as defeated
    } else {
        // Enemy retaliates if not defeated
        printf("%s is still alive with %d health.\n", enemy->name, enemy->health);
        player->health -= 10; // Enemy deals 10 damage to the player
        printf("%s attacked back! You took 10 damage. Your current health: %d\n", enemy->name, player->health);

        // Check if the player is defeated
        if (player->health <= 0) {
            printf("You have been defeated by %s. Game over.\n", enemy->name);
        }
    }
}




//I CHANGED HEALTH_POTION TO H
void healPlayer(Player *player) {
    for (int i = 0; i < player->inventoryCapacity; i++) {
            if (player->inventory[i] != NULL && strcmp(player->inventory[i], "H") == 0) {
                player->health += 20;
            if (player->health > 100) player->health = 100;
                printf("You healed 20 HP! Current health: %d\n", player->health);
                free(player->inventory[i]);
                player->inventory[i] = NULL;
            return;
        }
    }
    printf("No health potions in inventory!\n");
}

//PICKUP ITEM 
void pickupItem(Player *player, int positionX, int positionY) {
    Room *currentRoom = &rooms[player->roomIndex];

    for (int i = 0; i < currentRoom->itemCount; i++) {
        if (currentRoom->items[i] != '\0') { // Check if the item exists
            printf("Picked up %c!\n", currentRoom->items[i]);
            
            // Add to player inventory and change weapon
            for (int j = 0; j < player->inventoryCapacity; j++) {
                if (player->inventory[j] == NULL) {
                    player->inventory[j] = malloc(sizeof(char));
                    *player->inventory[j] = currentRoom->items[i];
                    player->currentWeapon = player->inventory[j];
                    break;
                }
            }
            currentRoom->items[i] = '\0'; // Remove item from room
            return;
        }
    }
    printf("No items to pick up!\n");
}

void listInventory(Player *player) {
    printf("Inventory:\n");
    for (int i = 0; i < player->inventoryCapacity; i++) {
        if (player->inventory[i] != NULL) {
            printf("- %s\n", player->inventory[i]);
        }
    }
}



