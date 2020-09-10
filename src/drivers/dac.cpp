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
}

void DACClass::SetVoltage(uint8_t channel, uint16_t voltage) {
  /* @TODO do we need a `ready` flag? */
  /* Write to buffer with data and load DAC (selected by DB17 and DB18) */
  /* command[0] = 0b00010000; */
  command[0] = 0x10;
  /**
   * Channel select
   * a 0b00010000
   * b 0b00010010
   * c 0b00010100
   * d 0b00010110
   */
  command[0] |= channel << 1;
  // Upper 8 bits
  command[1] = voltage >> 8;
  // Lower 8 bits
  command[2] = voltage & 0xff;
  // @TODO interrupt handlers!
  HAL_SPI_Transmit_IT(&spi, command, 3);
}

void DACClass::SetNoteVoltage(uint8_t channel, uint8_t note, uint8_t octave) {
  // @TODO this is definitely not correct, adjust these values according to the
  // used op-amp Calculate V/OCT value divided by the voltage multiplier
  float absoluteNote = (float)octave + (float)note / 12.0;
  uint16_t voltage = floor(1000.0 * absoluteNote / DAC_VOLTAGE_MULTIPLIER);
  SetVoltage(channel, voltage);
}

DACClass _DAC;
