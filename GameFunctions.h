#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "Player.h"
#include "Room.h"


void movePlayer(Player *player, const char *direction);
void saveGame(const char *filename);
void loadGame(const char *filename);
void lookAround(Player *player); // Add declaration for lookAround

#endif // GAMEFUNCTIONS_H
