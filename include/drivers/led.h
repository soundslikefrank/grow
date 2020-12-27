// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef LED_H_
#define LED_H_

// 16LEDs * 4 control bytes + 2 latch bytes at the end
#define LED_BUFFER_SIZE 66

#include <stm32l4xx_hal.h>

enum LEDColor { LED_COLOR_GREEN, LED_COLOR_RED, LED_COLOR_YELLOW };

const uint8_t greenLEDs[8] = {0, 2, 4, 6, 14, 12, 10, 8};
const uint8_t redLEDs[8] = {1, 3, 5, 7, 15, 13, 11, 9};

class LEDClass {
 private:
  bool stateChange_ = false;
  uint16_t ledState_[16] = {0};
  uint8_t spiBuffer_[LED_BUFFER_SIZE] = {0};
  QSPI_CommandTypeDef cqspi_ = {0};
  QSPI_HandleTypeDef hqspi_ = {nullptr};

 public:
  LEDClass();
  void Init();
  void Set(uint8_t led, LEDColor color, uint16_t brightness);
  void Update();
};

extern LEDClass LED;

#endif  // LED_H_
