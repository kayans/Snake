#include "game_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "game.h"
#include "common.h"

// Some handy dandy macros for decompression
#define E_CAP_HEX 0x45
#define E_LOW_HEX 0x65
#define G_CAP_HEX 0x47
#define G_LOW_HEX 0x67
#define S_CAP_HEX 0x53
#define S_LOW_HEX 0x73
#define W_CAP_HEX 0x57
#define W_LOW_HEX 0x77
#define DIGIT_START 0x30
#define DIGIT_END 0x39

/** Initializes the board with walls around the edge of the board.
 *
 * Modifies values pointed to by cells_p, width_p, and height_p and initializes
 * cells array to reflect this default board.
 *
 * Returns INIT_SUCCESS to indicate that it was successful.
 *
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 */
enum board_init_status initialize_default_board(int** cells_p, size_t* width_p,
                                                size_t* height_p) {
    *width_p = 20;
    *height_p = 10;
    int* cells = malloc(20 * 10 * sizeof(int));
    *cells_p = cells;
    for (int i = 0; i < 20 * 10; i++) {
        cells[i] = PLAIN_CELL;
    }

    // Set edge cells!
    // Top and bottom edges:
    for (int i = 0; i < 20; ++i) {
        cells[i] = FLAG_WALL;
        cells[i + (20 * (10 - 1))] = FLAG_WALL;
    }
    // Left and right edges:
    for (int i = 0; i < 10; ++i) {
        cells[i * 20] = FLAG_WALL;
        cells[i * 20 + 20 - 1] = FLAG_WALL;
    }

    // Set grass cells!
    // Top and bottom edges:
    for (int i = 1; i < 19; ++i) {
        cells[i + 20] = FLAG_GRASS;
        cells[i + (20 * (9 - 1))] = FLAG_GRASS;
    }
    // Left and right edges:
    for (int i = 1; i < 9; ++i) {
        cells[i * 20 + 1] = FLAG_GRASS;
        cells[i * 20 + 19 - 1] = FLAG_GRASS;
    }

    // Add snake
    cells[20 * 2 + 2] = FLAG_SNAKE;  

    return INIT_SUCCESS;
}

/** Initialize variables relevant to the game board.
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 *  - snake_p: a pointer to your snake struct (not used until part 3!)
 *  - board_rep: a string representing the initial board. May be NULL for
 * default board.
 */
enum board_init_status initialize_game(int** cells_p, size_t* width_p,
                                       size_t* height_p, snake_t* snake_p,
                                       char* board_rep) {
    // TODO: implement!
    enum board_init_status status;

    // char board_test[] = "B5x10|W10|W1E8W5|W1E8W1|W1E3S1E4W1|W10"; // test 20
    // char board_test[] = "B7x10|W1E1W1E1W1E1W1E1W1S1|E1W1E1W1E1W1E1W1E1W1|E10|W10|W1G1E1G1E1G1E1G1E1W1|W1E1G1E1G1E1G1E1G1W1|W10"; // success, test 18
    // if (board_test != NULL) {
    //     status = decompress_board_str(cells_p, width_p, height_p, snake_p, board_test);
    //     if (status != INIT_SUCCESS){
    //         snake_p->head = NULL;
    //         return status;
    //     }
    //     set_snake_location(cells_p, width_p, height_p, snake_p);
    // }
    if (board_rep != NULL){ // Decompress the board and initialize
        status = decompress_board_str(cells_p, width_p, height_p, snake_p, board_rep);
        if (status != INIT_SUCCESS) {
            snake_p->head = NULL;
            return status;
        }
        set_snake_location(cells_p, width_p, height_p, snake_p);
    }
    else { // Initialize the default board and global variables
        status = initialize_default_board(cells_p, width_p, height_p);
        node_t* new_node = (node_t*) malloc(sizeof(node_t)); // pointer to the snake's head
        new_node->location = 42;
        new_node->next = NULL; // no next body part at start
        new_node->prev = NULL;
        snake_p->head = new_node; //head point to the beginning head node
        // int default_start_location = 42;
        // insert_first(&(snake_p->head), default_start_location);
    }

    if (status == INIT_SUCCESS) {
        snake_p->direction = INPUT_RIGHT; // Default direction
        g_game_over = 0; // Game is start
        g_score = 0; // Initial score is 0
        place_food(*cells_p, *width_p, *height_p);
    }

    return status;
}


/** This function is to help convert char element to int cell data
*/
int get_target_element(char prev_element) {
    switch (prev_element) {
        case 'W':
            return FLAG_WALL;
        case 'G':
            return FLAG_GRASS;
        case 'E':
            return PLAIN_CELL;
        case 'S':
            return FLAG_SNAKE;
    }
    return -1;
}


