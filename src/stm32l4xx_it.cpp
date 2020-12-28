#include <stm32l4xx_hal.h>
#include "conf.h"
#include "drivers/adc_ui.h"
#include "drivers/jack_detect.h"
#include "drivers/led.h"
#include "drivers/tim_metronome.h"
#include "drivers/tim_ui.h"

// @TODO I think this is the way we're supposed to do this stuff
extern QSPI_HandleTypeDef hqspi;
extern DMA_HandleTypeDef hdma_qspi;

// @TODO: move to some other place? JackDetect class?
bool jackValues[INPUT_JACK_LAST] = {false, false, false};

extern "C" {
void SysTick_Handler() { HAL_IncTick(); }

// @TODO use extern (as for the QSPI handler)
void TIM2_IRQHandler() { HAL_TIM_IRQHandler(MetronomeTimer.GetTimer()); }
void TIM3_IRQHandler() { HAL_TIM_IRQHandler(UITimer.GetTimer()); }

// @TODO use extern (as for the QSPI handler)
void ADC1_IRQHandler() { HAL_ADC_IRQHandler(UIADC.GetADC()); }

// @TODO use extern (as for the QSPI handler)
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
  jackValues[INPUT_JACK_CV_1] = UIADC.GetValue(10) < 1500;
  jackValues[INPUT_JACK_CV_2] = UIADC.GetValue(11) < 1500;
  JackDetect.Next(jackValues);
}

// LED driver IRQ handler
void QUADSPI_IRQHandler(void) { HAL_QSPI_IRQHandler(&hqspi); }

void DMA1_Channel5_IRQHandler() { HAL_DMA_IRQHandler(&hdma_qspi); }
}
