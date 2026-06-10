#include <Arduino.h>
#include "RocketConfig.h"
#include "pitches.h"

class Tune {
    public: 
        Tune(const int (&melody)[4], const int (&noteDurations)[4]) {
            for (int i = 0; i < 4; ++i) {
                this->melody[i] = melody[i];
                this->noteDurations[i] = noteDurations[i];
            }
        }
        
        int melody[4]; 
        int noteDurations[4]; 
};

class Buzzer {
    public: 
        Buzzer() {
            pinMode(BUZZER_PIN, OUTPUT); 
        } 

        void play(Tune tune) {
            int size = sizeof(tune.noteDurations) / sizeof(int);

            for (int thisNote = 0; thisNote < size; thisNote++) {

                // to calculate the note duration, take one second divided by the note type.
                //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
                int noteDuration = 1000 / tune.noteDurations[thisNote];
                tone(BUZZER_PIN, tune.melody[thisNote], noteDuration);

                // to distinguish the notes, set a minimum time between them.
                // the note's duration + 30% seems to work well:
                int pauseBetweenNotes = noteDuration * 1.30;
                delay(pauseBetweenNotes);
                // stop the tone playing:
                noTone(BUZZER_PIN);
            }
        }

        Tune startupTune = Tune({NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5}, {4, 4, 4, 4}); 
        

};