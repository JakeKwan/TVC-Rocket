#ifndef BUZZER_H
#define BUZZER_H

#include "Config.h"
#include "Pitches.h"

class Tune
{
public:
    Tune(const int (&melody)[4], const int (&noteDurations)[4])
    {
        for (int i = 0; i < 4; ++i)
        {
            this->melody[i] = melody[i];
            this->noteDurations[i] = noteDurations[i];
        }
    }

    int melody[4];
    int noteDurations[4];
};

class Buzzer
{
public:
    Buzzer(uint8_t pin)
    {
        this->PIN = pin;
        pinMode(PIN, OUTPUT);
    }

    void play(Tune tune)
    {
        const int size = sizeof(tune.noteDurations) / sizeof(int);

        for (int thisNote = 0; thisNote < size; thisNote++)
        {

            // to calculate the note duration, take one second divided by the note type.
            // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
            const int noteDuration = 1000 / tune.noteDurations[thisNote];
            tone(PIN, tune.melody[thisNote], noteDuration);

            // to distinguish the notes, set a minimum time between them.
            // the note's duration + 30% seems to work well:
            const int pauseBetweenNotes = noteDuration * 1.30;
            delay(pauseBetweenNotes);
            // stop the tone playing:
            noTone(PIN);
        }
    }

    // void beep()
    // {
    //     if (isPlaying)
    //     tone(PIN, NOTE_A4, );
    // }

private:
    uint8_t PIN;
    bool isPlaying = false;
};

#endif