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
// data ... 1 to number of data bytes
// 0x8F end

// panel's speed setting: 1-OFF 2-ON 3 - ON
// panel address : 1 (8 pos dip switch: 1:on 2 -8: off)

// The RS485 breakout board is connected in the following way:
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
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include "secrets.h"


// #####################################################################################################################
// Parameter
// #####################################################################################################################
// WiFi stuff - CHANGE FOR YOUR OWN NETWORK!
const IPAddress ip(192, 168, 47, 9);  // IP address that THIS DEVICE should request
const IPAddress gateway(192, 168, 47, 1);  // Your router
const IPAddress subnet(255, 255, 255, 0);  // Your subnet mask (find it from your router's admin panel)
const int recv_port = 42069;  // OTA Port

// matrix setup
int const lines = 14;
int const columns = 28;
int const m_size = 2 * columns;

byte matrix[m_size];

byte new_matrix[m_size];

byte data_prefix[] = {0x80, 0x84};

byte panels[] = {0x00, 0x01};

byte refresh[] = {0x80, 0x82, 0x8F};

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
    if (x >= columns && y >= lines)
        return get_value(x - columns, lines - y, byte_matrix);
    if (x < 0) {
        return get_value(columns + x, y, byte_matrix);
    }
    if (x >= columns)
        return get_value(x - columns, y, byte_matrix);
    if (y < 0) {
        return get_value(x, lines + y, byte_matrix);
    }
    if (y >= lines)
        return get_value(x, y - lines, byte_matrix);


    if (y < 7) {
        return (byte_matrix[x] >> y) & 0b01;
    }
    return (byte_matrix[x + columns] >> (y - 7)) & 0b01;

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


void fill_random(double density, byte *byte_matrix) {
    double r;
    for (int i = 0; i < m_size; i++) {
        for (int ii = 0; ii < 7; ii++) {
            r = random(0, 100) / 100.0;
            if (r < density)
                byte_matrix[i] = byte_matrix[i] | 1 << ii;
        }
    }
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
    flip_dots.write(refresh, 3);

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

//bool OCA_maze_rules(bool alive, int neighbours) {
//
//    if (neighbours < 1 || neighbours > 5)
//        return false;
//    if (neighbours == 3)
//        return true;
//    return alive;
//}

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

void setup() {
    // #################################################################################################################
    // system setup
    Serial.begin(9600);
    flip_dots.begin(57600);
    Serial.println("setting up wifi!");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    WiFi.config(ip, gateway, subnet);
    WiFi.hostname("flip dot matrix");
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
    Serial.println("Wifi setup success!");
    ArduinoOTA.setHostname("Flip-dot-matrix");
    ArduinoOTA.setPort(recv_port);

    Serial.println("Setting up wireless firmware updates");
    // Wireless OTA updating? On an ARDUINO?! It's more likely than you think!
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        else // U_SPIFFS
            type = "filesystem";

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Serial.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

    ArduinoOTA.begin();
    Serial.println("setup finished!");

    Serial.println("Ready for WiFi OTA updates");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    // #################################################################################################################
    // Matrix setup
    fill_random(.22, matrix);
}

void loop() {
    ArduinoOTA.handle();
    calc_next_gen();
    std::swap(matrix, new_matrix);
    show_on_flip_dots(matrix);
    delay(epoch_delay);
}