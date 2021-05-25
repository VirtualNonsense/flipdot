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


const int s_day_and_night_count = 4;
const int s_day_and_night[] = {
        3,6,7,8
};
const int b_day_and_night_count = 5;
const int b_day_and_night[] = {
        3,4,6,7,8
};

int count_neighbours(int x, int y, int columns, int lines, byte *byte_matrix);

bool gol_rules(bool alive, int neighbours);

bool oca_maze_rules(bool alive, int neighbours);

bool oca_mazectric_rules(bool alive, int neighbours);

void calculate_next_epoch(byte *byte_matrix, byte *new_byte_matrix, rule rule, int columns, int lines);