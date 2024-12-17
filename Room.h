#ifndef ROOM_H
#define ROOM_H

#define ROOM_WIDTH 5
#define ROOM_HEIGHT 5
#define ROOM_COUNT 3
#define MAX_ITEMS 10
#include "Player.h" // Include Player.h to recognize the Player type


// I CHANGED
/*
#define WALL "#"
#define EMPTY "."
#define PLAYER "P"
#define KNIFE "K"            
#define SWORD "S"            
#define HEALTH_POTION "H"  
*/

typedef struct {
    int enemyPositionX; // Add enemy X position
    int positionX; // Add room X position
    int positionY; // Add room Y position
    int enemyPositionY; // Add enemy Y position
    char innerMap[ROOM_HEIGHT][ROOM_WIDTH];
    char description[256];
    char items[MAX_ITEMS];
    int itemCount;
    int hasMonster;
    int connections[4];
} Room;
 
extern Room rooms[ROOM_COUNT];

void initializeRooms();
void lookAround(Player *player);

#endif
