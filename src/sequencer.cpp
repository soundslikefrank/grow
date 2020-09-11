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

void SequencerClass::Loop() {
  if (!running_) {
    return;
  }
  // @TODO We can only use Metronome.Tick() once in the entire program. Let's see if
  // this is going to be a problem
  if (MetronomeTimer.Tick()) {
    NextStep();
    // @TODO this obviously won't work with more than 8 steps
    FaderLED.SetPosition(currentStep_);
  }
}

SequencerClass Sequencer;

