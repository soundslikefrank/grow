// Copyright 2020 Christian Maniewski <code@chmanie.com>

#include <drivers/dac.h>
#include <math.h>
#include <stm32l4xx_hal.h>

// @TODO use hardware chip select
#define PINS_SPI GPIO_PIN_13 | GPIO_PIN_15
#define PIN_SPI_CS GPIO_PIN_12

SPI_HandleTypeDef spi;

DACClass::DACClass() = default;

void DACClass::Init() {
  GPIO_InitTypeDef gpio = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_SPI2_CLK_ENABLE();

  spi.Instance = SPI2;
  spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  spi.Init.Direction = SPI_DIRECTION_2LINES;
  spi.Init.CLKPhase = SPI_PHASE_1EDGE;
  spi.Init.CLKPolarity = SPI_POLARITY_LOW;
  spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  spi.Init.DataSize = SPI_DATASIZE_8BIT;
  spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
  spi.Init.NSS = SPI_NSS_SOFT;
  spi.Init.TIMode = SPI_TIMODE_DISABLE;
  spi.Init.Mode = SPI_MODE_MASTER;

  HAL_SPI_Init(&spi);
  // @TODO Maybe we don't need this once we're using _IT and/or msp init?
  __HAL_SPI_ENABLE(&spi);

  gpio.Pin = PINS_SPI;
  gpio.Mode = GPIO_MODE_AF_PP;
  gpio.Pull = GPIO_PULLUP;
  gpio.Speed = GPIO_SPEED_FREQ_HIGH;
  gpio.Alternate = GPIO_AF5_SPI2;

  HAL_GPIO_Init(GPIOB, &gpio);

  gpio.Pin = PIN_SPI_CS;
  gpio.Mode = GPIO_MODE_OUTPUT_PP;

  HAL_GPIO_Init(GPIOB, &gpio);
  HAL_GPIO_WritePin(GPIOB, PIN_SPI_CS, GPIO_PIN_SET);

  command_[0] = 0b00111000;
  command_[1] = 0;
  command_[2] = 1;
  HAL_GPIO_WritePin(GPIOB, PIN_SPI_CS, GPIO_PIN_RESET);
  // @TODO this can't be _IT for some reason. find out why
  HAL_SPI_Transmit(&spi, command_, 3, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOB, PIN_SPI_CS, GPIO_PIN_SET);
}

// @TODO make this take an actual voltage e.g. 8000 for 8V
void DACClass::SetVoltage(uint8_t channel, uint16_t voltage) {
  // We only have two channels
  if (channel > 1) {
    channel = 1;
  }
  /* @TODO do we need a `ready` flag? */
  /* Write to buffer with data and load DAC (selected by DB17 and DB18) */
  // @TODO it is very unclear to me why it has to be binary. See logic analyzer
  /**
   * Channel select
   * a 0b00010000
   * b 0b00010010
   * c 0b00010100
   * d 0b00010110
   */
  command_[0] = 0b00011000 | channel;
  // Upper 8 bits
  command_[1] = voltage >> 8;
  // Lower 8 bits
  command_[2] = voltage & 0xff;
  // @TODO interrupt handlers!

  HAL_GPIO_WritePin(GPIOB, PIN_SPI_CS, GPIO_PIN_RESET);
  // @TODO Make this an _IT command!!!
  HAL_SPI_Transmit(&spi, command_, 3, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOB, PIN_SPI_CS, GPIO_PIN_SET);
}

// @TODO move this function elsewhere (or remove it?)
void DACClass::SetNoteVoltage(uint8_t channel, uint8_t note, uint8_t octave) {
  // @TODO tunining (equal temperament?)
  uint8_t absoluteNote = octave * 12 + note;
  // @TODO figure out proper values here
  // We set 7V as a maximum = 84 notes = 780.xxx steps / note
  // (gain is 2.8)
  double stepsPerNote = 780.19047619;
  uint16_t voltage = round(stepsPerNote * (double)absoluteNote) - 1;
  SetVoltage(channel, voltage);
}

DACClass _DAC;
