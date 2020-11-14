// Copyright 2020 Christian Maniewski <code@chmanie.com>

#include <drivers/dac.h>
#include <math.h>
#include <stm32f3xx_hal.h>

// @TODO use hardware chip select
#define PINS_SPI GPIO_PIN_5 | GPIO_PIN_7
// @TODO have these in a config file somewhere
#define GPIO_PORT GPIOA
// @TODO Adjust this value
#define DAC_VOLTAGE_MULTIPLIER 10

SPI_HandleTypeDef spi;

DACClass::DACClass() = default;

void DACClass::Init() {
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_SPI1_CLK_ENABLE();

  spi.Instance = SPI1;
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
  __HAL_SPI_ENABLE(&spi);

  GPIO_InitStruct.Pin = PINS_SPI;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

// @TODO make this take an actual voltage e.g. 8000 for 8V
void DACClass::SetVoltage(uint8_t channel, uint16_t voltage) {
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
  command_[0] = 0b00010000 | (channel * 2);
  /* command_[0] = 0b00010110; */
  // Upper 8 bits
  command_[1] = voltage >> 8;
  // Lower 8 bits
  command_[2] = voltage & 0xff;
  // @TODO interrupt handlers!

  // @TODO this can't be _IT for some reason. find out why
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&spi, command_, 3, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

// @TODO move this function elsewhere
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
