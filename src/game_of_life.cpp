//
// Created by Andre on 22/05/2021.
//
#include "game_of_life.h"



int count_neighbours(int x, int y, FlipDotMatrix *matrix) {
    int neighbours = 0;
    for (int r = y - 1; r < y + 2; r++) {
        for (int c = x - 1; c < x + 2; c++) {
            if (c == x && r == y)
                continue;
            if (matrix->getValue(c, r, FRONT))
                neighbours++;
        }
    }
    return neighbours;
}

bool gol_rules(bool alive, int neighbours) {
    if (neighbours < 2 || neighbours > 3)
        return false;
    if (neighbours == 3)
        return true;
    return alive;
}

bool oca_maze_rules(bool alive, int neighbours) {

    if (neighbours < 1 || neighbours > 5)
        return false;
    if (neighbours == 3)
        return true;
    return alive;
}

bool oca_mazectric_rules(bool alive, int neighbours) {

    if (neighbours < 1 || neighbours > 4)
        return false;
    if (neighbours == 3)
        return true;
    return alive;
}
bool generic_rules(bool alive, int neighbours, int b_count, int s_count, const int *b_list, const int *s_list){
    if(alive){
        for (int i = 0; i < s_count; i++){
            if(s_list[i] == neighbours)
                return true;
        }
        return false;
    }
    for (int i = 0; i < b_count; i++){
        if(b_list[i] == neighbours)
            return true;
    }
    return false;
}

//######################################################################################################################
// RULES
//######################################################################################################################
const int s_day_and_night_count = 4;
const int s_day_and_night[] = {
        3,6,7,8
};
const int b_day_and_night_count = 5;
const int b_day_and_night[] = {
        3,4,6,7,8
};


void calculate_next_epoch(FlipDotMatrix *matrix, rule rule){
    int n;
    bool alive;
    for (int c = 0; c < matrix->getWidth(); c++) {
        for (int r = 0; r < matrix->getHeight(); r++) {
            alive = matrix->getValue(c, r, FRONT);
            n = count_neighbours(c, r, matrix);
            switch (rule) {
                case game_of_life:
                    alive = gol_rules(alive, n);
                    break;
                case oca_maze:
                    alive = oca_maze_rules(alive, n);
                    break;
                case oca_mazectric:
                    alive = oca_mazectric_rules(alive, n);
                    break;
                case day_and_night:
                    alive = generic_rules(alive, n, b_day_and_night_count, s_day_and_night_count, b_day_and_night, s_day_and_night);
                    break;
            }
            matrix->setValue(c, r, alive);
        }
    }
}