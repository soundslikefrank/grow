#include "drivers/fader_led.h"

FaderLEDClass::FaderLEDClass() = default;

void FaderLEDClass::Init() {
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
                        GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Let's reset the ODR register as a current sink
  GPIOB->ODR = 0x0000ffff;
}

void FaderLEDClass::SetPosition(uint8_t position) {
  if (position > 7) {
    position = 7;
  }
  if (position < 0) {
    position = 0;
  }

  // Just light LED in given position (first byte sets LED register)
  GPIOB->ODR = 0x0000ffff & ~(1 << (8 + position));
}

FaderLEDClass FaderLED;
