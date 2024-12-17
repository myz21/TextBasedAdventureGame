#include <stdio.h>
#include <string.h>
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
    for (int i = 0; i < MAX_ITEMS; i++) {
        player->inventory[i] = NULL;
    }
}

// I CHANGED //KNIFE 
//SWORD TO K AND S
void attack(Player *player, Enemy *enemy, const char *weapon) {
    int damage = 0;

    if (weapon != NULL && strcmp(weapon, "K") == 0) {
        damage = 20;
    } else if (strcmp(weapon, "S") == 0) {
        damage = 30;
    }

    enemy->health -= damage;
    printf("%s attacked %s with %s for %d damage!\n", player->name, enemy->name, weapon, damage);

    if (enemy->health <= 0) {
        printf("%s is defeated!\n", enemy->name);
        player->score += 1; // New: Increase score by 1
        printf("Your score: %d\n", player->score);
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
            
            // Add to player inventory
            for (int j = 0; j < player->inventoryCapacity; j++) {
                if (player->inventory[j] == NULL) {
                    player->inventory[j] = malloc(sizeof(char));
                    *player->inventory[j] = currentRoom->items[i];
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
