// Copyright 2020 Christian Maniewski.
//
#include "drivers/adc.h"
#include <math.h>
#include <stm32l4xx_hal.h>
#include "util.h"

ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdmaADC;

ADCClass::ADCClass() = default;

uint16_t ADCClass::values[12] = {};

void ADCClass::Init() {
  GPIO_InitTypeDef gpio = {0};
  ADC_ChannelConfTypeDef sConfig;

  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_ADC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /** Configure GPIO pins
   *
   * ADC1 sits on
   * PC0-PC3 (ADC1_IN1-ADC1_IN4)
   * PA0-PA7 (ADC1_IN5-ADC_IN12)
   */
  gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
  gpio.Mode = GPIO_MODE_ANALOG;
  gpio.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &gpio);
  gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |
             GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
  HAL_GPIO_Init(GPIOA, &gpio);

  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.ScanConvMode = ENABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  // We use TIM3's TRGO to trigger a conversion
  hadc.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T3_TRGO;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  // 12 channels
  hadc.Init.NbrOfConversion = 12;
  HAL_ADC_Init(&hadc);

  HAL_NVIC_SetPriority(DMA2_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Channel3_IRQn);

  /* ADC2 DMA Init */
  hdmaADC.Instance = DMA2_Channel3;
  hdmaADC.Init.Request = DMA_REQUEST_0;
  hdmaADC.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdmaADC.Init.PeriphInc = DMA_PINC_DISABLE;
  hdmaADC.Init.MemInc = DMA_MINC_ENABLE;
  // ADC values cover 12 bits aligned in a half-word (2 bytes)
  hdmaADC.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdmaADC.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  hdmaADC.Init.Mode = DMA_CIRCULAR;
  hdmaADC.Init.Priority = DMA_PRIORITY_LOW;
  HAL_DMA_Init(&hdmaADC);

  __HAL_LINKDMA(&hadc, DMA_Handle, hdmaADC);

  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_92CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;

  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_7;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_8;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = ADC_REGULAR_RANK_9;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_10;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = ADC_REGULAR_RANK_11;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = ADC_REGULAR_RANK_12;
  HAL_ADC_ConfigChannel(&hadc, &sConfig);

  HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(ADC1_IRQn);

  HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED);

  // casting to uint32_t as it can potentially handle a full word (4 byte)
  HAL_ADC_Start_DMA(&hadc, reinterpret_cast<uint32_t*>(values), 12);
}

// @TODO obviously this should be somewhere else
double cvACalibrationSlope = 0.0078125;
double cvACalibrationIntercept = 1.71428;
// @TODO these are not correct yet
double cvBCalibrationSlope = 0.0078125;
double cvBCalibrationIntercept = 1.71428;

uint16_t ADCClass::GetValue(uint8_t index) {
  CONSTRAIN(index, 0, 11)
  // Correct CV input values using the linear regression results in calibration
  if (index == 10) {
    return values[10] +
           (uint16_t)(round(cvACalibrationSlope * (double)values[10] +
                            cvACalibrationIntercept));
  }
  if (index == 11) {
    return values[11] +
           (uint16_t)(round(cvBCalibrationSlope * (double)values[11] +
                            cvBCalibrationIntercept));
  }

  return values[index];
}

float ADCClass::GetValueN(uint8_t index) {
  return (float)ADCClass::GetValue(index) / 4096;
}

ADCClass ADC;
