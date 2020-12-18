// Copyright 2020 Christian Maniewski.
//
// Read encoder w/ switch

#include "drivers/encoder.h"
#include <stm32l4xx_hal.h>
#include "util.h"

EncoderClass::EncoderClass() = default;

void EncoderClass::Init() {
  GPIO_InitTypeDef igpio = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();

  igpio.Pin = ENCODER_PIN_CLK | ENCODER_PIN_DATA;
  igpio.Mode = GPIO_MODE_INPUT;
  igpio.Pull = GPIO_NOPULL;
  igpio.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ENCODER_PORT, &igpio);

  igpio.Pin = ENCODER_PIN_SW;
  igpio.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ENCODER_PORT, &igpio);
}

int8_t EncoderClass::ReadEncoder() {
  // Left-shift last state and read new state
  transitionState_ <<= 2;
  // @TODO this looks just weird
  transitionState_ |=
      ((uint8_t)(!(bool)HAL_GPIO_ReadPin(ENCODER_PORT, ENCODER_PIN_CLK)) << 1);
  transitionState_ |=
      (uint8_t)(!(bool)HAL_GPIO_ReadPin(ENCODER_PORT, ENCODER_PIN_DATA));

  // Clear first four bits (our array just has 16 entries)
  transitionState_ &= 0x0f;

  // Check if valid state found
  if (encoderStates_[transitionState_]) {
    // We are expecting a full cycle, either CW or CCW, that is
    // 11 -> 10, 10 -> 00, 00 -> 01, 01 -> 11 (CW) or
    // 01 -> 00, 00 -> 10, 10 -> 11, 11 -> 01 (CCW)
    // Store the last four transition bits
    cycleCompare_ <<= 4;
    cycleCompare_ |= transitionState_;
    // We're just looking at the last byte to be a bit more generous
    if ((cycleCompare_ & 0xff) == 0b10111101) {
      // Probabl CCW (see above)
      return -1;
    }
    if ((cycleCompare_ & 0xff) == 0b00010111) {
      // Probably CW (see above)
      return 1;
    }
  }
  return 0;
};

ButtonState EncoderClass::ReadSwitch() {
  if (buttonSampleIdx_ == BUTTON_SAMPLE_SIZE) {
    buttonSampleIdx_ = 0;
    if (buttonSamples_) {
      // We're still going!
      buttonLongPressCounter_ =
          constrain(buttonLongPressCounter_ + 1, 0, UINT16_MAX);
    } else if (buttonLongPressCounter_) {
      if (buttonLongPressCounter_ > ENCODER_BUTTON_LONGPRESS_THRESHOLD) {
        buttonLongPressCounter_ = 0;
        return BUTTON_STATE_LONGPRESS;
      }
      // Long press counter started but we don't have presses anymore. It's a
      // short press
      buttonLongPressCounter_ = 0;
      return BUTTON_STATE_PRESS;
    }
    buttonSamples_ = 0;
  }
  buttonSamples_ |=
      ((!HAL_GPIO_ReadPin(ENCODER_PORT, ENCODER_PIN_SW)) << buttonSampleIdx_);
  buttonSampleIdx_++;
  return BUTTON_STATE_IDLE;
}

EncoderClass Encoder;
