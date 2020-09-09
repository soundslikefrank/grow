#include "quantizer.h"

QuantizerClass::QuantizerClass() = default;

void QuantizerClass::SetTonic(Note tonic) { currentTonic = tonic; }

void QuantizerClass::SetKey(Key key) { currentKey = key; }

void QuantizerClass::SetOctave(uint8_t octave) { currentOctave = octave; }

void QuantizerClass::Refresh() {
  // Pick the right scale array
  bool *scale = currentKey ? minorScale : majorScale;
  uint8_t note = currentTonic;
  uint8_t octave = currentOctave;
  // The first note of the scale is the one we start with
  notes[0] = static_cast<Note>(note);
  octaves[0] = octave;
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
    notes[step + 1] = static_cast<Note>(note);
    octaves[step + 1] = octave;
  }
}

Note QuantizerClass::GetQuantizedNote(uint8_t position) {
  return notes[position];
}

uint8_t QuantizerClass::GetQuantizedOctave(uint8_t position) {
  return octaves[position];
}

QuantizerClass Quantizer;
