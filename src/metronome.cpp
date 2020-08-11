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

#include <math.h>
#include <stm32f3xx_hal.h>

#include "metronome.h"

#define DEFAULT_BPM 120

extern TIM_HandleTypeDef htim2;

// @TODO: Understand why these are necessary
uint16_t MetronomeClass::bpm_;
bool MetronomeClass::tick_;

void MetronomeClass::Init() {
  __HAL_RCC_TIM2_CLK_ENABLE();
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;  // 48MHz/24000 = 2000Hz
  htim2.Init.Period = 23999999;
  // Start with the default bpm value
  // In this configuration it can be max 1.8μs per day off
  htim2.Init.Period = round(60 * 48000000 / DEFAULT_BPM) - 1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;

  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);

  HAL_TIM_Base_Init(&htim2);
  HAL_TIM_Base_Start_IT(&htim2);

  // Enable DMA for the TIM_UPDATE event on the timer
  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_UPDATE);
}

void MetronomeClass::SetBPM(uint16_t bpm) {
  bpm_ = bpm < 20 ? 20 : bpm;
  uint32_t period = round(60U * 48000000U / bpm_) - 1;
  TIM2->ARR = period;
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
void TIM2_IRQHandler(void) { HAL_TIM_IRQHandler(&htim2); }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) MetronomeClass::SetTick();
}
}
