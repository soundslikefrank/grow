// Copyright 2020 Christian Maniewski.

#include "drivers/tim_ui.h"
#include <stm32f3xx_hal.h>

// Times per second, has to be divisor of 1000
#define UI_TIMER_SAMPLE_RATE 1

UITimerClass::UITimerClass() = default;

void UITimerClass::Init() {
  // Use basic timer
  __HAL_RCC_TIM7_CLK_ENABLE();
  htim_.Instance = TIM7;
  htim_.Init.Prescaler = 47999;  // 1000Hz
  htim_.Init.Period = (1000 / UI_TIMER_SAMPLE_RATE) - 1;
  htim_.Init.CounterMode = TIM_COUNTERMODE_UP;

  HAL_NVIC_SetPriority(TIM7_IRQn, 1, 1);
  HAL_NVIC_EnableIRQ(TIM7_IRQn);

  HAL_TIM_Base_Init(&htim_);
  HAL_TIM_Base_Start_IT(&htim_);
}

TIM_HandleTypeDef* UITimerClass::GetTimer() { return &htim_; }

void UITimerClass::SetTick() { tick_ = true; }

bool UITimerClass::Tick() {
  if (tick_) {
    tick_ = false;
    return true;
  }
  return false;
}

UITimerClass UITimer;
