#include "drivers/fader_led.h"

FaderLEDClass::FaderLEDClass() = default;

#define FADER_LED_PINS                                               \
  (GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | \
   GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13)

void FaderLEDClass::Init() {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Pin = FADER_LED_PINS;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  // Let's reset the ODR register as a current sink
  HAL_GPIO_WritePin(GPIOC, FADER_LED_PINS, GPIO_PIN_SET);
}

void FaderLEDClass::SetPosition(uint8_t position) {
  if (position > 7) {
    position = 7;
  }
  if (position < 0) {
    position = 0;
  }
  // Turn off all LEDs except position
  // We can do this only because all the register bits are adjecent to each
  // other
  HAL_GPIO_WritePin(GPIOC, FADER_LED_PINS & ~(1 << (6 + position)),
                    GPIO_PIN_SET);
  // Turn on LED on position
  HAL_GPIO_WritePin(GPIOC, FADER_LED_PINS & (1 << (6 + position)),
                    GPIO_PIN_RESET);
}

FaderLEDClass FaderLED;
