#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>

#include "linked_list.h"
#include "mbstrings.h"
#include "common.h"

/** Updates the game by a single step, and modifies the game information
 * accordingly. Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: width of the board.
 *  - height: height of the board.
 *  - snake_p: pointer to your snake struct (not used until part 3!)
 *  - input: the next input.
 *  - growing: 0 if the snake does not grow on eating, 1 if it does.
 */
void update(int* cells, size_t width, size_t height, snake_t* snake_p,
            enum input_key input, int growing) {
    // `update` should update the board, your snake's data, and global
    // variables representing game information to reflect new state. If in the
    // updated position, the snake runs into a wall or itself, it will not move
    // and global variable g_game_over will be 1. Otherwise, it will be moved
    // to the new position. If the snake eats food, the game score (`g_score`)
    // increases by 1. This function assumes that the board is surrounded by
    // walls, so it does not handle the case where a snake runs off the board.

    // TODO: implement!

    // printf("BEFORE: ");
    // for (unsigned int i = 0; i < width * height; i++) {
    //     if (i % width == 0) {
    //         printf("\n");
    //     }
    //     printf("%d", cells[i]);
    // }
    // printf("\n");
    // int g_snake_x = snake_p->head->location / width; // x row from the left (0-based indexing)
    // int g_snake_y = snake_p->head->location % width; // y column down (0-based indexing)
    // printf("g_snake_x: %d\n", g_snake_x);
    // printf("g_snake_y: %d\n", g_snake_y);

    if (g_game_over == 1) {
        return;
    }

    int snake_length = length_list(snake_p->head);
    int old_cell = snake_p->head->location; // old snake head position in cell
    
    int dx = 0; // horizontal movement
    int dy = 0; // vertical movement

    if (input == INPUT_NONE) {
        input = snake_p->direction;
    }
    // if snake length > 1, backing into itself is not allowed
    else if ((snake_length > 1) & (((input == INPUT_UP) & (snake_p->direction == INPUT_DOWN)) | ((input == INPUT_DOWN) & (snake_p->direction == INPUT_UP)) | ((input == INPUT_LEFT) & (snake_p->direction == INPUT_RIGHT)) | ((input == INPUT_RIGHT) & (snake_p->direction == INPUT_LEFT)))) {
        input = snake_p->direction;
    }
    else {
        snake_p->direction = input;
    }

    switch (input) {
        case INPUT_UP:
            dx = -1;
            break;
        case INPUT_DOWN:
            dx = 1;
            break;
        case INPUT_LEFT:
            dy = -1;
            break;
        case INPUT_RIGHT:
            dy = 1;
            break;
        case INPUT_NONE:
            break;
    }
    
    // check whether snake runs into a wall
    int old_x = old_cell / width; // x row from the left (0-based indexing)
    int old_y = old_cell % width; // y column down (0-based indexing)
    int new_cell = width * (old_x + dx) + (old_y + dy); // new snake head position in cell
    if (cells[new_cell] & FLAG_WALL){
        g_game_over = 1;
        return;
    }

    // check whether snake runs into its body
    int is_bite_tail = 0;
    int tail_location = get_last(snake_p->head);
    if (cells[new_cell] & FLAG_SNAKE) {
        if (new_cell == tail_location) {
            is_bite_tail = 1;
        }
        else {
            g_game_over = 1;
            return;
        }
    }

    // This move is valid, so udpate snake location
    // Move head to point to the new location
    insert_first(&(snake_p->head), new_cell);
    // node_t* new_node = (node_t*) malloc(sizeof(node_t));
    // new_node->location = new_cell;
    // new_node->next = snake_p->head;
    // new_node->prev = NULL;
    // snake_p->head->prev = new_node;
    // snake_p->head = new_node;

    // update the new head position's cell state
    cells[new_cell] = cells[new_cell] | FLAG_SNAKE;

    if (growing == 0) {
        // if growing == 0, always free the removed cell
        // remove_last: removes the original tail
        int removed_cell = remove_last(&(snake_p->head));
        // clear the removed cell by removing snake
        // if !bite_tail, then no need to remove tail cell
        if (!is_bite_tail) {
            cells[removed_cell] = cells[removed_cell] ^ FLAG_SNAKE;
        }
    }
    else if (!(cells[new_cell] & FLAG_FOOD)) {
        // if growing == 1 and snake not eating a food, then remove cell according to g_to_be_grown
        // this is to support growing with >1 unit
        if (g_num_to_grow == 0) {
            // remove_last: removes the original tail
            int removed_cell = remove_last(&(snake_p->head));
            // clear the removed cell by removing snake
            // if !bite_tail, then no need to remove tail cell
            if (!is_bite_tail) {
                cells[removed_cell] = cells[removed_cell] ^ FLAG_SNAKE;
            }
        }
        else if (g_num_to_grow > 0) {
            g_num_to_grow -= 1;
        }
    }

    // if snake eats food, update score and replace food
    if (cells[new_cell] & FLAG_FOOD) {
        g_num_to_grow = g_num_to_grow + g_food_growing_unit;
        g_score ++;
        cells[new_cell] = cells[new_cell] ^ FLAG_FOOD;
        place_food(cells, width, height);
        g_num_to_grow -= 1;
    }

    // printf("AFTER: ");
    // for (unsigned int i = 0; i < width * height; i++) {
    //     if (i % width == 0) {
    //         printf("\n");
    //     }
    //     printf("%d", cells[i]);
    // }
    // printf("\n\n\n\n\n");
}

