/*

Project for VSL Summer 2024 Middle School students

Broken down into 4 files for readability and reusability

AUTHOR: Sebastian Yepez
Date: June 4, 2024

*/

// Libraries and headers
#include <WiFi.h>
#include <M5Stack.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

#include "myHTML.h"
#include "JAAK_functions.h"

// Network credentials and API Key
const char *ssid = "YOUR_WIFI-SSID"; // must be 2.4 GHz
const char *password = "YOUR_WIFI_PASSWORD";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Function that initializes the websocket and links it with the server
void initWebSocket()
{
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

// SETUP FUNCTION
void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  delay(1000); // Give the Serial time to initialize

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP()); // So that we can connect to the websocket on a web browser

  // Initialize M5Stack and Websocket
  M5.begin();
  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", myHTML); });

  // Start server
  server.begin();

  // Prep LCD screen
  M5.Lcd.fillScreen(DARKCYAN);

  // Display QR code on M5Stack
  String qrcodeLink = "http://" + WiFi.localIP().toString();
  M5.Lcd.qrcode(qrcodeLink, 50, 20, 200, 6);
}

// LOOP FUNCTION
void loop()
{
  ws.cleanupClients(); // This function goes through the list of WebSocket clients and removes any that have been disconnected. - frees up resources
  delay(100); // Small delay to allow for smooth processing
}