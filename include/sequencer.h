// Copyright 2020 Christian Maniewski.

#ifndef SEQUENCER_H_
#define SEQUENCER_H_

#include <stm32f3xx_hal.h>

class SequencerClass {
 private:
  uint8_t stepLength_ = 8;
  uint8_t currentStep_ = 0;
  bool running_;

 public:
  SequencerClass();
  void Init();
  void Start();
  uint8_t NextStep();
  void Stop();
  void SetStepLength(uint8_t stepLength);
};

extern SequencerClass Sequencer;

#endif  // SEQUENCER_H_
