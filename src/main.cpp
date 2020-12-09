// Copyright 2020 <Christian Maniewski>

#include <stm32l4xx_hal.h>
#include <string.h>
#include <cstdio>
#include "drivers/adc_ui.h"
#include "drivers/dac.h"
#include "drivers/fader_led.h"
#include "drivers/tim_metronome.h"
#include "drivers/tim_ui.h"
#include "quantizer.h"
#include "sequencer.h"
#include "uart_debug.h"

// @TODO Apply
// https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html

#define DATA_PIN GPIO_PIN_0
#define CLK_PIN GPIO_PIN_1
#define LAT_PIN GPIO_PIN_4

TIM_HandleTypeDef htim1;

void MX_TIM1_Init(void);

// Default clock config, generated with STM32CubeMX
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSE;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 8;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
}

void writeLEDData(uint8_t data[16]) {
  for (uint8_t i = 0; i < 16; i++) {
    HAL_GPIO_WritePin(GPIOA, DATA_PIN, data[i] ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, CLK_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, CLK_PIN, GPIO_PIN_RESET);
  }
  HAL_GPIO_WritePin(GPIOA, DATA_PIN, GPIO_PIN_RESET);
}

int main() {
  HAL_Init();
  SystemClock_Config();
  HUART1_Init();

  _DAC.Init();
  MetronomeTimer.Init();
  UITimer.Init();
  UIADC.Init();
  FaderLED.Init();
  Quantizer.Refresh();

  char msg[20] = "Hello world";
  /* char msg[20]; */

  MetronomeTimer.SetBPM(120);
  Sequencer.Start();

  while (true) {
    if (MetronomeTimer.Tick()) {
      uint8_t step = Sequencer.NextStep();
      uint16_t faderPos = (4096 - UIADC.GetValue(step % 8));
      // Somewhere in the third octave after c0 (0v), 8192/octave
      uint16_t voltage = 16 * faderPos - 1;
      /* sprintf(msg, "rawValue0: %hu\r\n", voltage); */
      HAL_UART_Transmit(&huart1, reinterpret_cast<uint8_t*>(msg), strlen(msg), HAL_MAX_DELAY);
      _DAC.SetVoltage(0, voltage);
      // @TODO make sure that the dac is ready before sending this command
      // That's why it's in the loop here
      /* _DAC.SetVoltage(0, 30000); */
      /* _DAC.SetVoltage(1, 40000); */
      /* _DAC.SetVoltage(2, 50000); */
      /* _DAC.SetVoltage(3, 60000); */
    }
  }
}
