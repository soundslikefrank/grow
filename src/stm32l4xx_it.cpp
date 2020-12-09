#include <stm32l4xx_hal.h>
#include "drivers/tim_metronome.h"
#include "drivers/tim_ui.h"
#include "drivers/adc_ui.h"

extern "C" {
void SysTick_Handler() { HAL_IncTick(); }

void TIM2_IRQHandler() { HAL_TIM_IRQHandler(MetronomeTimer.GetTimer()); }
void TIM3_IRQHandler() { HAL_TIM_IRQHandler(UITimer.GetTimer()); }

void ADC1_IRQHandler() { HAL_ADC_IRQHandler(UIADC.GetADC()); }

void DMA2_Channel3_IRQHandler() { HAL_DMA_IRQHandler(UIADC.GetDMA()); }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) {
    MetronomeTimer.SetTick();
  }
  if (htim->Instance == TIM3) {
    UITimer.SetTick();
  }
}
}

