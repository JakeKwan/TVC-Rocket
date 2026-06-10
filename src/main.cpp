#include "State.h"

StateMachine *myStateMachine; 

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); 
  }

  myStateMachine = new StateMachine(); 
  myStateMachine->setup(); 
}

void loop() {
  myStateMachine->stateLoop();
}