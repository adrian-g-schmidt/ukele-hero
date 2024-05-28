// Load the libraries
#include <Arduino.h>
#include <BleGamepad.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

// Make a new gamepad for bluetooth
BleGamepad bleGamepad("Ukele", "Adrian", 100);

//Button variables - order doesn't matter as I remap in the game. 
const int buttonPinCount = 9;
const int buttonPins[] = {15, 2, 0, 4, 16, 17, 5, 18, 19};
const int buttonValues[] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8, BUTTON_9,};
const int lrPin = 36;
const int udPin = 39; 

void setup()
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Set brownout voltage to 2.6V, so the arduino consistently runs off the battery
    Serial.begin(115200);
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
      // Loop over all the buttons and send whether they are being pressed or released
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