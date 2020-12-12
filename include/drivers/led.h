// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef LED_H_
#define LED_H_

#include <stm32l4xx_hal.h>

class LEDClass {
 public:
  LEDClass();
  void Init();
};

extern LEDClass LED;

#endif  // LED_H_
