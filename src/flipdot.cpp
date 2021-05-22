//
// Created by Andre on 22/05/2021.
//
#include "flipdot.h"

bool get_value(int x, int y, int columns, int lines, byte *byte_matrix) {
    if (x < 0 && y < 0) {
        return get_value(columns + x, lines + y, columns, lines, byte_matrix);
    }
    if (x >= columns && y >= lines)
        return get_value(x - columns, lines - y, columns, lines, byte_matrix);
    if (x < 0) {
        return get_value(columns + x, y, columns, lines, byte_matrix);
    }
    if (x >= columns)
        return get_value(x - columns, y, columns, lines, byte_matrix);
    if (y < 0) {
        return get_value(x, lines + y, columns, lines, byte_matrix);
    }
    if (y >= lines)
        return get_value(x, y - lines, columns, lines, byte_matrix);


    if (y < 7) {
        return (byte_matrix[x] >> y) & 0b01;
    }
    return (byte_matrix[x + columns] >> (y - 7)) & 0b01;

}

void set_value(int x, int y, bool value, int columns, int lines, byte *byte_matrix) {

    if (x < 0 && y < 0) {
        return set_value(columns + x, lines + y, columns, lines, value, byte_matrix);
    }
    if (x < 0) {
        return set_value(columns + x, y, value, columns, lines, byte_matrix);
    }
    if (y < 0) {
        return set_value(x, lines + y, value, columns, lines, byte_matrix);
    }

    if (y < 7) {
        if (value)
            byte_matrix[x] = byte_matrix[x] | 1 << y;
        else
            byte_matrix[x] = byte_matrix[x] ^ (byte_matrix[x] & 1 << y);
        return;
    }
    if (value) {
        byte_matrix[x + columns] = byte_matrix[x + columns] | 1 << (y - 7);
        return;
    }
    byte_matrix[x + columns] = byte_matrix[x + columns] ^ (byte_matrix[x + columns] & 1 << (y - 7));
}