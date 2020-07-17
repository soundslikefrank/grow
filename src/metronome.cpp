// Copyright 2020 Christian Maniewski.
//
// Author: Christian Maniewski (code@chmanie.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Simple metronome, running a tick interval for a given BPM

#include "metronome.h"

#include <math.h>
#include <stm32f3xx_hal.h>

#define DEFAULT_BPM 120

TIM_HandleTypeDef htim6;

// @TODO: Understand why these are necessary
uint16_t MetronomeClass::bpm_;
bool MetronomeClass::tick_;

void MetronomeClass::Begin() {
  // Start with the default bpm value
  // In this configuration it can be max 0.1μs off
  htim6.Instance = TIM6;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  // 48MHz/2400 = 20,000Hz
  htim6.Init.Prescaler = 2399;
  htim6.Init.Period = round(60 * 20000 / DEFAULT_BPM) - 1;

  __HAL_RCC_TIM6_CLK_ENABLE();

  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

  HAL_TIM_Base_Init(&htim6);
  HAL_TIM_Base_Start_IT(&htim6);
}

void MetronomeClass::SetBPM(uint16_t bpm) {
  bpm_ = bpm < 20 ? 20 : bpm;
  uint16_t period = round(60 * 20000 / bpm_) - 1;
  TIM6->ARR = period;
}

void MetronomeClass::SetTick() { tick_ = true; }

bool MetronomeClass::Tick() {
  if (tick_) {
    tick_ = false;
    return true;
  }
  return false;
}

extern "C" {

void TIM6_DAC1_IRQHandler(void) { HAL_TIM_IRQHandler(&htim6); }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM6) MetronomeClass::SetTick();
}
}
