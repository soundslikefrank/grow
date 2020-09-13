#include "drivers/tim_metronome.h"
#include "drivers/tim_ui.h"
#include "drivers/adc_ui.h"

extern "C" {
void SysTick_Handler() { HAL_IncTick(); }

void TIM2_IRQHandler() { HAL_TIM_IRQHandler(MetronomeTimer.GetTimer()); }
void TIM7_IRQHandler() { HAL_TIM_IRQHandler(UITimer.GetTimer()); }

// https://github.com/STMicroelectronics/STM32CubeF3/blob/master/Projects/STM32303C_EVAL/Templates/EWARM/startup_stm32f303xc.s#L93
void ADC1_2_IRQHandler() { HAL_ADC_IRQHandler(UIADC.GetADC()); }

void DMA1_Channel1_IRQHandler() { HAL_DMA_IRQHandler(UIADC.GetDMA()); }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) {
    MetronomeTimer.SetTick();
  }
  if (htim->Instance == TIM7) {
    UITimer.SetTick();
  }
}
}

