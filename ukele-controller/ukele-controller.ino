/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <Arduino.h>
#include <BleGamepad.h>

BleGamepad bleGamepad("Ukele", "Adrian", 100);
const int buttonPinCount = 7;
const int buttonPins[] = {15, 2, 0, 4, 16, 17, 5};
const int buttonValues[] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7};
const int lrPin = 36; // Left/Right
const int udPin = 39; // Up/Down

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    bleGamepad.begin();
    for (int i = 0; i < buttonPinCount; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
    pinMode(lrPin, INPUT);
    pinMode(udPin, INPUT);
}

void loop()
{
    if (bleGamepad.isConnected())
    {
        for (int i = 0; i < buttonPinCount; i++) {
            if (digitalRead(buttonPins[i]) == LOW) {
                bleGamepad.press(buttonValues[i]);
            } else {
                bleGamepad.release(buttonValues[i]);
            }
        }
        
        // Read the analog values for the thumbstick
        int lrValue = analogRead(lrPin);
        int udValue = analogRead(udPin);
        
        // Map the analog values to the range [0, 32767]
        int lrMapped = map(lrValue, 450, 3300, 0, 32767);
        int udMapped = map(udValue, 450, 3300, 0, 32767);
        
        // Send the thumbstick values
        bleGamepad.setLeftThumb(lrMapped, udMapped);
    }
}