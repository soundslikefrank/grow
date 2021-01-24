#include "drivers/led.h"
#include "util.h"

QSPI_CommandTypeDef cqspi;
QSPI_HandleTypeDef hqspi;
TIM_HandleTypeDef htim15;

LEDClass::LEDClass() {
  cqspi.InstructionMode = QSPI_INSTRUCTION_NONE;
  cqspi.AddressMode = QSPI_ADDRESS_NONE;
  cqspi.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  cqspi.DataMode = QSPI_DATA_2_LINES;
  cqspi.DummyCycles = 0;
  cqspi.NbData = LED_BUFFER_SIZE;
};

void LEDClass::Init() {
  // Timer for GSCLK
  htim15.Instance = TIM15;
  htim15.Init.Prescaler = 0;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  // GSCLK needs to be pretty fast (>4MHz), otherwise there might be
  // a noticeable delay
  htim15.Init.Period = 4;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_OC_Init(&htim15);

  // Dual SPI for SIN and LAT
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 39;
  hqspi.Init.FifoThreshold = 1;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  hqspi.Init.FlashSize = 31;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  HAL_QSPI_Init(&hqspi);

  HAL_TIM_OC_Start(&htim15, TIM_CHANNEL_1);
}

void LEDClass::Set(uint8_t led, LEDColor color, uint16_t brightness) {
  // @TODO proper constrain function here
  /* brightness = constrain(brightness, 0, LED_MAX_BRIGHTNESS); */
  switch (color) {
    case LED_COLOR_GREEN:
      ledState_[14 - led * 2] = brightness;
      break;
    case LED_COLOR_RED:
      ledState_[15 - led * 2] = brightness;
      break;
    case LED_COLOR_YELLOW:
      ledState_[14 - led * 2] = brightness / 2;
      ledState_[15 - led * 2] = brightness / 2;
      break;
  }
  stateChange_ = true;
}

void LEDClass::SetX(uint8_t led, LEDColor color, uint16_t brightness) {
  for (uint8_t i = 0; i < 16; i++) {
    ledState_[i] = 0;
  }
  return Set(led, color, brightness);
}

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
    // @TODO do not recreate this variable every time?
    uint32_t ledData = ledState_[15 - i] ? joinBits(ledState_[15 - i], 0) : 0;
    // Endianness
    spiBuffer_[i * 4 + 0] = (uint8_t)(ledData >> 24);
    spiBuffer_[i * 4 + 1] = (uint8_t)(ledData >> 16);
    spiBuffer_[i * 4 + 2] = (uint8_t)(ledData >> 8);
    spiBuffer_[i * 4 + 3] = (ledData & 0xff) | 1;
  }
  // Latch into third GS register
  spiBuffer_[LED_BUFFER_SIZE - 1] = 0b01010100;
  HAL_QSPI_Command_IT(&hqspi, &cqspi);
  HAL_QSPI_Transmit_DMA(&hqspi, spiBuffer_);
}

LEDClass LED;
