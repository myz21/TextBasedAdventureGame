#include "Room.h"
#include "Player.h" // Include Player.h for Player structure
#include <time.h>
#include <string.h>

void printRoomDiagram(Player *player, int roomIndex) {
    // Print the room description
    if (rooms[roomIndex].description[0] != '\0') {
        printf("%s\n", rooms[roomIndex].description);
    } else {
        printf("Room description not available.\n");
    }
    
    printf("Room Diagram:\n");
    for (int i = 0; i < ROOM_HEIGHT; i++) {
        for (int j = 0; j < ROOM_WIDTH; j++) {
            if (i == player->positionY && j == player->positionX) {
                printf("P "); // Player's position
            } else {
                printf("%c ", rooms[roomIndex].innerMap[i][j]); // Display items
            }
        }
        printf("\n");
    }
}

void describeAdjacentRooms(Player *player, int roomIndex) {
    printf("You see:\n");
    if (roomIndex >= ROOM_WIDTH) {
        printf("In the up: %s\n", rooms[roomIndex - ROOM_WIDTH].description);
    } else {
        printf("In the up: none\n");
    }
    
    if (roomIndex < ROOM_COUNT - ROOM_WIDTH) {
        printf("In the down: %s\n", rooms[roomIndex + ROOM_WIDTH].description);
    } else {
        printf("In the down: none\n");
    }
    
    if (roomIndex % ROOM_WIDTH > 0) {
        printf("In the left: %s\n", rooms[roomIndex - 1].description);
    } else {
        printf("In the left: none\n");
    }
    
    if (roomIndex % ROOM_WIDTH < ROOM_WIDTH - 1) {
        printf("In the right: %s\n", rooms[roomIndex + 1].description);
    } else {
        printf("In the right: none\n");
    }
}

void initializeRooms(Player *player) {
    // Initialize rooms
    printf("Initializing rooms...\n");

    // Initialize rooms
    for (int roomIndex = 0; roomIndex < ROOM_COUNT; roomIndex++) {
        // Set room descriptions and initialize enemies
        int enemyCount = ENEMY_LENGTH;

        for (int e = 0; e < enemyCount; e++) {
            int enemyX = rand() % ROOM_WIDTH; // Random X position
            int enemyY = rand() % ROOM_HEIGHT; // Random Y position

            // Ensure the enemy does not spawn on the player or items
            while ((enemyX == player->positionX && enemyY == player->positionY) || 
                   (rooms[roomIndex].innerMap[enemyY][enemyX] != '\0')) {
                enemyX = rand() % ROOM_WIDTH;
                enemyY = rand() % ROOM_HEIGHT;
            }

            // Initialize the enemy
            initializeEnemy(&rooms[roomIndex].enemies[e], "Goblin", 20, 5, enemyX, enemyY);
            rooms[roomIndex].innerMap[enemyY][enemyX] = 'E'; // Place enemy in the room
            //printf("Enemy position: (%d, %d)\n", enemyX, enemyY);
        }
        if (roomIndex == 0) {
            strcpy(rooms[roomIndex].description, "A dark and eerie room.");
        } else if (roomIndex == 1) {
            strcpy(rooms[roomIndex].description, "A bright and sunny room.");
        } else {
            strcpy(rooms[roomIndex].description, "A mysterious room filled with shadows.");
        }

        int itemCount = rand() % 3 + 1; // Random number of items (1 to 3)
        for (int i = 0; i < itemCount; i++) {
            int itemType = rand() % 3; // Randomly choose item type
            if (itemType == 0) {
                rooms[roomIndex].items[i] = 'H'; // For HEALTH_POTION
                rooms[roomIndex].innerMap[1][1] = 'H'; // Place health potion in the room
            } else if (itemType == 1) {
                rooms[roomIndex].items[i] = 'K'; // For KNIFE
                rooms[roomIndex].innerMap[2][2] = 'K'; // Place knife in the room
            } else {
                rooms[roomIndex].items[i] = 'S'; // For SWORD
                rooms[roomIndex].innerMap[3][3] = 'S'; // Place sword in the room
            }
        }
        rooms[roomIndex].itemCount = itemCount; // Set the item count

        // Print the room diagram after items are placed
        printRoomDiagram(player, roomIndex);
    }
}


