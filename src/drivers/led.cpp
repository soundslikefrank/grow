#include "drivers/led.h"
#include "util.h"

LEDClass::LEDClass() {
  // QuadSPI command defaults (they don't change)
  cqspi_.InstructionMode = QSPI_INSTRUCTION_NONE;
  cqspi_.AddressMode = QSPI_ADDRESS_NONE;
  cqspi_.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  cqspi_.DataMode = QSPI_DATA_2_LINES;
  cqspi_.DummyCycles = 0;
  cqspi_.NbData = LED_BUFFER_SIZE;
};

void LEDClass::Init() {
  TIM_HandleTypeDef htim1 = {nullptr};
  TIM_OC_InitTypeDef sConfigOC = {0};
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_TIM15_CLK_ENABLE();
  __HAL_RCC_QSPI_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  hdma_.Instance = DMA1_Channel5;
  hdma_.Init.Request = DMA_REQUEST_5;
  hdma_.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_.Init.MemInc = DMA_MINC_ENABLE;
  hdma_.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_.Init.Mode = DMA_NORMAL;
  hdma_.Init.Priority = DMA_PRIORITY_LOW;
  /* hdma_.XferCpltCallback = &DMATransferComplete; */
  HAL_DMA_Init(&hdma_);

  /* GSCLK timer configuration */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF14_TIM15;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  htim1.Instance = TIM15;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  // GSCLK needs to be pretty fast (>2MHz)
  htim1.Init.Period = 19;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_OC_Init(&htim1);

  sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);

  /* QUADSPI parameter configuration*/
  hqspi_.Instance = QUADSPI;
  hqspi_.Init.ClockPrescaler = 39;
  hqspi_.Init.FifoThreshold = 1;
  hqspi_.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  hqspi_.Init.FlashSize = 31;
  hqspi_.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi_.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi_.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi_.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  HAL_QSPI_Init(&hqspi_);

  HAL_NVIC_SetPriority(QUADSPI_IRQn, 4, 4);
  HAL_NVIC_EnableIRQ(QUADSPI_IRQn);

  __HAL_LINKDMA(&hqspi_, hdma, hdma_);

  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 5, 5);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

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

void LEDClass::Set(uint8_t led, LEDColor color, uint16_t brightness) {
  stateChange_ = true;
  switch (color) {
    case LED_COLOR_GREEN:
      ledState_[greenLEDs[led]] = brightness;
      break;
    case LED_COLOR_RED:
      ledState_[redLEDs[led]] = brightness;
      break;
    case LED_COLOR_YELLOW:
      ledState_[greenLEDs[led]] = brightness / 2;
      ledState_[redLEDs[led]] = brightness / 2;
      break;
  }
}

// @TODO like this only one LED can be ON at a time.
// For different behaviour we should create a state object
// for all the LED states and update that regularly
void LEDClass::Update() {
  if (!stateChange_) {
    return;
  }
  stateChange_ = false;
  for (uint8_t i = 0; i < 16; i++) {
    /*
     * We need 4 bytes for the data to send:
     * 2 bytes for SIN data
     * 2 bytes for LAT silence
     */
    /* uint32_t ledData = (15 - i) == led ? joinBits(brightness, 0) : 0; */
    // @TODO do not recreate this variable every time?
    /* uint32_t ledData = joinBits(0b1000000000000000, 0); */
    uint32_t ledData = ledState_[15 - i] ? joinBits(ledState_[15 - i], 0) : 0;
    // Endianness
    spiBuffer_[i * 4 + 0] = (uint8_t)(ledData >> 24);
    spiBuffer_[i * 4 + 1] = (uint8_t)(ledData >> 16);
    spiBuffer_[i * 4 + 2] = (uint8_t)(ledData >> 8);
    spiBuffer_[i * 4 + 3] = (ledData & 0xff) | 1;
  }
  // Latch into third GS register
  spiBuffer_[LED_BUFFER_SIZE - 1] = 0b01010100;
  HAL_QSPI_Command_IT(&hqspi_, &cqspi_);
  HAL_QSPI_Transmit_DMA(&hqspi_, spiBuffer_);
}

void LEDClass::HandleIRQQuadSPI() { HAL_QSPI_IRQHandler(&hqspi_); }

void LEDClass::HandleIRQDMA() { HAL_DMA_IRQHandler(&hdma_); }

LEDClass LED;
