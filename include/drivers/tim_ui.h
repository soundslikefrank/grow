// Copyright 2020 Christian Maniewski.

#ifndef DRIVERS_TIM_UI_H
#define DRIVERS_TIM_UI_H

#include <stm32f3xx_hal.h>

class UITimerClass {
 private:
  bool tick_;
  TIM_HandleTypeDef htim_;

 public:
  UITimerClass();
  TIM_HandleTypeDef* GetTimer();
  void Init();
  void SetTick();
  bool Tick();
};

extern UITimerClass UITimer;

#endif  // DRIVERS_TIM_UI_H
