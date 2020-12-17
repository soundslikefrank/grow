#include <stm32l4xx_hal.h>
#include "conf.h"
#include "drivers/adc_ui.h"
#include "drivers/jack_detect.h"
#include "drivers/tim_metronome.h"
#include "drivers/tim_ui.h"

// @TODO: move to some other place? JackDetect class?
bool jackValues[INPUT_JACK_LAST] = {false, false, false};

extern "C" {
void SysTick_Handler() { HAL_IncTick(); }

void TIM2_IRQHandler() { HAL_TIM_IRQHandler(MetronomeTimer.GetTimer()); }
void TIM3_IRQHandler() { HAL_TIM_IRQHandler(UITimer.GetTimer()); }

void ADC1_IRQHandler() { HAL_ADC_IRQHandler(UIADC.GetADC()); }

void DMA2_Channel3_IRQHandler() { HAL_DMA_IRQHandler(UIADC.GetDMA()); }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
  if (htim->Instance == TIM2) {
    MetronomeTimer.SetTick();
  }
  if (htim->Instance == TIM3) {
    UITimer.SetTick();
  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* /* hadc */) {
  // @TODO abstract the trigger input read
  jackValues[INPUT_JACK_TRIGGER] = (bool)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1);
  // @TODO pick this value more carefully (calibration)
  jackValues[INPUT_JACK_CV_1] = UIADC.GetValue(8) < 1500;
  // @TODO this is just dummy data
  jackValues[INPUT_JACK_CV_2] = false;
  JackDetect.Next(jackValues);
}
}

