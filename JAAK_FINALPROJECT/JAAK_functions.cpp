// This file contains the DEFINITIONS OF THE FUNCTIONS
  // In other words, this file contains what the functions actually do
  // They are separate from the other files in order to promote code readibility, reusability, and security

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "JAAK_functions.h"

// This function receives events from the websocket and there are three main events that we focus on here:
    // WS Connection
    // WS Disconnection
    // WS Event (Button is pressed)
        // TASK: Button is pressed, now we have to CALL A FUNCTION that handles this message from the websocket 
                // with the 3 arguments: (arg,data,len)
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      /* Call a function to handle the websocket message */ 
       handleWebSocketMessage(arg,data,len); // Have your students write this line of code
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

// A function that handles the message received from the websocket
  // How it works:
    // Gets the string from the user from the websocket and stores it in inputText
    // TASK: create a string that gets the result from sending inputText to openAI's API
    // Sends the response from ChatGPT to the websocket to be displayed
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    data[len] = 0;

    String inputText = (char *)data; // we have received our text from the web socket stored in inputText

    Serial.printf("Received message from client: %s\n", inputText.c_str());

    // Here you can handle the received message and perform actions

    /* Create a String object called outputText that gets the result from sending the inputText we receive to OpenAI */
      String outputText = sendRequestToOpenAI(inputText); // Have your students run this line of code
    //sends outputText to the websocket to display it
    ws.textAll(outputText);
  }
}

// This function sends the argument inputText to openAI's API and returns the RESPONSE
// Nothing to be done inside the function, but just know how it works and make sure you store the result in a String
String sendRequestToOpenAI(String inputText)
{
    // Debug API setup
    String apiUrl = "https://api.openai.com/v1/chat/completions";
    String payload = "{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"" + inputText + "\"}], \"max_tokens\": 100}";
    Serial.print("API URL: ");
    Serial.println(apiUrl);
    Serial.print("Payload: ");
    Serial.println(payload);

    // Send request to OpenAI API
    HTTPClient http;
    http.begin(apiUrl);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String("YOUR_API_KEY")); // adds api key
    Serial.println("Sending POST request...");

    int httpResponseCode = http.POST(payload);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    // If successful:
    if (httpResponseCode > 0)
    {
        String response = http.getString();
        Serial.println("Response received!");

        // Parse JSON response
        DynamicJsonDocument jsonDoc(4096); // Increase buffer size for larger responses
        DeserializationError error = deserializeJson(jsonDoc, response);
        if (error)
        {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.f_str());
            return "error";
        }
        String outputText = jsonDoc["choices"][0]["message"]["content"].as<String>();
        http.end(); // End the HTTP request
        return outputText;
    }
    
    // If failure:
    Serial.printf("Error %i: %s\n", httpResponseCode, http.errorToString(httpResponseCode).c_str());
    String response = http.getString();
    Serial.println("Response: " + response);
    http.end(); // End the HTTP request
    return response;
}