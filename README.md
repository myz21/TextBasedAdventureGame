# Text-Based Adventure Game

This is a text-based adventure game where the player explores different rooms, collects items, fights monsters, and tries to survive using strategic decisions. The player interacts with the game by typing commands.

## Table of Contents

- [How to Play](#how-to-play)
- [Features](#features)
- [Installation](#installation)
- [Game Commands](#game-commands)
- [Code Structure](#code-structure)
- [Contributing](#contributing)
- [License](#license)

---

## How to Play
1. Start the game by running the compiled executable.
2. Use simple text-based commands (e.g., `move`, `pickup`, `look`) to interact with the game world.
3. Explore rooms, pick up items, fight enemies, and heal when necessary.
4. Save and load your progress to continue your adventure at any time.

Example gameplay flow:
- Enter a command like `move` and specify a direction (e.g., `up`, `down`).
- Pick up weapons such as **K** (Knife) or **S** (Sword) for combat.
- Heal your health using **H** (Health Potion).

## Features
- **Room Exploration**: Navigate through a grid-based world with interconnected rooms.
- **Item Management**: Collect and manage items such as health potions, knives, and swords.
- **Combat System**: Attack enemies using weapons.
- **Health Management**: Heal using collected health potions.
- **Save/Load Progress**: Save your current progress and reload from the same state.
- **Score Tracking**: Track your score by defeating enemies.

---

## Installation
1. Clone this repository:
   ```bash
   git clone  https://github.com/myz21/TextBasedAdventureGame.git
   cd text-adventure-game
   ```
2. Compile the source code using the provided **Makefile**:
   ```bash
   make
   ```
3. Run the game:
   ```bash
   ./game.exe
   ```

### Clean up generated files:
   ```bash
   make clean
   ```

---

## Game Commands
Here are the available commands in the game:

| **Command**   | **Description**                         |
|-------------- |----------------------------------------|
| `move`       | Move the player in a specified direction (e.g., `up`, `down`). |
| `pickup`     | Pick up items in the current room.      |
| `look`       | Inspect the current room layout.        |
| `inventory`  | Display the player’s inventory.         |
| `heal`       | Use a health potion to restore health.  |
| `save`       | Save the current game state.            |
| `load`       | Load a previously saved game.           |
| `list`       | List all saved games (in the save folder).|
| `quit`       | Quit the game.                          |

---

## Code Structure
The project uses a modular design to organize core functionalities:

```
/TextBasedAdventureGame
├── TextBasedAdventureGame.c   // Main game loop
├── GameFunctions.c            // Game functions (save/load, move)
├── Player.c                   // Player-related logic
├── Room.c                     // Room initialization and exploration
├── Player.h                   // Player struct and declarations
├── Room.h                     // Room struct and declarations
├── enemy.h                    // Enemy struct and declarations
├── Makefile                   // Build automation
└── savegame.txt               // Example save file
```

### Key Components
1. **Main Loop**: Manages user commands and game flow.
2. **Player Management**: Handles player health, inventory, and combat.
3. **Room Initialization**: Generates rooms, items, and enemies.
4. **Game State Management**: Provides save/load functionality to persist progress.

---

## Contributing
Contributions are welcome! If you’d like to improve the game or fix bugs:
1. Fork this repository.
2. Create a new branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add your feature or fix"
   ```
4. Push to the branch:
   ```bash
   git push origin feature/your-feature-name
   ```
5. Open a pull request.

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
