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

void fill_random(double density, int m_size, byte *byte_matrix) {
    double r;
    for (int i = 0; i < m_size; i++) {
        for (int ii = 0; ii < 7; ii++) {
            r = random(0, 100) / 100.0;
            if (r < density)
                byte_matrix[i] = byte_matrix[i] | 1 << ii;
        }
    }
}
