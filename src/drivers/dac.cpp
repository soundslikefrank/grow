// Copyright 2020 Christian Maniewski <code@chmanie.com>

#include <drivers/dac.h>
#include <math.h>
#include <stm32l4xx_hal.h>
#include "util.h"

/* Also for that dac you may want to soft reset it and then enable both dacs */
/* After each spi transmit if you’re doing back to back spi calls */

SPI_HandleTypeDef hspi2;

DACClass::DACClass() = default;

void DACClass::Init() {
  hspi2.Instance = SPI2;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.Mode = SPI_MODE_MASTER;

  HAL_SPI_Init(&hspi2);

  HAL_GPIO_WritePin(GPIOB, PIN_SPI2_CS, GPIO_PIN_SET);

  // Manually enable SPI as otherwise the clock gets messed up in the first tx
  // There might be a case for investigating this further
  __HAL_SPI_ENABLE(&hspi2);

  // Reset the DAC
  command_[0] = 0b00101000;
  command_[1] = 0;
  command_[2] = 1;
  HAL_GPIO_WritePin(GPIOB, PIN_SPI2_CS, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, command_, 3, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOB, PIN_SPI2_CS, GPIO_PIN_SET);

  // Enable the internal voltage reference
  command_[0] = 0b00111000;
  command_[1] = 0;
  command_[2] = 1;
  HAL_GPIO_WritePin(GPIOB, PIN_SPI2_CS, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, command_, 3, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOB, PIN_SPI2_CS, GPIO_PIN_SET);

  // Set gain back to 1
  command_[0] = 0b00000010;
  command_[1] = 0;
  command_[2] = 0b11;
  HAL_GPIO_WritePin(GPIOB, PIN_SPI2_CS, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, command_, 3, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOB, PIN_SPI2_CS, GPIO_PIN_SET);
}

// Polynomial regression, calibration results
// @TODO: Move somewhere else, when EPROM
float cal[2][3] = {{2.87784e-09, -0.00039953, 32.3809},
                    {2.55127e-09, -0.000398639, 17.119}};

void DACClass::SetVoltage(uint8_t channel, uint16_t voltage) {
  CONSTRAIN(channel, 0, 1);

  // Quadratic regression calibration correction
  int16_t calibAdd = round(cal[channel][0] * pow(voltage, 2) +
                            cal[channel][1] * voltage + cal[channel][2]);

  voltage = clampU16(static_cast<int32_t>(voltage + calibAdd));

  // @FIXv0.2 For v0.2 (channels are switched)
  channel = channel == 1 ? 0 : 1;
  // Write to buffer with data and load DAC (selected by DB17 and DB18)
  command_[0] = 0b00011000 | channel;
  // Upper 8 bits
  command_[1] = voltage >> 8;
  // Lower 8 bits
  command_[2] = voltage & 0xff;

  HAL_GPIO_WritePin(GPIOB, PIN_SPI2_CS, GPIO_PIN_RESET);
  HAL_SPI_Transmit_IT(&hspi2, command_, 3);
}

DACClass _DAC;
