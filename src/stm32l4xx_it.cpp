#include <stm32l4xx_hal.h>
#include "conf.h"
#include "drivers/adc_ui.h"
#include "drivers/dac.h"
#include "drivers/jack_detect.h"
#include "drivers/tim_metronome.h"
#include "drivers/tim_ui.h"

// LEDs
extern QSPI_HandleTypeDef hqspi;
extern DMA_HandleTypeDef hdmaQSPI;
// MetronomeTimer
extern TIM_HandleTypeDef htim2;
// IOTimer
extern TIM_HandleTypeDef htim3;
// ADC
extern ADC_HandleTypeDef hadc;
extern DMA_HandleTypeDef hdmaADC;
// DAC
extern SPI_HandleTypeDef hspi2;

// @TODO: move to some other place? JackDetect class?
bool jackValues[INPUT_JACK_LAST] = {false, false, false};

extern "C" {
void SysTick_Handler() { HAL_IncTick(); }

/* Interrupt handlers */

// MetronomeTimer
void TIM2_IRQHandler() { HAL_TIM_IRQHandler(&htim2); }

// IOTimer
void TIM3_IRQHandler() { HAL_TIM_IRQHandler(&htim3); }

// ADC
void ADC1_IRQHandler() { HAL_ADC_IRQHandler(&hadc); }
void DMA2_Channel3_IRQHandler() { HAL_DMA_IRQHandler(&hdmaADC); }

// LEDs
void QUADSPI_IRQHandler() { HAL_QSPI_IRQHandler(&hqspi); }
void DMA1_Channel5_IRQHandler() { HAL_DMA_IRQHandler(&hdmaQSPI); }

// DAC
void SPI2_IRQHandler() { HAL_SPI_IRQHandler(&hspi2); }

/* Callbacks */
// @TODO I think these should go into the corresponding files
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim) {
  if (htim->Instance == TIM2) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET);
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
  if (htim->Instance == TIM2) {
    MetronomeTimer.SetTick();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_SET);
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

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi) {
  if (hspi->Instance == SPI2) {
    HAL_GPIO_WritePin(GPIOB, PIN_SPI2_CS, GPIO_PIN_SET);
  }
}
}
