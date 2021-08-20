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

enum MatrixBuffer{
    BACK,
    FRONT,
};

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

    /// returns the with of the entire matrix
    int getWidth();

    /// returns the height of the entire matrix
    int getHeight();

    /// returns the value in a specified place within the back buffer
    bool getValue(int x, int y);

    /// returns the value in a specified place within the given buffer
    bool getValue(int x, int y, MatrixBuffer buffer);

    /// write value to a specific place in back buffer
    void setValue(int x, int y, bool value);

    /// write a matrix to a specified place in back buffer
    void setValues(int x, int y, int width, int height, bool *values);

    /// write a matrix to a specified place in back buffer
    void setValues(int x, int y, int width, int height, bool *values, bool see_through);

    /// swap front and back buffer references
    void swapBuffer();

    /// copies back buffer to front buffer
    void updateFrontBuffer();

    /// cleanse back buffer
    void flushBackBuffer();

    /// write front buffer to flip dot matrix
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

void fill_random(double density, FlipDotMatrix *matrix);