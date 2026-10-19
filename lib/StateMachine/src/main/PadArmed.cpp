#include "PadArmed.h"

PadArmed::PadArmed()
{
    ;
}
void PadArmed::onEntry(State prevState)
{
    switch (prevState)
    {
    default:
        break;

    case State::PAD_IDLE:
        Serial.print("PadArmed entry from ");
        Serial.print(printState[prevState].c_str());
        Serial.print(',');
        break;

    case State::PAD_ARMED:
        run();
        break;
    }
}

void PadArmed::run()
{
    Serial.print("run:PadArmed");
    Serial.print(',');
}