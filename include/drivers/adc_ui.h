// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef ADC_UI_H
#define ADC_UI_H

#include <stm32l4xx_hal.h>

class UIADCClass {
 private:
  static uint16_t adcValues[8];
  ADC_HandleTypeDef hadc_;
  DMA_HandleTypeDef hdmaAdc_;
 public:
  UIADCClass();
  ADC_HandleTypeDef* GetADC();
  DMA_HandleTypeDef* GetDMA();
  uint16_t GetValue(uint8_t index);
  void Init();

};

extern UIADCClass UIADC;

#endif  // ADC_UI_H

