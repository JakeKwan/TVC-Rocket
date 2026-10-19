#include <Arduino.h>

class Button
{
public:
    Button(int buttonPin)
    {
        this->buttonPin = buttonPin;
        pinMode(buttonPin, INPUT_PULLUP);
    }

    /**
     * @brief Rising edge button press detection. 
     * 
     * @return true 
     * @return false 
     */
    bool isPressed()
    {
        bool isButtonPressed = !digitalRead(buttonPin);
        // If there is a change of state, then return true (rising edge).
        if (isButtonPressed && !wasButtonPressed)
        {
            wasButtonPressed = !wasButtonPressed;
            return true;
        }
        else 
        {
            wasButtonPressed = isButtonPressed;
            return false;
        }
    }

private:
    int buttonPin;
    bool wasButtonPressed;
};