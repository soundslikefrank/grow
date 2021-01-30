// Copyright 2020 Christian Maniewski.

#ifndef QUANTIZER_H_
#define QUANTIZER_H_

#include <stm32l4xx_hal.h>

#define QUANT_STEP_SEMITONE 1.0F / 12.0F

enum Key { KEY_SEMITONE, KEY_MAJOR, KEY_MINOR };

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

const uint64_t keys[3] = {
    // SEMITONE
    0xfffffffffffffff,
    // MAJOR
    0xad5ad5ad5ad5ad5,
    // MINOR
    0xb5ab5ab5ab5ab5a};

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
