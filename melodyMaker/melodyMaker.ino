/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"

#include "mono.h"

#define AUDIO_PIN 2

void playMusicMono(int melody[][2], int len) {
  for (int thisNote = 0; thisNote < len; thisNote++) {
    int note = melody[thisNote][0];

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 900 / melody[thisNote][1];

    tone(AUDIO_PIN, note, duration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(AUDIO_PIN);
  }
}

void setup() {
  playMusicMono(POKEMON_CENTER, POKEMON_CENTER_LEN);
  delay(1000);
  playMusicMono(A_CRUEL_ANGELS_THESIS, A_CRUEL_ANGELS_THESIS_LEN);
  delay(1000);
  playMusicMono(KK_BOSA, KK_BOSA_LEN);
  delay(1000);
  playMusicMono(BTS_DNA_WHISTLE, BTS_DNA_WHISTLE_LEN);
  delay(1000);
  playMusicMono(COFFIN_DANCE, COFFIN_DANCE_LEN);
  delay(1000);
  playMusicMono(HIKARU_NARA, HIKARU_NARA_LEN);
  delay(1000);
}

void loop() {

}
