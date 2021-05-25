//
// Created by Andre on 22/05/2021.
//

#ifndef FLIPDOT_GAME_OF_LIFE_H
#define FLIPDOT_GAME_OF_LIFE_H

#endif //FLIPDOT_GAME_OF_LIFE_H
#include "flipdot.h"
const int RULE_COUNT = 4;
enum rule{
    game_of_life,
    oca_maze,
    oca_mazectric,
    day_and_night,
};



int count_neighbours(int x, int y, int columns, int lines, byte *byte_matrix);

void calculate_next_epoch(byte *byte_matrix, byte *new_byte_matrix, rule rule, int columns, int lines);