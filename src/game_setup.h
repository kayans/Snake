#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include <stddef.h>

#include "common.h"
#include "game.h"

/** Enum to communicate board initialization status.
 * Values include INIT_SUCCESS, INIT_ERR_INCORRECT_DIMENSIONS,
 * INIT_ERR_WRONG_SNAKE_NUM, and INIT_ERR_BAD_CHAR.
 */
enum board_init_status {
    INIT_SUCCESS,                   // no errors were thrown
    INIT_ERR_INCORRECT_DIMENSIONS,  // dimensions description was not formatted
                                    // correctly, or too many rows/columns are
                                    // specified anywhere in the string for the
                                    // given dimensions
    INIT_ERR_WRONG_SNAKE_NUM,  // no snake or multiple snakes are on the board
    INIT_ERR_BAD_CHAR,  // any other part of the compressed string was formatted
                        // incorrectly
    INIT_UNIMPLEMENTED  // only used in stencil, no need to handle this
};

enum board_init_status initialize_game(int** cells_p, size_t* width_p,
                                       size_t* height_p, snake_t* snake_p,
                                       char* board_rep);

enum board_init_status decompress_board_str(int** cells_p, size_t* width_p,
                                            size_t* height_p, snake_t* snake_p,
                                            char* compressed);
enum board_init_status initialize_default_board(int** cells_p, size_t* width_p,
                                                size_t* height_p);

int is_digit(int c);
int get_target_element(char prev_element);
void set_snake_location(int** cells, size_t* width_p, size_t* height_p, snake_t* snake_p);
enum board_init_status get_board_dimensions(size_t* height_p, size_t* width_p, char* token);
enum board_init_status get_extraction_dimensions(int* our_cells_p, int* cursor_p, size_t* width_p, unsigned int* col_num_p, int* snake_num_p, char* token);

#endif
