// Copyright 2020 Christian Maniewski.

#include "drivers/tim_ui.h"
#include <stm32l4xx_hal.h>

// @TODO rename. Maybe IO timer? input-timer? stream-timer? clock?

TIM_HandleTypeDef htim3;

UITimerClass::UITimerClass() = default;

void UITimerClass::Init() {
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  __HAL_RCC_TIM3_CLK_ENABLE();
  htim3.Instance = TIM3;
  // @40Mhz SysClock this should be 4kHz
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.Prescaler = 19;
  htim3.Init.Period =  499;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;

  HAL_NVIC_SetPriority(TIM3_IRQn, 1, 1);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);

  HAL_TIM_Base_Init(&htim3);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

  HAL_TIM_Base_Start_IT(&htim3);
}

void UITimerClass::SetTick() { tick_ = true; }

bool UITimerClass::Tick() {
  if (tick_) {
    tick_ = false;
    return true;
  }
  return false;
}

UITimerClass UITimer;
