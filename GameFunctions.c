#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // Include for directory types
#include "Player.h"
#include "Room.h"

void saveGame(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error saving game.\n");
        return;
    }

    // Save player state
    fprintf(file, "Player Name: %s\n", player.name);
    fprintf(file, "Health: %d\n", player.health);
    fprintf(file, "Position: (%d, %d)\n", player.positionX, player.positionY);
    fprintf(file, "Score: %d\n", player.score); //UPDATE

    // Save room state
    for (int i = 0; i < ROOM_COUNT; i++) {
        fprintf(file, "Room %d:\n", i);
        fprintf(file, "Description: %s\n", rooms[i].description);
        fprintf(file, "Items: ");
        for (int j = 0; j < rooms[i].itemCount; j++) {
            fprintf(file, "%c ", rooms[i].items[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Game saved successfully to %s.\n", filename);
}

void loadGame(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error loading game from %s.\n", filename);
        return;
    }

    // Load player state and print debug information
    char line[100];
    fgets(line, sizeof(line), file);
    printf("Line read for health: %s", line); // Debug statement
    sscanf(line, "Health: %d\n", &player.health);
    fscanf(file, "Score: %d\n", &player.score); // Load score
    printf("Loading player state...\n");
    fscanf(file, "Player Name: %s\n", player.name);
    // Debug statement to check raw input for health
    int healthInput;
    fscanf(file, "Health: %d\n", &healthInput);
    player.health = healthInput;
    printf("Raw Health Input: %d\n", healthInput); // Debug statement
    fscanf(file, "Position: (%d, %d)\n", &player.positionX, &player.positionY);

    // Load room state
    for (int i = 0; i < ROOM_COUNT; i++) {
        fscanf(file, "Room %d:\n", &i);
        fscanf(file, "Description: %[^\n]\n", rooms[i].description);
        rooms[i].itemCount = 0; // Reset item count before loading
        fscanf(file, "Items: ");
        char item;
        while (fscanf(file, " %c", &item) == 1) {
            rooms[i].items[rooms[i].itemCount++] = item;
        }
    }

    fclose(file);
    //updated
    printf("Game loaded successfully. Your score: %d\n", player.score);
}

void movePlayer(Player *player, const char *direction) {
    printf("Attempting to move. Current Position: (%d, %d), Room Index: %d\n", player->positionX, player->positionY, player->roomIndex);
    Room currentRoom = rooms[player->roomIndex]; // Get the current room
    int newX = player->positionX;
    int newY = player->positionY;

    // Calculate the new position based on the direction
    if (strcmp(direction, "up") == 0) newY--;
    else if (strcmp(direction, "down") == 0) newY++;
    else if (strcmp(direction, "left") == 0) newX--;
    else if (strcmp(direction, "right") == 0) newX++;
    else {
        printf("Invalid direction!\n");
        return;
    }

    // 1. If the player attempts to move outside the current room boundaries, check for room connections
    if (newX < 0 || newX >= ROOM_WIDTH || newY < 0 || newY >= ROOM_HEIGHT) {
        int directionIndex = (strcmp(direction, "up") == 0) ? 0 :   // North
                             (strcmp(direction, "down") == 0) ? 2 : // South
                             (strcmp(direction, "left") == 0) ? 3 : // West
                             1;  // East

        // Check if there is a valid room connection in the given direction
        if (currentRoom.connections[directionIndex] != -1) {
            player->roomIndex = currentRoom.connections[directionIndex]; // Update to the next room
            printf("You moved to Room %d.\n", player->roomIndex);

            // Adjust the player's position in the new room based on the movement direction
            if (directionIndex == 0) {       // Moving North
                player->positionY = ROOM_HEIGHT - 1; // Enter at the bottom of the new room
            } else if (directionIndex == 2) { // Moving South
                player->positionY = 0; // Enter at the top of the new room
            } else if (directionIndex == 1) { // Moving East
                player->positionX = 0; // Enter at the left side of the new room
            } else if (directionIndex == 3) { // Moving West
                player->positionX = ROOM_WIDTH - 1; // Enter at the right side of the new room
            }
        } else {
            printf("You can't move in that direction!\n");
        }
    } 
    // 2. If the player stays within the room boundaries, update the position
    else {
        player->positionX = newX;
        player->positionY = newY;
        printf("Player moved %s to position (%d, %d).\n", direction, newX, newY);
    }
}


//I CHANGED
void lookAround(Player *player) {
    Room currentRoom = rooms[player->roomIndex];
    printf("\n%s\n", currentRoom.description); // Print room description

    printf("Room Layout:\n");    
    for (int i = 0; i < ROOM_HEIGHT; i++) {
        for (int j = 0; j < ROOM_WIDTH; j++) {
            if (i == player->positionY && j == player->positionX) {
                printf("P "); // Show the player
            } else {
                char cell = currentRoom.innerMap[i][j];
                if (cell == '\0' || cell == ' ') { // If empty, show a dot
                    printf(". ");
                } else {
                    printf("%c ", cell); // Show item or enemy
                }
            }
        }
        printf("\n");
    }
}



void listSavedGames() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("saved_games")) != NULL) {
        printf("Saved games:\n");
        while ((ent = readdir(dir)) != NULL) {
            // Print all entries, excluding "." and ".."
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                printf("%s\n", ent->d_name);
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
}
