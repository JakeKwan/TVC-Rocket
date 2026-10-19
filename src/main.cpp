#include "main/StateMachine.h"

StateMachine *stateMachine; 

void setup() {
  Serial.begin(115200);
  // while (!Serial) {
    // delay(300);
  // }
  Wire.setClock(1000000);

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setShowLevel(false);
  
  stateMachine = new StateMachine(); 
  stateMachine->setup();
}

void loop() {
  //TODO: set frequency 
  stateMachine->run();
}