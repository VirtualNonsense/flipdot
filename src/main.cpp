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
#include "game_of_life.h"


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
// #####################################################################################################################
// Functions
// #####################################################################################################################

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
    if (request.indexOf("/reset") != -1) {
        fill_random(0.2, &matrix);
        matrix.updateFrontBuffer();
    }

    if (request.indexOf("/change_mode") != -1) {
        rule_set = static_cast<rule>((rule_set + 1) % RULE_COUNT);
    }
    String game_mode;
    switch (rule_set) {

        case game_of_life:
            game_mode = "game of life";
            break;
        case oca_maze:
            game_mode = "oca maze";
            break;
        case oca_mazectric:
            game_mode = "oca mazectric";
            break;
        case day_and_night:
            game_mode = "day and night";
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
    client.println("Click <a href=\"/reset\">here</a> to reset the matrix<br>");
    client.print("Click <a href=\"/change_mode\">here</a> to change the rule set. current mode: ");
    client.print(game_mode);
    client.println("<br>");
    client.println("</html>");

    delay(1);
    Serial.println("Client disconnected");
    Serial.println("");
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
    pinMode(enableMatrixComPin, OUTPUT);
    digitalWrite(enableMatrixComPin, HIGH);
}

void loop() {
    ArduinoOTA.handle();
    website();
    calculate_next_epoch(&matrix, rule_set);
    matrix.swapBuffer();
    matrix.updateMatrix();
    delay(epoch_delay);
}