// An include guard is a preprocessor directive used in C and C++ to prevent a header file from being 
// included more than once in a single compilation. This can prevent issues such as redefinition errors.

#ifndef JAAK_FUNCTIONS_H // Check if JAAK_FUNCTIONS_H is not defined
#define JAAK_FUNCTIONS_H // Define JAAK_FUNCTIONS_H

  // Header contents:

  #include <Arduino.h>
  #include <ESPAsyncWebServer.h>

  // Declare the ws object as external so it can be used in the .cpp file
  extern AsyncWebSocket ws;

  // Function declarations
  void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
              void *arg, uint8_t *data, size_t len);
  void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
  String sendRequestToOpenAI(String inputText);

#endif // End of the include guard
/*

#ifndef JAAK_FUNCTIONS_H: This checks if the macro JAAK_FUNCTIONS_H has not been defined yet.
#define JAAK_FUNCTIONS_H: If the macro JAAK_FUNCTIONS_H has not been defined, it defines it.
Header file content: The actual content of the header file goes here.
#endif: This ends the #ifndef block.
*/
