// https://medium.com/coinmonks/flip-dot-display-with-arduino-and-rs485-shield-ca2cec1b971a
// 0x80 beginning
//___________________
// 0x81 - 112 bytes / no refresh / C+3E
// 0x82 - refresh
// 0x83 - 28 bytes of data / refresh / 2C
// 0x84 - 28 bytes of data / no refresh / 2C
// 0x85 - 56 bytes of data / refresh / C+E
// 0x86 - 56 bytes of data / no refresh / C+E
// ---------------------------------------
// address or 0xFF for all
// data ... 1 to nuber of data bytes
// 0x8F end

// panel's speed setting: 1-OFF 2-ON 3 - ON
// panel address : 1 (8 pos dip switch: 1:on 2 -8: off)

// I was sng RS485 Breakout and Duemilanova connected in the following way:
// [Panel]  [RS485]  [Arduino]
// 485+       A
// 485-       B
//          3-5V    5V
//          RX-I    D3
//          TX-O    Not connected
//           RTS    5V
//           GND    GND
#include <Arduino.h>
#include <SoftwareSerial.h>
//#include <vector>
//#include <cassert>



int const m_size = 56;

byte matrix[m_size] = {
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        //
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
};

byte new_matrix[m_size] = {
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        //
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
};

// data prefix
byte data_prefix[] = {0x80, 0x83};

byte panels[] = {0x00, 0x01};

// data prefix
byte data_suffix[] = {0x8F};

uint epoch_delay = 500;

SoftwareSerial flip_dots(D4, D3); // rx (not used), tx
// #####################################################################################################################
// Functions
// #####################################################################################################################

bool get_value(int x, int y, byte *byte_matrix) {
    if (x < 0 && y < 0) {
        return get_value(columns + x, lines + y, byte_matrix);
    }
    if (x < 0) {

        return get_value(columns + x, y, byte_matrix);
    }
    if (y < 0) {
        return get_value(x, lines + y, byte_matrix);
    }


    if (y < 7) {
        return (byte_matrix[x] >> y) & 0b01;
    }
    return (byte_matrix[x+columns] >> (y - 7)) & 0b01;

}

void set_value(int x, int y, bool value, byte *byte_matrix) {

    if (x < 0 && y < 0) {
        return set_value(columns + x, lines + y, value, byte_matrix);
    }
    if (x < 0) {
        return set_value(columns + x, y, value, byte_matrix);
    }
    if (y < 0) {
        return set_value(x, lines + y, value, byte_matrix);
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

void show_on_flip_dots(byte *byte_matrix) {
    flip_dots.write(data_prefix, 2);
    flip_dots.write(panels[0]);
    for (int i = 0; i < m_size / 2; i++) {
        flip_dots.write(byte_matrix[i]);
    }
    flip_dots.write(data_suffix, 1);

    flip_dots.write(data_prefix, 2);
    flip_dots.write(panels[1]);
    for (int i = m_size / 2; i < m_size; i++) {
        flip_dots.write(byte_matrix[i]);
    }
    flip_dots.write(data_suffix, 1);

}

// #####################################################################################################################
// Setup/Loop
// #####################################################################################################################

void setup() {
//    Serial.begin(57600);
    flip_dots.begin(57600);

}

void loop() {
    show_on_flip_dots();
    delay(epoch_delay);
}