#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "Player.h"
#include "Room.h"

#define KNIFE "K"
#define SWORD "S"
#define HEALTH_POTION "H"

void movePlayer(Player *player, const char *direction);
void saveGame(const char *filename);
void loadGame(const char *filename);

#endif // GAMEFUNCTIONS_H
