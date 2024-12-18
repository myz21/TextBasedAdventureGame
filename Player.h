#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "enemy.h" // Include enemy.h to recognize the Enemy type
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ITEMS 10

typedef struct {
    char name[50];
    int health;
    int strength;
    int inventoryCapacity;
    char *inventory[MAX_ITEMS];
    int positionX, positionY;
    int roomIndex; // Index of the room the player is currently in
    int score; // Player's score
    const char *currentWeapon; // Add currentWeapon member
} Player;

void initializePlayer(Player *player);
void pickupItem(Player *player, int positionX, int positionY);
void listInventory(Player *player);
void healPlayer(Player *player);
void attack(Player *player, Enemy *enemy, const char *weapon);

extern Player player; // Declare player variable as external

#endif
