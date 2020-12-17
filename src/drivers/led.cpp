#include "drivers/led.h"

// @TODO move to utility library
// Interleave bits
// Maybe we can find a more efficient way if that's needed
uint32_t JoinBits(uint16_t a, uint16_t b) {
  uint32_t result = 0;
  for (int8_t ii = 15; ii >= 0; ii--) {
    result |= (a >> ii) & 1;
    result <<= 1;
    result |= (b >> ii) & 1;
    if (ii != 0) {
      result <<= 1;
    }
  }
  return result;
}

LEDClass::LEDClass() {
  // QuadSPI command defaults (they don't change)
  cqspi_.InstructionMode = QSPI_INSTRUCTION_NONE;
  cqspi_.AddressMode = QSPI_ADDRESS_NONE;
  cqspi_.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  cqspi_.DataMode = QSPI_DATA_2_LINES;
  cqspi_.DummyCycles = 0;
  // 16LEDs * 5 control bytes + 1 latch byte
  cqspi_.NbData = 81;
};

void LEDClass::Init() {
  TIM_HandleTypeDef htim1 = {nullptr};
  TIM_OC_InitTypeDef sConfigOC = {0};
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_TIM1_CLK_ENABLE();
  __HAL_RCC_QSPI_CLK_ENABLE();

  /* GSCLK timer configuration */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 99;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_OC_Init(&htim1);

  sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);

  /* QUADSPI parameter configuration*/
  hqspi_.Instance = QUADSPI;
  hqspi_.Init.ClockPrescaler = 255;
  hqspi_.Init.FifoThreshold = 1;
  hqspi_.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  hqspi_.Init.FlashSize = 31;
  hqspi_.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi_.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi_.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi_.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  HAL_QSPI_Init(&hqspi_);

  /*
   * PB0     ------> DATA / QUADSPI_BK1_IO1
   * PB1     ------> LAT / QUADSPI_BK1_IO0
   * PB10     ------> CLK / QUADSPI_CLK
   */
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1);
}

void LEDClass::Update() {
  for (uint8_t i = 0; i < 16; i++) {
    /*
     * We need 5 bytes for the data to send:
     * 2 bytes for SIN data
     * 2 bytes for LAT silence
     * 1 byte to send LAT command
     */
    uint32_t ledData = JoinBits(0b0010000000000000, 0);
    // Endianness
    spiBuffer_[i * 5 + 0] = (uint8_t)(ledData >> 24);
    spiBuffer_[i * 5 + 1] = (uint8_t)(ledData >> 16);
    spiBuffer_[i * 5 + 2] = (uint8_t)(ledData >> 8);
    spiBuffer_[i * 5 + 3] = ledData & 0xff;
    // Latch into GS register
    spiBuffer_[i * 5 + 4] = 0b00010000;
  }
  // Latch into third GS register
  spiBuffer_[80] = 0b01010100;
  HAL_QSPI_Command(&hqspi_, &cqspi_, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
  HAL_QSPI_Transmit(&hqspi_, spiBuffer_, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

LEDClass LED;
