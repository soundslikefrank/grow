// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef SRC_DRIVERS_LED_H_
#define SRC_DRIVERS_LED_H_

#include <stm32f3xx_hal.h>

class LEDClass {
 public:
  LEDClass();
  void Init();
};

extern LEDClass LED;

#endif  // SRC_DRIVERS_LED_H_
