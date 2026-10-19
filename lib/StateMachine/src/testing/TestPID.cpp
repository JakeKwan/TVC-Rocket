#include "TestPID.h"

TestPID::TestPID() {}

void TestPID::run() {
    navigation.step();
    control.step();
}

void TestPID::onEntry(State prevState) {
    switch (prevState) {
        default: 
            break;
        case State::TEST_PID:
            run();
            break;
    }
}