CSCI 0300 Project 1 - Snake
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

# II. Collaborators:

# III. Responsible Computing:
Partner CS login: bwilli48

1. **Who founded the Consortium? Who is represented among the current members, and how might that affect decisions being made for Unicode?**

    Consortium was founded by engineers from Xerox (Joe Becker) and Apple (Lee Collins and Mark Davis). Mark Davis was the president of the Unicode Consortium from when the Consortium was incorporated in 1991 until 2023 when he changed roles to CTO.  

    The current members represented in the Consortium include a wide range of computer software and hardware companies with an interest in text-processing standards. Some of the notable voting members are Adobe, Apple, the Bangladesh Computer Council, Emojipedia, Facebook, Google, IBM, Microsoft, the Omani Ministry of Endowments and Religious Affairs, Monotype Imaging, Netflix, Salesforce, SAP SE, Tamil Virtual Academy, and the University of California, Berkeley.

    The diverse membership of the Unicode Consortium, including major tech companies, significantly influences Unicode decisions. These members aim to ensure the standard meets the global needs of their customers, affecting language, script, and symbol representation in digital communication. While their involvement keeps Unicode up-to-date with technological and societal trends, it raises concerns about the influence balance, possibly overshadowing smaller communities' needs. 

2. **Find a language that is not yet in Unicode, has only recently been supported (e.g., in the last 10 years), or is/was missing important characters. What is/was missing, and how does this affect the users of the language?**

    The Adlam script, developed in the late 1980s for the Fulani language spoken across West Africa, was included in Unicode Version 9.0 in 2016. Before its inclusion, the Fulani language lacked a dedicated digital writing system, impacting literacy, cultural preservation, and communication. The absence of Adlam in digital formats restricted the development of educational resources, risked the loss of cultural heritage, and complicated written communication for Fulani speakers.

    Unicode's support for Adlam now enables digital content creation in Fulfulde, supporting literacy efforts and cultural documentation. It facilitates accurate digital communication among Fulani speakers, enhancing the visibility and use of the language online. This inclusion marks a significant step in preserving and promoting the Fulani language and culture in the digital realm.

3. **Unicode has also faced controversies with representing (and unifying) similar languages. One of the biggest controversies is Han unification, an attempt to unify the Chinese, Japanese, and Korean (CJK) languages into one common encoding.**

- **Position against Han Unification**:

    Critics of Han Unification argue it neglects the cultural and linguistic nuances of Chinese, Japanese, and Korean scripts by unifying visually and contextually distinct characters under single code points. This process fails to respect the unique developments and significances of characters across languages, risking cultural erasure and misunderstanding in digital communication. The simplification may lead to a loss of linguistic heritage and compromises the accurate digital representation crucial for maintaining each language's integrity.

    Opposition to Han Unification also highlights its negative impact on users and scholars, stressing that it hinders educational and research efforts by blurring historical and dialectical character variations. This one-size-fits-all approach to encoding complicates digital resource development for language learning, sidelining the diverse needs of those dedicated to studying and preserving East Asian languages. This situation raises broader concerns about the effects of digital standards on maintaining linguistic diversity and cultural heritage.

- **Tradeoff of Unicode**:

    In implementing Han Unification, Unicode made a tradeoff that prioritizes efficiency and universality over the accurate representation of linguistic and cultural diversity. By choosing to unify the Han characters across multiple languages into a single code point, Unicode aimed to simplify the encoding process, reduce the complexity of text processing, and ensure compatibility across different digital platforms and systems. This decision reflects a prioritization of technical and operational "goods" such as memory efficiency and the ease of software development. However, it comes at the expense of "goods" like accuracy in cultural representation, fairness to the unique identities of each language, and the sustainability of linguistic diversity. While the efficiency gained is undeniable, the simplification process has sparked debates about the balance between universal digital standards and the preservation of cultural and linguistic nuances.

- **Summary between my partner and me**:

    We explored the nuanced debate surrounding Han Unification from opposing perspectives. Wiiliams argued for the benefits of Han Unification, emphasizing its role in promoting efficiency, consistency, and interoperability in the digital processing of East Asian texts. On the other hand, I highlighted the cultural, linguistic, and practical concerns that arise from such a unification, pointing out the potential loss of meaning, cultural erasure, and the practical challenges faced by users and scholars. Throughout our discussion, we encountered a common understanding of the complexity of this issue, recognizing the tradeoffs made by Unicode in its decision. While we acknowledged the technical advantages of a unified approach, we also agreed on the importance of respecting and preserving linguistic diversity and cultural heritage in the digital age. This dialogue underscored the ongoing challenge of balancing universal digital standards with the nuances of human languages and cultures. 

# IV. Extra Credit attempted:

## a. Design

### Better Snake visuals
- **Solid Snake**: Instead of using simple "S" characters to represent the snake, the game now renders the snake as a solid, continuous entity. This is achieved by using a full block character (`\u2588`) and coloring it green, offering a more visually cohesive and appealing representation of the snake.
  
- **Realistic Food Representation**: The food items the snake consumes have been visually upgraded from a basic character representation to more food-like symbols. This includes using specific Unicode characters, enhancing the thematic immersion of the game.

### Grow more than one length on each food

- **Enhanced Growth Mechanismn**: Upon consuming food, the snake can now grow by more than one unit in length. This introduces an adjustable growth rate, determined by the variable g_food_growing_unit in common.c, which can be set to values greater than 1 (e.g. g_food_growing_unit = 2). This mechanic adds an extra layer of challenge and strategy to the game, as players must navigate an increasingly lengthy snake within the confined space of the game board.

## b. Implementation Details
- **Snake and Food Rendering**: The rendering logic has been adjusted in render_game within render.c to accommodate the new visual enhancements. The snake's body segments are rendered using wide characters for a solid appearance, and food items utilize a distinct visual apple symbol.

- **Growth Mechanism**: The growth mechanism is implemented in the update function within game.c, where the snake's growth rate is dynamically adjusted based on the g_food_growing_unit. This allows for increased flexibility in how the snake's growth is handled upon consuming food.


# V. How long did it take to complete Snake?

30 hours

<!-- Enter an approximate number of hours that you spent actively working on the project. -->
