// Copyright 2020 Christian Maniewski.

#ifndef QUANTIZER_H_
#define QUANTIZER_H_

#include <stm32l4xx_hal.h>

#define QUANT_STEP_SEMITONE 1.0F / 12.0F

enum Key {
  KEY_SEMITONE,
  KEY_MAJOR,
  KEY_MINOR,
  KEY_PENTATONIC_MAJOR,
  KEY_PENTATONIC_MINOR,
  KEY_PURVI,
  KEY_TODI,
  KEY_LAST
};

enum Note {
  NOTE_C,
  NOTE_C_,
  NOTE_D,
  NOTE_D_,
  NOTE_E,
  NOTE_F,
  NOTE_F_,
  NOTE_G,
  NOTE_G_,
  NOTE_A,
  NOTE_A_,
  NOTE_B,
};

// Four octaves of notes encoded in the following way
// Starting from C, the following notes, that _are_ in the scale
// get a one, the one's that aren't get a 0. Do that four times
const uint64_t keys[KEY_LAST] = {
    // SEMITONE
    0xfffffffffffffff,
    // MAJOR
    0xad5ad5ad5ad5ad5,
    // MINOR
    0xb5ab5ab5ab5ab5a,
    // PENTATONIC MAJOR,
    0xa94a94a94a94a94,
    // PENTATONIC MINOR,
    0x952952952952952,
    // PURVI SCALE
    0xcb9cb9cb9cb9cb9,
    // TODI SCALE,
    0xd39d39d39d39d39, 
};

class QuantizerClass {
 private:
  float currentScale_[61] = {0};
  uint8_t currentScaleLength_ = 0;

 public:
  QuantizerClass();
  void SetScale(Note tonic, Key key, Note root, uint8_t octave, uint8_t range);
  float GetQuantizedVoltage(float value);
};

extern QuantizerClass Quantizer;

#endif  // QUANTIZER_H_
