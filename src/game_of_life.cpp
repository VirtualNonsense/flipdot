//
// Created by Andre on 22/05/2021.
//
#include "game_of_life.h"


int count_neighbours(int x, int y, int columns, int lines, byte *byte_matrix) {
    int neighbours = 0;
    for (int r = y - 1; r < y + 2; r++) {
        for (int c = x - 1; c < x + 2; c++) {
            if (c == x && r == y)
                continue;
            if (get_value(c, r, columns, lines, byte_matrix))
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

bool OCA_maze_rules(bool alive, int neighbours) {

    if (neighbours < 1 || neighbours > 5)
        return false;
    if (neighbours == 3)
        return true;
    return alive;
}

void calc_next_gen(byte *byte_matrix, byte *new_byte_matrix, int columns, int lines) {
    int n;
    bool alive;
    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < lines; r++) {
            alive = get_value(c, r, columns, lines, byte_matrix);
            n = count_neighbours(c, r, columns, lines, byte_matrix);
            alive = gol_rules(alive, n);
            set_value(c, r, alive, columns, lines, new_byte_matrix);
        }
    }
}