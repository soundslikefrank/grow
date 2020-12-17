// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef JACK_DETECT_H
#define JACK_DETECT_H

#include <stm32l4xx_hal.h>
#include "conf.h"

struct JackState {
  uint8_t errors;
  bool pluggedIn;
};

class JackDetectClass {
 private:
  JackState jackStates_[INPUT_JACK_LAST];
  // Pattern to look for in jack output. The value is arbitrary
  const uint32_t pattern_ = 0x80dc4370;
  uint8_t detectBit_ = 0;
  bool detectState_;

 public:
  JackDetectClass();
  void Init();
  void Next(const bool values[INPUT_JACK_LAST]);
  bool IsPluggedIn(InputJack jack);
};

extern JackDetectClass JackDetect;

#endif  // JACK_DETECT_H
