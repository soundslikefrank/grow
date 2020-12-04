// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef FADER_LED_H_
#define FADER_LED_H_

#include <stm32l4xx_hal.h>

class FaderLEDClass {
 public:
  FaderLEDClass();
  void Init();
  void SetPosition(uint8_t position);
};

extern FaderLEDClass FaderLED;

#endif  // FADER_LED_H_
