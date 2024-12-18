#include "enemy.h"
#include <string.h> // Include for strncpy

void initializeEnemy(Enemy *enemy, const char *name, int health, int strength, int positionX, int positionY) {
    strncpy(enemy->name, name, MAX_ENEMY_NAME_LENGTH - 1);
    enemy->name[MAX_ENEMY_NAME_LENGTH - 1] = '\0'; // Ensure null-terminated string
    enemy->health = health;
    enemy->strength = strength;
    enemy->positionX = positionX; // Set initial X position
    enemy->positionY = positionY; // Set initial Y position
    enemy->isDefeated = 0; // Mark the enemy as not defeated initially
}
