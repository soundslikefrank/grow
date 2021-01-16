// Copyright 2020 <Christian Maniewski>

#include <stm32l4xx_hal.h>
#include <string.h>
#include <cstdio>
#include "drivers/adc_ui.h"
#include "drivers/dac.h"
#include "drivers/encoder.h"
#include "drivers/fader_led.h"
#include "drivers/jack_detect.h"
#include "drivers/led.h"
#include "drivers/tim_metronome.h"
#include "drivers/tim_ui.h"
#include "quantizer.h"
#include "sequencer.h"
#include "uart_debug.h"

// @TODO Apply
// https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html

void Error_Handler() {}

void SystemClock_Config() {
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
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_ADC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
  /** Enables the Clock Security System
   */
  HAL_RCC_EnableCSS();
  /** Configure the main internal regulator output voltage
   */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
    Error_Handler();
  }
}

int main() {
  HAL_Init();
  SystemClock_Config();
  HUART1_Init();

  Encoder.Init();
  JackDetect.Init();
  MetronomeTimer.Init();
  UITimer.Init();
  UIADC.Init();
  FaderLED.Init();
  LED.Init();
  _DAC.Init();
  Quantizer.Refresh();

  /* char msg[20] = "Hello world"; */
  char msg[30];

  uint16_t counter;
  uint8_t step;

  MetronomeTimer.SetBPM(120);
  Sequencer.Start();

  while (true) {
    if (UITimer.Tick()) {
      /* counter += Encoder.ReadEncoder(); */
      counter = 4 * UIADC.GetValue(9);
      LED.SetX(step % 8, LED_COLOR_YELLOW, counter);
      /* if (Encoder.ReadSwitch() == BUTTON_STATE_LONGPRESS) { */
      /*   counter = 1; */
      /* } */
      LED.Update();
    }
    if (MetronomeTimer.Tick()) {
      step = Sequencer.NextStep();
      uint16_t faderPos = (4096 - UIADC.GetValue(step % 8));
      uint16_t voltage = 16 * (4096 - UIADC.GetValue(7)) - 1;
      auto isPluggedIn = (uint8_t)JackDetect.IsPluggedIn(INPUT_JACK_CV_1);
      sprintf(msg, "rawValue%d: %hu, plugged in: %d\r\n", 8, UIADC.GetValue(7),
              isPluggedIn);
      HAL_UART_Transmit(&huart1, reinterpret_cast<uint8_t*>(msg), strlen(msg),
                        HAL_MAX_DELAY);
      /* _DAC.SetVoltage(0, voltage); */
      // @TODO make sure that the dac is ready before sending this command
      // That's why it's in the loop here
      _DAC.SetVoltage(0, 0);
      _DAC.SetVoltage(1, 0);
    }
  }
}

extern "C" {
// @TODO: put this somewhere sane?
void HAL_MspInit(void) {
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}
}