/** Sets a random space on the given board to food.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: the width of the board
 *  - height: the height of the board
 */
void place_food(int* cells, size_t width, size_t height) {
    /* DO NOT MODIFY THIS FUNCTION */
    unsigned food_index = generate_index(width * height);
    // check that the cell is empty or only contains grass
    if ((*(cells + food_index) == PLAIN_CELL) || (*(cells + food_index) == FLAG_GRASS)) {
        *(cells + food_index) |= FLAG_FOOD;
    } else {
        place_food(cells, width, height);
    }
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Prompts the user for their name and saves it in the given buffer.
 * Arguments:
 *  - `write_into`: a pointer to the buffer to be written into.
 */
void read_name(char* write_into) {
    // TODO: implement! (remove the call to strcpy once you begin your implementation)
    // strcpy(write_into, "placeholder");
    printf("Please enter your name: "); // Prompt the user for their name
    fflush(stdout); // forcefully flush the buffer before reading in input

    int file_descriptor = 0; // input via the keyboard
    int bytes_read; // Name bytes
    bytes_read = read(file_descriptor, write_into, 1000); // Read input from the user
    while (bytes_read == 1) {
        printf("Name Invalid: must be longer than 0 characters.\n"); // Continue to prompt the user
        printf("Please re-enter your name: ");
        fflush(stdout); // forcefully flush the buffer before reading in input
        bytes_read = read(file_descriptor, write_into, 1000); // Read input from the user
    }
    write_into[bytes_read - 1] = '\0'; // Replace the newline character with a null terminator
}

/** Cleans up on game over — should free any allocated memory so that the
 * LeakSanitizer doesn't complain.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - snake_p: a pointer to your snake struct. (not needed until part 3)
 */
void teardown(int* cells, snake_t* snake_p) {
    // TODO: implement!
    // Traverse the linked list and free each node.
    node_t* curr = snake_p->head;
    while (curr) {
        node_t* temp = curr;
        curr = curr->next;
        free(temp);
        
        // int removed_cell = remove_first(&curr);
        // printf(removed_cell);
        // free(curr); // Free the current node.
        // curr = temp; // Move to the next node.
    }

    // while (snake_p->head) {
    //     int removed_cell = remove_first(&(snake_p->head));
    //     printf("Location removed: %d\n", removed_cell);
    // }
}
