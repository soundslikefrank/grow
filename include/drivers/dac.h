// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef DAC_H
#define DAC_H

#include <stm32l4xx_hal.h>

#define PINS_SPI2 GPIO_PIN_13 | GPIO_PIN_15
#define PIN_SPI2_CS GPIO_PIN_12

class DACClass {
 private:
  uint8_t command_[3];

 public:
  DACClass();
  void Init();
  void SetVoltage(uint8_t channel, float voltage);
};

// @TODO find a better name
extern DACClass _DAC;

#endif  // DAC_H

