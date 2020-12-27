// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef LED_H_
#define LED_H_

#include <stm32l4xx_hal.h>

class LEDClass {
 private:
  // @TODO: Idea! Keep the LED state stored in class instance
  // to be able to just toggle individual LEDs
  // Initialize with 0?
  uint8_t spiBuffer_[81] = {0};
  QSPI_CommandTypeDef cqspi_ = {0};
  QSPI_HandleTypeDef hqspi_ = {nullptr};

 public:
  LEDClass();
  void Init();
  void Update(uint8_t led, uint16_t brightness);
};

extern LEDClass LED;

#endif  // LED_H_
