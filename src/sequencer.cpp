// Copyright 2020 Christian Maniewski.

#include "sequencer.h"
#include <stm32f3xx_hal.h>
#include "drivers/fader_led.h"
#include "drivers/tim_metronome.h"

SequencerClass::SequencerClass() = default;

void SequencerClass::Init() { /* @TODO Do we need to do anything here? */
}

void SequencerClass::Start() { running_ = true; }

void SequencerClass::Stop() { running_ = false; }

void SequencerClass::NextStep() {
  if (currentStep_ < stepLength_ - 1) {
    currentStep_++;
  } else {
    currentStep_ = 0;
  }
}

void SequencerClass::SetStepLength(uint8_t stepLength) {
  if (stepLength > 64) {
    stepLength_ = 64;
  } else if (stepLength < 0) {
    stepLength_ = 0;
  } else {
    stepLength_ = stepLength;
  }
}

void SequencerClass::Loop() {
  if (!running_) {
    return;
  }
  // @TODO We can only use Metronome.Tick() once in the entire program. Let's
  // see if this is going to be a problem
  if (MetronomeTimer.Tick()) {
    NextStep();
    FaderLED.SetPosition(currentStep_ % 8);
  }
}

SequencerClass Sequencer;

