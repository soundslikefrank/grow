// Copyright 2020 Christian Maniewski.

#include "drivers/tim_ui.h"
#include <stm32f3xx_hal.h>

// Times per second, has to be divisor of 1000
#define UI_TIMER_SAMPLE_RATE 500

UITimerClass::UITimerClass() = default;

void UITimerClass::Init() {
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  __HAL_RCC_TIM3_CLK_ENABLE();
  htim_.Instance = TIM3;
  htim_.Init.Prescaler = 47999;  // 1000Hz
  htim_.Init.Period = (1000 / UI_TIMER_SAMPLE_RATE) - 1;
  htim_.Init.CounterMode = TIM_COUNTERMODE_UP;

  HAL_NVIC_SetPriority(TIM3_IRQn, 1, 1);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);

  HAL_TIM_Base_Init(&htim_);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim_, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim_, &sMasterConfig);

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
