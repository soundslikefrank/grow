// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef ADC_H
#define ADC_H

#include <stm32l4xx_hal.h>

class ADCClass {
 private:
  static uint16_t values[12];
 public:
  ADCClass();
  uint16_t GetValue(uint8_t index);
  /* Get normalized value (percentage) */
  float GetValueN(uint8_t index);
  void Init();

};

extern ADCClass ADC;

#endif  // ADC_H

