#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ENEMY_NAME_LENGTH 50

typedef struct {
    char name[MAX_ENEMY_NAME_LENGTH];
    int health;
    int strength;
} Enemy;

void initializeEnemy(Enemy *enemy, const char *name, int health, int strength);

#endif
