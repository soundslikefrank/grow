// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef LED_H_
#define LED_H_

// 16LEDs * 4 control bytes + 2 latch bytes at the end
#define LED_BUFFER_SIZE 66
#define LED_MAX_BRIGHTNESS UINT16_MAX

#include <stm32l4xx_hal.h>

enum LEDColor { LED_COLOR_GREEN, LED_COLOR_RED, LED_COLOR_YELLOW };

class LEDClass {
 private:
  bool stateChange_ = false;
  uint16_t ledState_[16] = {0};
  uint8_t spiBuffer_[LED_BUFFER_SIZE] = {0};

 public:
  LEDClass();
  void Init();
  void Set(uint8_t led, LEDColor color, uint16_t brightness);
  void SetX(uint8_t led, LEDColor color, uint16_t brightness);
  void Update();
  void HandleIRQQuadSPI();
  void HandleIRQDMA();
};

extern LEDClass LED;

#endif  // LED_H_
