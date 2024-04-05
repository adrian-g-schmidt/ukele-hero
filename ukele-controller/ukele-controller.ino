/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <Arduino.h>
#include <BleGamepad.h>

BleGamepad bleGamepad("Ukele", "Adrian", 100);
const int buttonPin1 = 15;
const int buttonPin2 = 2;


void setup()
{
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    bleGamepad.begin();
    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);
    // The default bleGamepad.begin() above enables 16 buttons, all axes, one hat, and no simulation controls or special buttons
}

void loop()
{
    if (bleGamepad.isConnected())
    {
      //There is definitely a neater way to do this
      if (digitalRead(buttonPin1)==LOW){
        bleGamepad.press(BUTTON_6);
      };
      if (digitalRead(buttonPin1)==HIGH){
        bleGamepad.release(BUTTON_6);
      };
      if (digitalRead(buttonPin2)==LOW){
        bleGamepad.press(BUTTON_5);
      };
      if (digitalRead(buttonPin2)==HIGH){
        bleGamepad.release(BUTTON_5);
      };
    }
}