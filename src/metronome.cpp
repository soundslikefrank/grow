// Copyright 2020 Christian Maniewski.
// Simple metronome, running a tick interval for a given BPM

#include "metronome.h"
#include <math.h>
#include <stm32f3xx_hal.h>

#define DEFAULT_BPM 120

TIM_HandleTypeDef htim2;

MetronomeClass::MetronomeClass() = default;

void MetronomeClass::Init() {
  __HAL_RCC_TIM2_CLK_ENABLE();
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;  // 48MHz/24000 = 2000Hz
  htim2.Init.Period = 23999999;
  // Start with the default bpm value
  // In this configuration it can be max 1.8μs per day off
  htim2.Init.Period = round(60U * 48000000U / DEFAULT_BPM) - 1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;

  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);

  HAL_TIM_Base_Init(&htim2);
  HAL_TIM_Base_Start_IT(&htim2);
}

void MetronomeClass::SetBPM(uint16_t bpm) {
  bpm_ = bpm < 20 ? 20 : bpm;
  uint32_t period = round(60U * 48000000U / bpm_) - 1;
  TIM2->ARR = period;
}

void MetronomeClass::SetTick() { tick_ = true; }

void MetronomeClass::Start() { running_ = true; }

void MetronomeClass::Stop() { running_ = false; }

bool MetronomeClass::Tick() {
  if (running_) {
    return false;
  }
  if (tick_) {
    tick_ = false;
    return true;
  }
  return false;
}

MetronomeClass Metronome;

extern "C" {
void TIM2_IRQHandler(void) { HAL_TIM_IRQHandler(&htim2); }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) {
    Metronome.SetTick();
  }
}
}
