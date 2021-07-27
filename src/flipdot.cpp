//
// Created by Andre on 22/05/2021.
//
#include "flipdot.h"
#include <cstring>

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
        return set_value(columns + x, lines + y, value, columns, lines, byte_matrix);
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
// #####################################################################################################################
// FlipDotMatrix
// #####################################################################################################################
bool FlipDotMatrix::getValue(int x, int y) {

    return getValue(x, y, BACK);
}

bool FlipDotMatrix::getValue(int x, int y, MatrixBuffer buffer) {
    if (x < 0 && y < 0) {
        return getValue(matrixWidth + x, matrixHeight + y, buffer);
    }
    if (x >= matrixWidth && y >= matrixHeight)
        return getValue(x - matrixWidth, matrixHeight - y, buffer);
    if (x < 0) {
        return getValue(matrixWidth + x, y, buffer);
    }
    if (x >= matrixWidth)
        return getValue(x - matrixWidth, y, buffer);
    if (y < 0) {
        return getValue(x, matrixHeight + y, buffer);
    }
    if (y >= matrixHeight)
        return getValue(x, y - matrixHeight, buffer);

    switch (buffer) {
        case FRONT:
            if (y < 7) {
                return (frontBuffer[x] >> y) & 0b01;
            }
            return (frontBuffer[x + matrixWidth] >> (y - 7)) & 0b01;
        case BACK:
            if (y < 7) {
                return (backBuffer[x] >> y) & 0b01;
            }
            return (backBuffer[x + matrixWidth] >> (y - 7)) & 0b01;
    }

}


int FlipDotMatrix::getWidth() {
    return matrixWidth;
}

int FlipDotMatrix::getHeight() {
    return matrixHeight;
}

void FlipDotMatrix::setValue(int x, int y, bool value) {
    matrixUpDated = true;
    if (x < 0 && y < 0) {
        return setValue(matrixWidth + x, matrixHeight + y, value);
    }
    if (x < 0) {
        return setValue(matrixWidth + x, y, value);
    }
    if (y < 0) {
        return setValue(x, matrixHeight + y, value);
    }
    //TODO: find a more general approach....
    if (y < 7) {
        if (value)
            backBuffer[x] = backBuffer[x] | 1 << y;
        else
            backBuffer[x] = backBuffer[x] ^ (backBuffer[x] & 1 << y);
        return;
    }
    if (value) {
        backBuffer[x + matrixWidth] = backBuffer[x + matrixWidth] | 1 << (y - 7);
        return;
    }
    backBuffer[x + matrixWidth] = backBuffer[x + matrixWidth] ^ (backBuffer[x + matrixWidth] & 1 << (y - 7));

}

FlipDotMatrix::FlipDotMatrix(int moduleHeight,
                             int moduleWidth,
                             int matrixHeight,
                             int matrixWidth,
                             byte *buffer,
                             byte *backBuffer,
                             SoftwareSerial *dotMatrix) {
    this->moduleHeight = moduleHeight;
    this->moduleWidth = moduleWidth;
    this->matrixHeight = matrixHeight;
    this->matrixWidth = matrixWidth;
    this->frontBuffer = buffer;
    this->backBuffer = backBuffer;
    this->dotMatrix = dotMatrix;

}

void FlipDotMatrix::swapBuffer() {
    std::swap(frontBuffer, backBuffer);
}


void FlipDotMatrix::updateMatrix() {
    if (!matrixUpDated) {
        return;
    }
    matrixUpDated = false;
    Serial.println("writing to matrix");
    dotMatrix->write(data_prefix, 2);
    dotMatrix->write(panels[0]);
    for (int i = 0; i < matrixWidth; i++) {
        dotMatrix->write(frontBuffer[i]);
    }
    dotMatrix->write(data_suffix, 1);

    dotMatrix->write(data_prefix, 2);
    dotMatrix->write(panels[1]);
    for (int i = matrixWidth; i < 2 * matrixWidth; i++) {
        dotMatrix->write(frontBuffer[i]);
    }
    dotMatrix->write(data_suffix, 1);
    dotMatrix->write(refresh, 3);
    Serial.println("flushing back buffer");
}

void FlipDotMatrix::flushBackBuffer() {
    for (int i = 0; i < 2 * matrixWidth; ++i) {
        backBuffer[i] = 0;
    }
}

void FlipDotMatrix::updateFrontBuffer() {
    std::memcpy(frontBuffer, backBuffer, 2 * matrixWidth);
}

