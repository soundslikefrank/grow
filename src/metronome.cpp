// Copyright 2020 Christian Maniewski.
//
// Author: Christian Maniewski (code@chmanie.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Simple metronome, running a tick interval for a given BPM

#include "metronome.hh"

#include <Arduino.h>
#include <math.h>

#define DEFAULT_BPM 120

// @TODO: Understand we these are necessary
uint16_t MetronomeClass::bpm_;
boolean MetronomeClass::tick_;

/*
 * Setup timers, using ATMega328P timers for now
 * With a prescaler of 256 we can go as low as 58bpm
 * (Output Compare interrupt flag at around 64,655)
 */
void MetronomeClass::Begin() {
  // Set Timer/Counter1 Control Register A to:
  // * Normal port operation, OC1A/OC1B disconnected.
  // * No Waveform Generation Mode
  TCCR1A = 0;
  // Set prescaler to 256, timer will overflow at 2^8 = 65536
  TCCR1B |= _BV(CS12);
  TCCR1B &= ~_BV(CS11);
  TCCR1B &= ~_BV(CS10);
  // Reset the timer after an interrupt was generated
  TCCR1B |= _BV(WGM12);
  // Start counting at 0
  TCNT1 = 0;
  // Enable timer interrupt on Output Compare A Match
  TIMSK1 |= _BV(OCIE1A);
  // Enable global interrupts
  sei();
  // Start with the default bpm value
  SetBPM(DEFAULT_BPM);
}

void MetronomeClass::SetBPM(uint16_t bpm) {
  bpm_ = bpm;
  // On this value we will reach (60s / bpm), so the timer should interrupt
  // Precision of this will be max 8us off / beat
  OCR1A = round(16000000.0 / 256.0 * 60.0 / static_cast<float>(bpm));
}

void MetronomeClass::SetTick() {
  tick_ = true;
}

boolean MetronomeClass::Tick() {
  if (tick_) {
    tick_ = false;
    return true;
  }
  return false;
}

ISR(TIMER1_COMPA_vect) {
  MetronomeClass::SetTick();
}
