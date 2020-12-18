// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef ENCODER_H
#define ENCODER_H

#include <stm32l4xx_hal.h>

#define ENCODER_PORT GPIOB
#define ENCODER_PIN_CLK GPIO_PIN_5
#define ENCODER_PIN_DATA GPIO_PIN_6
#define ENCODER_PIN_SW GPIO_PIN_7
#define BUTTON_SAMPLE_SIZE 8
// 2 seconds at 4kHz sample rate (thresh = 2s / (sampleSize * 4kHz))
#define ENCODER_BUTTON_LONGPRESS_THRESHOLD 1000

enum ButtonState {
  BUTTON_STATE_IDLE,
  BUTTON_STATE_PRESS,
  BUTTON_STATE_LONGPRESS,
};

class EncoderClass {
 private:
  const bool encoderStates_[16] = {false, true, true, false, true,  false,
                                   false, true, true, false, false, true,
                                   false, true, true, false};

  uint8_t transitionState_ = 0;
  int16_t cycleCompare_ = 0;
  uint8_t buttonSamples_ = 0;
  uint8_t buttonSampleIdx_ = 0;
  uint16_t buttonLongPressCounter_ = 0;

 public:
  EncoderClass();
  void Init();
  int8_t ReadEncoder();
  ButtonState ReadSwitch();
};

extern EncoderClass Encoder;

#endif  // ENCODER_H
