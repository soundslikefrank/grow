// Copyright 2020 Christian Maniewski.

#ifndef QUANTIZER_H_
#define QUANTIZER_H_

#include <stm32f3xx_hal.h>

enum Key { KEY_MAJOR, KEY_MINOR };

enum Note {
  NOTE_A,
  NOTE_A_,
  NOTE_B,
  NOTE_C,
  NOTE_D,
  NOTE_D_,
  NOTE_E,
  NOTE_F,
  NOTE_F_,
  NOTE_G,
  NOTE_G_
};

class QuantizerClass {
 private:
  bool majorScale[7] = {1, 1, 0, 1, 1, 1, 0};
  bool minorScale[7] = {1, 0, 1, 1, 0, 1, 1};
  Note currentTonic = NOTE_C;
  Key currentKey = KEY_MAJOR;
  uint8_t currentOctave = 0;
  Note notes[8] = {NOTE_A};
  uint8_t octaves[8] = {0};

 public:
  QuantizerClass();
  void SetTonic(Note tonic);
  void SetKey(Key key);
  void SetOctave(uint8_t octave);
  void Refresh();
  Note GetQuantizedNote(uint8_t position);
  uint8_t GetQuantizedOctave(uint8_t position);
};

extern QuantizerClass Quantizer;

#endif  // QUANTIZER_H_
