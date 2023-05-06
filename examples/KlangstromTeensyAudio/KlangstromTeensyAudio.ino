/*
  this example demonstrates how to integrate the *Klangstrom* library into the Teensy Audio Library.
*/

#include <Audio.h>
#include <KlangstromTeensy.h>
#include <KlangWellen.h>

/* integrate `KlangTeensy` like any other audio object */
KlangstromTeensy             mKlangTeensy;
AudioOutputI2S          i2s1;
AudioControlSGTL5000    sgtl5000_1;
AudioConnection         patchCord1(mKlangTeensy, 0, i2s1, 0);
AudioConnection         patchCord2(mKlangTeensy, 0, i2s1, 1);

int     mLED = 13;
float   mFreq = 220;
int     mFreqCounter = 0;

void setup() {
  Serial.begin(115200);
  /* wait for virtual serial port … note that the sketch will not start before the connection is established. */
  while (!Serial);

  /* check if the audio blocks’ sizes match. if not they need to be changed in the header files of either *Klang* or *Teensy Audio* */
  if (AUDIO_BLOCK_SAMPLES != KLANG_SAMPLES_PER_AUDIO_BLOCK * 2 ) {
    Serial.println("### WARNING change `KlangstromDefines.hpp` (Klang) or `AudioStream.h` (Teensy) to make `AUDIO_BLOCK_SAMPLES == KLANG_SAMPLES_PER_AUDIO_BLOCK * 2");
  }

  pinMode(mLED, OUTPUT);

  /* --- teensy audio setup --- */
  AudioMemory(10);
  AudioNoInterrupts();
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.85); // @TODO("SGTL5000 might need extra configuration")
  AudioInterrupts();

}

void loop() {
  digitalWrite(mLED, HIGH);
  delay(125);
  digitalWrite(mLED, LOW);
  delay(125);
}

void audioblock_transmit(float* pLeft, float* pRight) {
}
