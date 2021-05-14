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
//          RX-I    TX
//          TX-O    Not connected
//           RTS    5V
//           GND    GND
#include <Arduino.h>
#include <SoftwareSerial.h>


// numbers font
byte zero[]  = {B0111110, B0100010, B0100010, B0111110};
byte one[]   = {B0111110, B0000000, B0000000, B0000000};
byte two[]   = {B0111010, B0101010, B0101010, B0101110};
byte three[] = {B0111110, B0101010, B0101010, B0100010};
byte four[]  = {B0000100, B0111110, B0000100, B0111100};
byte five[]  = {B0101110, B0101010, B0101010, B0111010};
byte six[]   = {B0001110, B0001010, B0001010, B0111110};
byte seven[] = {B0111110, B0100000, B0100000, B0110000};
byte eight[] = {B0111110, B0101010, B0101010, B0111110};
byte nine[]  = {B0111110, B0101000, B0101000, B0111000};

// first digit
byte side_one[]  = {B0000000, B0111110, B0000000};
byte side_zero[] = {B0000000, B0000000, B0000000};

// brank space
byte space[] = {B0000000};

byte black[] = {B1111111};


// data prefix
byte data_prefix[] = {0x80, 0x83, 0x00};

// data prefix
byte data_suffix[] = {0x8F};

SoftwareSerial matrix(D4, D3);

void setup() {
//    Serial.begin(57600);
    matrix.begin(57600);

}

void loop() {
    // Display random number
//    /*
    int i, j;
    byte r[] = {0};
    for (j = 0; j <= 100; j++){
        matrix.write(data_prefix, 3);
        for (i = 0; i < 28; i++){
            r[0] = random(256);
            matrix.write(r, 1);
        }
        matrix.write(data_suffix, 1);
        delay(50);
    }
    delay(5000);
}