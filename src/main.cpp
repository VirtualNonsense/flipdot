#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include "secrets.h"
#include "game_of_life.h"
#include "Octafont7.h"


// #####################################################################################################################
// Parameter
// #####################################################################################################################
// WiFi stuff - CHANGE FOR YOUR OWN NETWORK!
const IPAddress ip(192, 168, 47, 9);  // IP address that THIS DEVICE should request
const IPAddress gateway(192, 168, 47, 1);  // Your router
const IPAddress subnet(255, 255, 255, 0);  // Your subnet mask (find it from your router's admin panel)
const int ota_port = 42069;  // OTA Port
const int interface_port = 420;
WiFiServer server(interface_port);

// frontBuffer setup
int const lines = 14;
int const columns = 28;
int const m_size = 2 * columns;

byte frontBuffer[m_size];

byte backBuffer[m_size];

uint epoch_delay = 100;

int enableMatrixComPin = D5;

SoftwareSerial flip_dots(D4, D3); // rx (not used), tx
FlipDotMatrix matrix(lines / 2, columns, lines, columns, frontBuffer, backBuffer, &flip_dots);

rule rule_set = game_of_life;

int MODE_COUNT = 4;
enum DeviceMode {
    OverTheAirUpdate,
    GameOfLife,
    Clock,
    Slave,
};

DeviceMode mode = OverTheAirUpdate;
// #####################################################################################################################
// Functions
// #####################################################################################################################
// TODO: implement
void listen() {
}

void website() {

    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client) {
        return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    while (!client.available()) {
        delay(1);
    }

    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Match the request
    if (request.indexOf("/fill_random") != -1) {
        fill_random(0.2, &matrix);
        matrix.swapBuffer();
        matrix.updateMatrix();
    }

    if (request.indexOf("/change_gol_mode") != -1) {
        rule_set = static_cast<rule>((rule_set + 1) % RULE_COUNT);
    }

    if (request.indexOf("/change_mode") != -1) {
        mode = static_cast<DeviceMode>((mode + 1) % MODE_COUNT);
    }

    if (request.indexOf("/clear_matrix") != -1) {
        matrix.flushBackBuffer();
        matrix.updateFrontBuffer();
        matrix.updateMatrix();
    }
    String game_mode_string;
    switch (rule_set) {

        case game_of_life:
            game_mode_string = "game of life";
            break;
        case oca_maze:
            game_mode_string = "oca maze";
            break;
        case oca_mazectric:
            game_mode_string = "oca mazectric";
            break;
        case day_and_night:
            game_mode_string = "day and night";
            break;
    }

    String mode_string;
    switch (mode) {
        case GameOfLife:
            mode_string = "Game of life";
            break;
        case Clock:
            mode_string = "Clock";
            break;
        case Slave:
            mode_string = "Slave";
            break;
        case OverTheAirUpdate:
            mode_string = "Over the air update";
            break;
    }

    //Set ledPin according to the request
    //digitalWrite(ledPin, value);

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("Click <a href=\"/clear_matrix\">here</a> to clear the matrix<br>");
    client.print("Click <a href=\"/change_gol_mode\">here</a> to change the rule set. current mode: ");
    client.print(game_mode_string);
    client.println("<br>");
    client.print("Click <a href=\"/change_mode\">here</a> to change the device mode. current mode: ");
    client.print(mode_string);
    client.println("<br>");
    client.println("Click <a href=\"/fill_random\">here</a> to fill the matrix with random values<br>");
    client.println("</html>");

    delay(1);
    Serial.println("Client disconnected");
    Serial.println("");
}

// #####################################################################################################################
// Setup/Loop
// #####################################################################################################################

int c_x = 0;
int c_y = 0;
Octafont7 font = Octafont7();

letter tmp{
        -1,
        -1,
        -1,
};
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
        EspClass::restart();
    }
    Serial.println("Wifi setup success!");
    ArduinoOTA.setHostname("Flip-dot-matrix");
    ArduinoOTA.setPort(ota_port);
    ArduinoOTA.setPassword(otaPassword);

    Serial.println("Setting up wireless firmware updates");
    // Wireless OTA updating
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
    server.begin();
    // #################################################################################################################
    // Matrix setup
    Serial.println("Matrix setup");
    pinMode(enableMatrixComPin, OUTPUT);
    digitalWrite(enableMatrixComPin, HIGH);
//    matrix.setValue(0, 0, true);
    matrix.flushBackBuffer();
    matrix.updateFrontBuffer();
    matrix.updateMatrix();
    Serial.println("Setup Done!");
}

void write(int x, int y, letter l) {
    for (int r = 0; r < l.height; ++r) {
        for (int c = 0; c < l.width; ++c) {
            matrix.setValue(x + c, y + r, l.letter[l.start_index + c + r * l.width], true);
        }
    }
    matrix.updateFrontBuffer();
//    matrix.flushBackBuffer();
    matrix.updateMatrix();
}

const char text[]{
    '!',
    '"',
    '#',
    '$',
    '%',
    '&',
    '\'',
    '(',
    ')',
    '*',
    '+',
    ',',
    '-',
    '.',
    '/',
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
};
int counter = 0;
void loop() {
    website();
    switch (mode) {
        // Game of life demo mode
        case GameOfLife:
            calculate_next_epoch(&matrix, rule_set);
            matrix.swapBuffer();
            matrix.updateMatrix();
            delay(epoch_delay);
            break;

            // Standalone clock
        case Clock:
            font.get_letter(text[counter % sizeof(text)], &tmp);
            if (c_x + tmp.width - 1 >= matrix.getWidth()) {
                c_x = 0;
                c_y += tmp.height;
                if (c_y >= matrix.getHeight()) {
                    c_y = 0;
                    matrix.flushBackBuffer();
                }
            }
            Serial.println(tmp.height);
            Serial.println(tmp.width);
            Serial.println(tmp.start_index);
            write(c_x, c_y, tmp);
            c_x+=tmp.width + 1;
            delay(3 * epoch_delay);
            counter++;
            break;

            // Handle remote control
        case Slave:
            listen();
            break;

            // Handle Updates
        case OverTheAirUpdate:
            ArduinoOTA.handle();
            break;
    }
}