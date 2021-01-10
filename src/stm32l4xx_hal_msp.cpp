#include <stm32l4xx_hal.h>
#include "drivers/dac.h"
#include "drivers/tim_metronome.h"

extern QSPI_HandleTypeDef hqspi;
extern TIM_HandleTypeDef htim15;

DMA_HandleTypeDef hdmaQSPI;

extern "C" {
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim) {
  GPIO_InitTypeDef gpio = {0};
  TIM_OC_InitTypeDef configOC = {0};
  TIM_MasterConfigTypeDef masterConfig = {0};

  if (htim->Instance == TIM2) {
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    gpio.Pin = GPIO_PIN_11 | GPIO_PIN_12;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &gpio);

    masterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    masterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(htim, &masterConfig);

    configOC.OCMode = TIM_OCMODE_PWM1;
    // 5ms
    configOC.Pulse = 200000;
    configOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    configOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(htim, &configOC, TIM_CHANNEL_1);

    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }
}
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef* htim) {
  GPIO_InitTypeDef gpio = {0};
  TIM_OC_InitTypeDef configOC = {0};

  if (htim->Instance == TIM15) {
    __HAL_RCC_TIM15_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* GSCLK timer configuration */
    gpio.Pin = GPIO_PIN_14;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Alternate = GPIO_AF14_TIM15;
    HAL_GPIO_Init(GPIOB, &gpio);

    configOC.OCMode = TIM_OCMODE_TOGGLE;
    configOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    configOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_OC_ConfigChannel(htim, &configOC, TIM_CHANNEL_1);
  }
}
void HAL_QSPI_MspInit(QSPI_HandleTypeDef* hqspi) {
  GPIO_InitTypeDef gpio = {0};

  __HAL_RCC_QSPI_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*
   * PB0     ------> DATA / QUADSPI_BK1_IO1
   * PB1     ------> LAT / QUADSPI_BK1_IO0
   * PB10     ------> CLK / QUADSPI_CLK
   */
  gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10;
  gpio.Mode = GPIO_MODE_AF_PP;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio.Alternate = GPIO_AF10_QUADSPI;
  HAL_GPIO_Init(GPIOB, &gpio);

  HAL_NVIC_SetPriority(QUADSPI_IRQn, 4, 4);
  HAL_NVIC_EnableIRQ(QUADSPI_IRQn);

  __HAL_RCC_DMA1_CLK_ENABLE();

  hdmaQSPI.Instance = DMA1_Channel5;
  hdmaQSPI.Init.Request = DMA_REQUEST_5;
  hdmaQSPI.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdmaQSPI.Init.PeriphInc = DMA_PINC_DISABLE;
  hdmaQSPI.Init.MemInc = DMA_MINC_ENABLE;
  hdmaQSPI.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdmaQSPI.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdmaQSPI.Init.Mode = DMA_NORMAL;
  hdmaQSPI.Init.Priority = DMA_PRIORITY_LOW;
  HAL_DMA_Init(&hdmaQSPI);

  __HAL_LINKDMA(hqspi, hdma, hdmaQSPI);

  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 5, 5);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi) {
  GPIO_InitTypeDef gpio = {0};
  if (hspi->Instance == SPI2) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SPI2_CLK_ENABLE();

    gpio.Pin = PINS_SPI2;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &gpio);

    gpio.Pin = PIN_SPI2_CS;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOB, &gpio);

    HAL_NVIC_SetPriority(SPI2_IRQn, 6, 6);
    HAL_NVIC_EnableIRQ(SPI2_IRQn);
  }
}
}