/** This function is to check digit or not
*/
int is_digit(int c) {
    return (c >= '0') && (c <= '9');
}


void set_snake_location(int** cells, size_t* width_p, size_t* height_p, snake_t* snake_p) {
    for (unsigned int i = 0; i < *width_p * *height_p; i++) {
        if ((*cells)[i] == FLAG_SNAKE) {
            node_t* new_node = (node_t*) malloc(sizeof(node_t)); // pointer to the snake's head
            new_node->location = (int)i;
            new_node->next = NULL; // no next body part at start
            new_node->prev = NULL;
            snake_p->head = new_node; //head point to the beginning head node
            // int start_location = (int)i;
            // insert_first(&(snake_p->head), start_location);
            break;
        }
    }
}


/** This function is to extract number of rows and columns from the first section
* (e.g., 10 and 5 from "B10x5")
*/
enum board_init_status get_board_dimensions(size_t* height_p, size_t* width_p, char* token) {
    if ((!strchr(token, 'B')) | (!strchr(token, 'x'))) {
        printf("ERROR: missing 'B' or 'x'!\n");
        return INIT_ERR_BAD_CHAR;
    }
    
    // Retrieve number of rows and columns
    unsigned int i;
    int is_prev_letter = 0;
    int is_prev_digit = 0;
    int digit;
    
    // Check the first section, i.e., B[..]x[..]
    for (i = 0; i < strlen(token); i++) {
        // Check errors
        if ((i == 0) && (token[i] != 'B')) {
            printf("ERROR: first letter is not 'B'!\n");
            return INIT_ERR_BAD_CHAR;
        }
        else if ((is_prev_digit == 1) && (!is_digit(token[i])) && (token[i] != 'x')) {
            printf("ERROR: letter before width is not 'x'!\n");
            return INIT_ERR_BAD_CHAR;
        }

        // Extract num_rows and num_cols
        if (token[i] == 'B') {
            is_prev_letter = 1;
            is_prev_digit = 0;
        } 
        else if (token[i] == 'x') {
            is_prev_letter = 1;
            is_prev_digit = 0;
            *height_p = digit;
            digit = 0;
        }
        else if (is_digit(token[i])) {
            if (is_prev_letter == 1) {
                is_prev_letter = 0;
                is_prev_digit = 1;
                digit = token[i] - '0';
            } 
            else {
                digit = digit * 10 + (token[i] - '0');
            }
        }
    }
    *width_p = digit;
    return INIT_SUCCESS;
}

/** This function is to extract number of rows and columns from the rest of sections
* (e.g., 1 row and 5 columns from 'W5')
*/
enum board_init_status get_extraction_dimensions(int* our_cells_p, int* cursor_p, size_t* width_p, unsigned int* col_num_p, int* snake_num_p, char* token) {
    // Start extraction of lengths of elements
    unsigned int i;
    int digit; 
    char prev_element;
    int is_prev_letter = 0;
    int is_prev_digit = 0;
    *col_num_p = 0;
    
    for (i = 0; i < strlen(token); i++) {
        // printf("token[%d]: %c\n", i, token[i]);
        // printf("prev_element: %c\n", prev_element);
        
        // Compute col_num
        if (is_digit(token[i])) {
            if (is_prev_letter == 1) {
                digit = token[i] - '0';
                is_prev_letter = 0;
                is_prev_digit = 1;
            }
            // previous char is not letter, which means is digit
            else {
                digit = digit * 10 + (token[i] - '0');
            }
        }
        else if ((token[i] == 'W') | (token[i] == 'G') | (token[i] == 'E') | (token[i] == 'S')) {
            if (prev_element == 'S') {
                *snake_num_p += digit;
            }
            if (is_prev_digit == 1) {
                *col_num_p += digit;
                // Fill in cells for current `prev_element` and `digit` (e.g., "W5" means 5 'W')
                int target_element = get_target_element(prev_element);
                for (int j = *cursor_p; j < (digit + *cursor_p); j++) {
                    our_cells_p[j] = target_element;
                }
                *cursor_p += digit;
                digit = 0;
            }
            prev_element = token[i];
            is_prev_letter = 1;
            is_prev_digit = 0;
        }
        else {
            // printf("Error: Bad Character!\n");
            return INIT_ERR_BAD_CHAR;
        }
        
        // Last element in this section
        if (i == strlen(token) - 1) {
            *col_num_p += digit;
            if (prev_element == 'S') {
                // printf("add ending Snake\n");
                *snake_num_p += digit;
            }
            // Fill in the `cells` based on `digit` and `prev_element`
            int target_element = get_target_element(prev_element);
            for (int j = *cursor_p; j < (digit + *cursor_p); j++) {
                our_cells_p[j] = target_element;
            }
            *cursor_p += digit;
        }
    }

    prev_element = '\0';
    
