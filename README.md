# Vegas-STEM-Lab-2024

## Table of Contents
- [Description](#description)
- [Functionality](#functionality)
- [Limitations](#limitations)
- [Usage](#usage)
- [Project for Students](#project-for-students)
- [M5Stack FIRE](#m5stack-fire)
- [Debugging](#debugging)

## Description
Hi, everyone! The Vegas STEM Lab was a three-year program offering a three-week long immersive experience for students to explore the world of STEM. As a mentor, my task was to create a project that students could replicate or innovate upon. This year, I developed an AI Chatbot powered by an ESP-32 microcontroller.

For more information regarding the source code, please check out my other repository: https://github.com/SebastianYepez/ESP32-AI-Chatbot

## Functionality
This .ino program works by initiating a websocket powered by the ESP32, taking the user's input from the input textbox, utilizing ChatGPT 3.5 Turbo through OpenAI's API, and returning the result back to the websocket.

## Limitations
Because of the usage of the API, each request is independent. This means that the bot is not capable of being contextually aware in relation to previous messages as ChatGPT would be.

Also, the ESP-32 is limited to 2.4 GHz WiFi. This can be a nuisance in today's age where 5 GHz is quickly becoming mainstream.

I've only tested this program on ESP32 board versions 2.0.16 and 2.0.17. I believe the code does not work on versions newer than this because of a difference in WiFi capabilities. Changing the version of your ESP32 board is very easy to do through Arduino, however. More information to install the ESP32 board can be found [here](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

Finally, if your students would like to add images to the HTML file, please ensure that these images can be accessed through a hyperlink. Otherwise, you'd have to find a way to work with SPIFFS or LittleFS, which is a huge hassle and may not be possible on versions of Arduino past 1.9.

## Usage
To use this program, simply download the folder. In the .ino file, a couple changes must be made:
 1. Input your WiFi credentials
 2. Add your API key
 3. Check to see if the OpenAI model is appropriate for your needs
 4. Delete/Change M5Stack attributes if unapplicable

After that is done, ensure you have the appropriate libraries installed.

When running, an IP address will be printed to the Serial Monitor. Copy and paste this IP address into a web browser and interact with your own chatbot!

### Project for Students
If you would like to provide this as a challenge to your students, I have annotated the code in such a way where they have to write only two lines of code:
1. Simply call a void function
2. Create a string that stores the response of another function

This allows them to learn the importance of documentation, function calls, and overall develop stronger programming principles.

Finally, the biggest part of the project would be allowing the students to customize their own HTML file so they get practice with HTML, CSS, and JavaScript. To provide them with a blank slate, please download and send them the "MYGPT.html" file. If you do decide to provide this project to your student(s), please share with me the finished product on [LinkedIn](https://www.linkedin.com/in/sebastian-yepez/)! I would love to repost it.

## M5Stack FIRE
The M5Stack FIRE is an ESP32-powered device that I utilized for this project. It comes with an LCD, microphone, speaker, and more. I simply used it to display a QR code that links to the websocket, but if one wishes they could definitely build upon this. Or, one could simply remove any reference to "M5Stack" and have it run just fine on a simple ESP32 board.

A quick note is that if one is utilizing the M5Stack Fire they should download the M5Stack library as well as the board from the board manager. When done, select M5Stack-FIRE from the boards as well as the appropriate COM port.

## Debugging
If you run into errors, please look at the debugging tips in my [other repository](https://github.com/SebastianYepez/ESP32-AI-Chatbot).
