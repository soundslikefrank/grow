// Copyright 2020 Christian Maniewski.

#include "drivers/adc_ui.h"
#include <stm32l4xx_hal.h>

UIADCClass::UIADCClass() = default;

uint16_t UIADCClass::adcValues[8] = {0,0,0,0,0,0,0,0};

void UIADCClass::Init() {
  GPIO_InitTypeDef gpio = {0};
  ADC_ChannelConfTypeDef sConfig;

  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_ADC1_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /** Configure GPIO pins
   *
   * ADC1 sits on
   * PA0-PA3 (ADC1_IN1-ADC1_IN4)
   * PF4 (ADC1_IN5)
   * PC0-PC2 (ADC1_IN6-ADC1_IN8) 
   */
  gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
  gpio.Mode = GPIO_MODE_ANALOG;
  gpio.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &gpio);

  gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
  HAL_GPIO_Init(GPIOC, &gpio);

  gpio.Pin = GPIO_PIN_4;
  HAL_GPIO_Init(GPIOF, &gpio);

  hadc_.Instance = ADC1;
  hadc_.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc_.Init.Resolution = ADC_RESOLUTION_12B;
  hadc_.Init.ScanConvMode = ENABLE;
  hadc_.Init.ContinuousConvMode = DISABLE;
  hadc_.Init.DiscontinuousConvMode = DISABLE;
  hadc_.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
  hadc_.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc_.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc_.Init.DMAContinuousRequests = ENABLE;
  hadc_.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  // 8 channels
  hadc_.Init.NbrOfConversion = 8;
  HAL_ADC_Init(&hadc_);

  /* ADC1 DMA Init */
  hdmaAdc_.Instance = DMA1_Channel1;
  hdmaAdc_.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdmaAdc_.Init.PeriphInc = DMA_PINC_DISABLE;
  hdmaAdc_.Init.MemInc = DMA_MINC_ENABLE;
  // ADC values cover 12 bits aligned in a half-word (2 bytes)
  hdmaAdc_.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdmaAdc_.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  hdmaAdc_.Init.Mode = DMA_CIRCULAR;
  hdmaAdc_.Init.Priority = DMA_PRIORITY_LOW;
  HAL_DMA_Init(&hdmaAdc_);

  __HAL_LINKDMA(&hadc_, DMA_Handle, hdmaAdc_);

  // @TODO use UI Timer
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;

  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  HAL_ADC_ConfigChannel(&hadc_, &sConfig);

  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  HAL_ADC_ConfigChannel(&hadc_, &sConfig);

  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  HAL_ADC_ConfigChannel(&hadc_, &sConfig);

  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  HAL_ADC_ConfigChannel(&hadc_, &sConfig);

  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  HAL_ADC_ConfigChannel(&hadc_, &sConfig);

  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  HAL_ADC_ConfigChannel(&hadc_, &sConfig);

  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_7;
  HAL_ADC_ConfigChannel(&hadc_, &sConfig);

  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_8;
  HAL_ADC_ConfigChannel(&hadc_, &sConfig);

  HAL_NVIC_SetPriority(ADC1_2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(ADC1_2_IRQn);

  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

  HAL_ADCEx_Calibration_Start(&hadc_, ADC_SINGLE_ENDED);

  // casting to uint32_t as it can potentially handle a full word (4 byte)
  HAL_ADC_Start_DMA(&hadc_, reinterpret_cast<uint32_t*>(adcValues), 8);
}

ADC_HandleTypeDef* UIADCClass::GetADC() {
  return &hadc_;
}

DMA_HandleTypeDef* UIADCClass::GetDMA() {
  return &hdmaAdc_;
}

uint16_t UIADCClass::GetValue(uint8_t index) {
  return adcValues[index];
}

UIADCClass UIADC;
