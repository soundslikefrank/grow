// Copyright 2020 Christian Maniewski.

#ifndef DRIVERS_TIM_METRONOME_H_
#define DRIVERS_TIM_METRONOME_H_

#include <stm32l4xx_hal.h>

class MetronomeTimerClass {
 private:
  bool tick_;
  uint16_t bpm_;
  TIM_HandleTypeDef htim_;

 public:
  MetronomeTimerClass();
  void Init();
  uint16_t GetBPM();
  TIM_HandleTypeDef* GetTimer();
  void SetBPM(uint16_t);
  void SetTick();
  bool Tick();
};

extern MetronomeTimerClass MetronomeTimer;

#endif  // DRIVERS_TIM_METRONOME_H_
