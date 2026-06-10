#include <Arduino.h>

class Button {
    public: 
        Button(int buttonPin) {
            this->buttonPin = buttonPin; 
            pinMode(buttonPin, INPUT_PULLUP); 
        }

        bool buttonIsPressed() {
            if (digitalRead(buttonPin) == HIGH) {
                return false; 
            } else {
                return true; 
            }
        }
    private: 
        int buttonPin; 
};