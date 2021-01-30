// Copyright 2020 Christian Maniewski.

#include "quantizer.h"
#include <math.h>
#include "util.h"

QuantizerClass::QuantizerClass() = default;

float QuantizerClass::GetQuantizedVoltage(float value) {
  uint8_t index = round(value * (float)currentScaleLength_);
  return currentScale_[index];
}

// Octave: 0 (C0) - Range - 1
// Range: 0 (1 Octave + 1) - 4 (5 Octaves + 1)
void QuantizerClass::SetScale(Note tonic, Key key, Note root, uint8_t octave, uint8_t range) {
  uint64_t scale = keys[key];
  uint8_t pos = 0;
  currentScaleLength_ = 0;

  // Shift scale for tonic and root appropriately
  int8_t shift = tonic - root;
  if (shift > 0) {
    scale = ror(scale, shift, 60);
  }
  if (shift < 0) {
    scale = rol(scale, abs(shift), 60);
  }
  // Assemble scale
  while (pos < (range + 1) * 12) {
    if (scale & (1ULL << (59 - pos))) {
      currentScale_[currentScaleLength_++] =
          (float)octave + (float)(root + pos) * QUANT_STEP_SEMITONE;
    }
    pos++;
  }
  // We add the root value to the end if it's a 1 (x Octaves + 1)
  if (scale & (1ULL << 59)) {
    currentScale_[currentScaleLength_] =
        (float)octave + (float)(root + pos) * QUANT_STEP_SEMITONE;
  }
}

QuantizerClass Quantizer;
