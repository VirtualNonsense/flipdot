//
// Created by Andre on 22/05/2021.
//

#ifndef FLIPDOT_FLIPDOT_H
#define FLIPDOT_FLIPDOT_H

#endif //FLIPDOT_FLIPDOT_H
#include <Arduino.h>

bool get_value(int x, int y, int columns, int lines, byte *byte_matrix);
void set_value(int x, int y, bool value, int columns, int lines, byte *byte_matrix);
void fill_random(double density, int m_size, byte *byte_matrix);

