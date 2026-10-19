#include "PadIdle.h"

PadIdle::PadIdle() {
    ;
}

void PadIdle::onEntry(State prevState)
{
    switch (prevState)
    {
    default:
        break;

    case State::PAD_IDLE:
        run();
        break;

    case State::PAD_ARMED:
        Serial.print("PadIdle entry from ");
        Serial.print(printState[prevState].c_str());
        Serial.print(",");
        break;
    }
}

void PadIdle::run()
{
    Serial.print("run:PadIdle");
    Serial.print(",");
}