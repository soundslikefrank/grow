// Copyright 2020 Christian Maniewski.

#include "quantizer.h"

QuantizerClass::QuantizerClass() = default;

void QuantizerClass::SetTonic(Note tonic) { currentTonic_ = tonic; }

void QuantizerClass::SetKey(Key key) { currentKey_ = key; }

void QuantizerClass::SetOctave(uint8_t octave) { currentOctave_ = octave; }

void QuantizerClass::Refresh() {
  // Pick the right scale array
  bool *scale = currentKey_ ? minorScale_ : majorScale_;
  uint8_t note = currentTonic_;
  uint8_t octave = currentOctave_;
  // The first note of the scale is the one we start with
  notes_[0] = static_cast<Note>(note);
  octaves_[0] = octave;
  for (int step = 0; step < 7; step++) {
    // Go up one semitone (because we do that in any case)
    if (++note == 12) {
      note = 0;
      octave++;
    }
    if (scale[step]) {
      // If the current step is a whole tone, bump again
      note++;
    }
    // If that got us out of the scale, start from 0
    if (note == 12) {
      note = 0;
      octave++;
    }
    notes_[step + 1] = static_cast<Note>(note);
    octaves_[step + 1] = octave;
  }
}

Note QuantizerClass::GetQuantizedNote(uint8_t position) {
  if (octaves_[position] < 0) {
    // return A as the lowest note possible
    return NOTE_A;
  }
  if ((octaves_[position] == 7 && notes_[position] > 3) ||
      octaves_[position] > 7) {
    // return G_ as the highest note
    return NOTE_G_;
  }
  return notes_[position];
}

uint8_t QuantizerClass::GetQuantizedOctave(uint8_t position) {
  if (octaves_[position] < 0) {
    return 0;
  }
  return octaves_[position];
}

QuantizerClass Quantizer;
