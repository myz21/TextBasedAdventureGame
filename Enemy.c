#include "enemy.h"

void initializeEnemy(Enemy *enemy, const char *name, int health, int strength) {
    strncpy(enemy->name, name, MAX_ENEMY_NAME_LENGTH);
    enemy->health = health;
    enemy->strength = strength;
}
