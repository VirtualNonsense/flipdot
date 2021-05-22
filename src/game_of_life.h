//
// Created by Andre on 22/05/2021.
//

#ifndef FLIPDOT_GAME_OF_LIFE_H
#define FLIPDOT_GAME_OF_LIFE_H

#endif //FLIPDOT_GAME_OF_LIFE_H
#include "flipdot.h"

int count_neighbours(int x, int y, int columns, int lines, byte *byte_matrix);

bool gol_rules(bool alive, int neighbours);

bool oca_maze_rules(bool alive, int neighbours);

void calc_next_gen(byte *byte_matrix, byte *new_byte_matrix, int columns, int lines);