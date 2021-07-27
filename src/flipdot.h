//
// Created by Andre on 22/05/2021.
//

#ifndef FLIPDOT_FLIPDOT_H
#define FLIPDOT_FLIPDOT_H

#endif //FLIPDOT_FLIPDOT_H

#include <Arduino.h>
#include <SoftwareSerial.h>

bool get_value(int x, int y, int columns, int lines, byte *byte_matrix);

void set_value(int x, int y, bool value, int columns, int lines, byte *byte_matrix);

void fill_random(double density, int m_size, byte *byte_matrix);

class FlipDotMatrix {
public:
    ///
    FlipDotMatrix(int moduleHeight,
                  int moduleWidth,
                  int matrixHeight,
                  int matrixWidth,
                  byte *buffer,
                  byte *backBuffer,
                  SoftwareSerial *dotMatrix);

    ~FlipDotMatrix() {
        free(backBuffer);
        backBuffer = nullptr;
        free(frontBuffer);
        frontBuffer = nullptr;
    }

    int getWidth();

    int getHeight();

    bool getValue(int x, int y);

    void setValue(int x, int y, bool value);

    void swapBuffer();

    void updateFrontBuffer();

    void flushBackBuffer();

    void updateMatrix();

private:

    const byte data_prefix[2] = {0x80, 0x84};

    const byte panels[2] = {0x00, 0x01};

    const byte refresh[3] = {0x80, 0x82, 0x8F};

    // data prefix
    const byte data_suffix[1] = {0x8F};
    SoftwareSerial *dotMatrix;

    int moduleHeight;
    int moduleWidth;
    int matrixHeight;
    int matrixWidth;

    /// determines whether the physical frontBuffer depicts the current front buffer;
    bool matrixUpDated = false;

    /// has the back buffer been updated yet
    bool backBufferClear = false;

    /// frontBuffer state that will be loaded on to the frontBuffer
    byte *frontBuffer;

    /// frontBuffer state depicting the next live state.
    /// this will be edited using the setValue function.
    byte *backBuffer;


};
