CSCI 1310 Project 1 - Snake
===========================

# I. Design Overview:

## a. Overview

This project is a modern implementation of the classic Snake game. It is developed in C and utilizes the `ncurses` library for rendering in terminal environments. The game supports UTF-8 encoded multibyte characters, enabling a wide range of text inputs for internationalization purposes.

## b. Design

### Modules
The design of this Snake game project is modular, with each component handling a specific aspect of the game's functionality:

- **Common (`common.h`, `common.c`)**: Defines global variables, enums, and constants that are used throughout the game. This includes game state flags and cell types.

- **Game Setup (`game_setup.h`, `game_setup.c`)**: Responsible for initializing the game environment, including setting up the game board and configuring initial game parameters. This component ensures the game starts with the correct settings and state.

- **Linked List (`linked_list.h`, `linked_list.c`)**: Implements a doubly linked list to manage the snake's body segments. This allows for dynamic growth and movement within the game.

- **Multibyte Strings (`mbstrings.h`, `mbstrings.c`)**: Provides functions for handling UTF-8 encoded strings, crucial for processing player names and ensuring correct display and input handling.

- **Rendering (`render.h`, `render.c`)**: Uses the `ncurses` library to draw the game board, snake, food, and obstacles on the terminal. It handles graphical rendering and window management.

- **Game Logic (`game.h`, `game.c`)**: Contains the core game loop, including input handling, snake movement, collision detection, and game state updates.

- **Main (`snake.c`)**: The entry point for the application, which sets up the game environment, processes command-line arguments, and runs the main game loop.

### Game Flow

1. **Initialization**: Configures the game board and initializes game variables. The board can be set up with default dimensions or customized via command-line arguments.

2. **Main Loop**: Processes user inputs to control the snake, updates the game state based on the snake's position and interactions (e.g., eating food, colliding with walls or itself), and renders the updated game state to the terminal.

3. **Game Over**: Triggers when the snake collides with a wall or itself. The game then displays a game-over screen, cleans up resources, and exits.

### Features

- **Snake Growth**: The snake grows each time it eats food, increasing the challenge as the game progresses.
- **Customizable Board**: The game supports custom board configurations provided as command-line arguments, allowing for varied gameplay experiences.
- **UTF-8 Support**: Ensures that player names and other text inputs can include multibyte characters, supporting internationalization.
- **Terminal Rendering**: Leverages `ncurses` for terminal-based rendering, making the game playable on any system with terminal access.

# II. Extra Credit attempted:

## a. Design

### Better Snake visuals
- **Solid Snake**: Instead of using simple "S" characters to represent the snake, the game now renders the snake as a solid, continuous entity. This is achieved by using a full block character (`\u2588`) and coloring it green, offering a more visually cohesive and appealing representation of the snake.
  
- **Realistic Food Representation**: The food items the snake consumes have been visually upgraded from a basic character representation to more food-like symbols. This includes using specific Unicode characters, enhancing the thematic immersion of the game.

### Grow more than one length on each food

- **Enhanced Growth Mechanismn**: Upon consuming food, the snake can now grow by more than one unit in length. This introduces an adjustable growth rate, determined by the variable g_food_growing_unit in common.c, which can be set to values greater than 1 (e.g. g_food_growing_unit = 2). This mechanic adds an extra layer of challenge and strategy to the game, as players must navigate an increasingly lengthy snake within the confined space of the game board.

## b. Implementation Details
- **Snake and Food Rendering**: The rendering logic has been adjusted in render_game within render.c to accommodate the new visual enhancements. The snake's body segments are rendered using wide characters for a solid appearance, and food items utilize a distinct visual apple symbol.

- **Growth Mechanism**: The growth mechanism is implemented in the update function within game.c, where the snake's growth rate is dynamically adjusted based on the g_food_growing_unit. This allows for increased flexibility in how the snake's growth is handled upon consuming food.
