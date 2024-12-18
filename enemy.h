#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ENEMY_NAME_LENGTH 50

typedef struct {
    int isDefeated; // New member to indicate if the enemy is defeated
    char name[MAX_ENEMY_NAME_LENGTH];
    int health;
    int strength;
    int positionX;
    int positionY;
    //bool isDefeated; // Track if the enemy is defeated
} Enemy;

void initializeEnemy(Enemy *enemy, const char *name, int health, int strength, int positionX, int positionY);

#endif
