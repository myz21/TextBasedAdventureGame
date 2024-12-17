#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for sleep function
#include "Player.h"
#include "Room.h"
#include "GameFunctions.h" // Include GameFunctions.h for function declarations

Room rooms[ROOM_COUNT];
Player player;

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
        printf("Command received: %s (result: %d)\n", command, result);

        if (strcmp(command, "move") == 0) {
            char direction[10];
            printf("Enter direction (up, down, left, right): ");
            scanf("%s", direction);
            movePlayer(&player, direction); // Pass player reference
        } else if (strcmp(command, "pickup") == 0) { 
            // Check for enemy proximity
            if (rooms[player.roomIndex].hasMonster) {
                if (player.positionX == rooms[player.roomIndex].enemyPositionX && 
                    player.positionY == rooms[player.roomIndex].enemyPositionY) {
                    printf("An enemy is nearby! It attacks you for 10 damage!\n");
                    player.health -= 10; // Apply damage
                    printf("Your health is now: %d\n", player.health);
                    // Implement a delay for the attack (2 seconds)
                    sleep(2);
                }
            }
            pickupItem(&player, player.positionX, player.positionY);
        } else if (strcmp(command, "look") == 0) {
            lookAround(&player);
        } else if (strcmp(command, "inventory") == 0) {
            listInventory(&player);
        } else if (strcmp(command, "heal") == 0) {
            healPlayer(&player);
        } else if (strcmp(command, "save") == 0) {
            saveGame("savegame.txt");
        } else if (strcmp(command, "load") == 0) {
            loadGame("savegame.txt");
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