    //Check col_num = width
    if (*col_num_p != *width_p) {
        // printf("Error: Wrong dimension in width!\n");
        return INIT_ERR_INCORRECT_DIMENSIONS;
    }
    
    return INIT_SUCCESS;
}

/** Takes in a string `compressed` and initializes values pointed to by
 * cells_p, width_p, and height_p accordingly. Arguments:
 *      - cells_p: a pointer to the pointer representing the cells array
 *                 that we would like to initialize.
 *      - width_p: a pointer to the width variable we'd like to initialize.
 *      - height_p: a pointer to the height variable we'd like to initialize.
 *      - snake_p: a pointer to your snake struct (not used until part 3!)
 *      - compressed: a string that contains the representation of the board.
 * Note: We assume that the string will be of the following form:
 * B24x80|E5W2E73|E5W2S1E72... To read it, we scan the string row-by-row
 * (delineated by the `|` character), and read out a letter (E, S or W) a number
 * of times dictated by the number that follows the letter.
 */
enum board_init_status decompress_board_str(int** cells_p, size_t* width_p,
                                            size_t* height_p, snake_t* snake_p,
                                            char* compressed) {
    // TODO: implement!
    enum board_init_status status;
    // printf("board: %s\n", compressed);

    // Step1: Get Board Dimensions: height and width
    char* token;
    char* progress_ptr = NULL;
    char* delimiter = "|";
    token = strtok_r(compressed, delimiter, &progress_ptr);
    status = get_board_dimensions(height_p, width_p, token);
    if (status != INIT_SUCCESS) {
        return status;
    }
    int* cells = malloc(*width_p * *height_p * sizeof(int)); // Initialize board
    *cells_p = cells;

    // Step2: Get Extraction Dimensions: rows_num and col_nums
    token = strtok_r(NULL, delimiter, &progress_ptr);

    unsigned int row_num = 0;
    unsigned int col_num = 0;
    int snake_num = 0;
    int cursor = 0;
    while (token != NULL) {
        row_num++;
        if (row_num > *height_p) {
            return INIT_ERR_INCORRECT_DIMENSIONS;
        }

        status = get_extraction_dimensions(cells, &cursor, width_p, &col_num, &snake_num, token);
        if (status != INIT_SUCCESS) {
            return status;
        }
        // printf("---Section %d---\n", row_num);
        // printf("Token: %s\n", token);
        // printf("col_num: %d\n", col_num);
        // printf("row_num: %d\n", row_num);
        // printf("snake_num: %d\n\n", snake_num);
        token = strtok_r(NULL, delimiter, &progress_ptr);
    }

    // Check row_num = height
    if (row_num != *height_p) {
        // printf("ERROR: Wrong dimension in height!\n");
        return INIT_ERR_INCORRECT_DIMENSIONS;
    }
    
    // Check snake exist
    // printf("Snake number: %d\n", snake_num);
    if (snake_num != 1) {
        // printf("ERROR: snake_num should be 1, but %d found!\n", snake_num);
        return INIT_ERR_WRONG_SNAKE_NUM;
    }

    // // Check wall cells
    // // Check top and bottom walls exist
    // for (unsigned int i = 0; i < *width_p; ++i) {
    //     if ((cells[i] != FLAG_WALL) | (cells[i + (*width_p * (*height_p - 1))] != FLAG_WALL)) {
    //         printf("ERROR: Not complete top/bottom wall!\n");
    //         return INIT_ERR_BAD_CHAR;
    //     }
    // }
    // // Check left and right walls exist
    // for (unsigned int i = 0; i < *height_p; ++i) {
    //     if ((cells[i * (*width_p)] != FLAG_WALL) | (cells[i * (*width_p) + (*width_p - 1)] != FLAG_WALL)) {
    //         printf("ERROR: Not complete left/right wall!\n");
    //         return INIT_ERR_BAD_CHAR;
    //     }
    // } 

    // // Check grass cells!
    // // Check top and bottom grass exist
    // for (unsigned int i = 1; i < (*width_p - 1); ++i) {
    //     if ((cells[i + (*width_p)] != FLAG_GRASS) | (cells[i + ((*width_p) * ((*height_p) - 2))] != FLAG_GRASS )) {
    //         printf("ERROR: Not complete top/bottom grass!\n");
    //         return INIT_ERR_BAD_CHAR;
    //     }
    // }

    // // Check left and right grass exist
    // for (unsigned int i = 1; i < (*height_p - 1); ++i) {
    //     if ( (cells[i * (*width_p) + 1] != FLAG_GRASS) | (cells[i * (*width_p) + (*width_p - 2)] != FLAG_GRASS)) {
    //         printf("ERROR: Not complete left/right grass!\n");
    //         return INIT_ERR_BAD_CHAR;
    //     }
    // }

    return status;
}
