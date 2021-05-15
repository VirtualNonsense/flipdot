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



int const lines = 14;
int const columns = 28;
int const m_size = 2 * columns;

byte matrix[m_size] = {
        B0000111,
        B0000000,
        B0000000,
        B0010000,
        B0001000,
        B0111000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000000,
        B0000001,
        B0000001,
        B0000001,
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

uint epoch_delay = 100;

SoftwareSerial flip_dots(D4, D3); // rx (not used), tx
// #####################################################################################################################
// Functions
// #####################################################################################################################

bool get_value(int x, int y, byte *byte_matrix) {
    if (x < 0 && y < 0) {
        return get_value(columns + x, lines + y, byte_matrix);
    }
    if(x >= columns && y >= lines)
        return get_value(x - columns, lines - y, byte_matrix);
    if (x < 0) {
        return get_value(columns + x, y, byte_matrix);
    }
    if (x >= columns)
        return get_value(x - columns, y, byte_matrix);
    if (y < 0) {
        return get_value(x, lines + y, byte_matrix);
    }
    if(y >= lines)
        return get_value(x, y - lines, byte_matrix);


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

int count_neighbours(int x, int y, byte *byte_matrix) {
    int neighbours = 0;
    for (int r = y - 1; r < y + 2; r++) {
        for (int c = x - 1; c < x + 2; c++) {
            if (c == x && r == y)
                continue;
            if (get_value(c, r, byte_matrix))
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

void calc_next_gen() {
    int n;
    bool alive;
    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < lines; r++) {
            alive = get_value(c, r, matrix);
            n = count_neighbours(c, r, matrix);
            alive = gol_rules(alive, n);
            set_value(c, r, alive, new_matrix);
        }
    }
}


// #####################################################################################################################
// Setup/Loop
// #####################################################################################################################
bool b = true;

void setup() {
    Serial.begin(9600);
    flip_dots.begin(57600);
//    Serial.println(get_value(0,0, matrix));
//    Serial.println(get_value(1,0, matrix));
//    Serial.println(get_value(0,1, matrix));
//    Serial.println(get_value(2,1, matrix));
//    Serial.println(get_value(1,2, matrix));
//    Serial.println(count_neighbours(1,1));
    show_on_flip_dots(matrix);
    delay(epoch_delay);
    Serial.println(count_neighbours(0, 0, matrix));
}

void loop() {
//    for (int r = 0; r < 1; r++) {
//        for (int c = 0; c < columns; c++) {
//            b = get_value(c-1, r, matrix);
//            Serial.println(b);
//            set_value(c, r, !b, matrix);
//            show_on_flip_dots(matrix);
//            delay(epoch_delay/16);
//        }
//    }
    calc_next_gen();
    std::swap(matrix, new_matrix);
    show_on_flip_dots(matrix);
    delay(epoch_delay);
}