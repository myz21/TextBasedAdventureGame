#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for sleep function
#include "Room.h"
#include "Player.h"
#include "enemy.h"
#include "GameFunctions.h" // Include GameFunctions.h for function declarations

Room rooms[ROOM_COUNT];
Player player;
//ADDED

// Function declarations
void movePlayer(Player *player, const char *direction);
void saveGame(const char *filename);
void loadGame(const char *filename);
void pickupItem(Player *player, int positionX, int positionY);
void lookAround(Player *player);
void healPlayer(Player *player);
void listInventory(Player *player);



void gameLoop() {
    char command[20];
    while (1) {
        
        printf("\nEnter a command (move, pickup, inventory, heal, save <filepath>, load <filepath>, list, look, exit): ");
        printf("Current Player Position: (%d, %d), Room Index: %d\n", player.positionX, player.positionY, player.roomIndex);
        
        int result = scanf("%s", command);

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        
        printf("Command received: %s (result: %d)\n", command, result);

        if (strcmp(command, "move") == 0) {
            char direction[10];
            printf("Enter direction (up, down, left, right): ");
            scanf("%s", direction);
            movePlayer(&player, direction); // Pass player reference
        } else if (strcmp(command, "pickup") == 0) { 
            pickupItem(&player, player.positionX, player.positionY);
        } else if (strcmp(command, "look") == 0) {
            lookAround(&player);
        }
        else if (strcmp(command, "inventory") == 0) {
            listInventory(&player);
        } else if (strcmp(command, "heal") == 0) {
            healPlayer(&player);
        } else if (strcmp(command, "save") == 0) {
            saveGame("savegame.txt");
        } else if (strcmp(command, "load") == 0) {
            loadGame("savegame.txt");
        } else if (strcmp(command, "attack") == 0) {
            int enemyFound = 0;
            Room currentRoom = rooms[player.roomIndex];
            for (int i = 0; i < ENEMY_LENGTH; i++) {
                Enemy enemy = currentRoom.enemies[i];
                if (!enemy.isDefeated && enemy.positionX == player.positionX && enemy.positionY == player.positionY) {
                    printf("\nENEMY IS HERE\n");
                    //printf("weapon::::: %s", player.currentWeapon);
                    attack(&player, &enemy, player.currentWeapon);
                    enemyFound = 1;
                    if (player.health <= 0) {
                        printf("You died! Game over.\n");
                        return; // Exit the loop and end the game
                    }
                    break;
                }
            }
            if (!enemyFound) {
                printf("No enemy here to attack!\n");
            }
        } else if (strcmp(command, "quit") == 0) {
            printf("Exiting game. Goodbye!\n");
            break;
        } else {
            printf("Unknown command!\n");
        }

        // Debug statement to check player's health after loading
        printf("Player Health after loading: %d\n", player.health);
        if (player.health <= 0) {
            printf("You died! Restarting the game...\n");
            //player->score = 0;
            initializePlayer(&player);
            initializeRooms(&player);
            printf("Game restarted.\n");
        }
    }
}

int main() {
    // Check if loading a game
    char loadGameFlag;
    printf("Do you want to load a saved game? (y/n): ");
    scanf(" %c", &loadGameFlag);
    if (loadGameFlag == 'y') {
        loadGame("savegame.txt");
    } else {
        initializeRooms(&player);
        initializePlayer(&player);
    }
    gameLoop();
    return 0;
}
