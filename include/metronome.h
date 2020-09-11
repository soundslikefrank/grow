// Copyright 2020 Christian Maniewski.

#ifndef METRONOME_H_
#define METRONOME_H_

#include <stm32f3xx_hal.h>

class MetronomeClass {
 private:
  bool tick_;
  uint16_t bpm_;
  bool running_ = false;

 public:
  MetronomeClass();
  void Init();
  void Start();
  void Stop();
  uint16_t GetBPM();
  void SetBPM(uint16_t);
  void SetTick();
  bool Tick();
};

extern MetronomeClass Metronome;

#endif  // METRONOME_H_
