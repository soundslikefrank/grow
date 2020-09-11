// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef DAC_H
#define DAC_H

#include <stm32f3xx_hal.h>

class DACClass {
 private:
   uint8_t command_[3];
   void SetVoltage(uint8_t channel, uint16_t voltage);
 public:
  DACClass();
  void Init();
  void SetNoteVoltage(uint8_t channel, uint8_t note, uint8_t octave);
};

// @TODO find a better name
extern DACClass _DAC;

#endif  // DAC_H

