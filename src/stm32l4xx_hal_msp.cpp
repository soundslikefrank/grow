#include <stm32l4xx_hal.h>
#include <stm32l4xx_hal_tim.h>

extern QSPI_HandleTypeDef hqspi;
extern DMA_HandleTypeDef hdma_qspi;
extern TIM_HandleTypeDef htim15;

extern "C" {
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

  hdma_qspi.Instance = DMA1_Channel5;
  hdma_qspi.Init.Request = DMA_REQUEST_5;
  hdma_qspi.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_qspi.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_qspi.Init.MemInc = DMA_MINC_ENABLE;
  hdma_qspi.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_qspi.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_qspi.Init.Mode = DMA_NORMAL;
  hdma_qspi.Init.Priority = DMA_PRIORITY_LOW;
  /* hdma_qspi.XferCpltCallback = &DMATransferComplete; */
  HAL_DMA_Init(&hdma_qspi);

  __HAL_LINKDMA(hqspi, hdma, hdma_qspi);

  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 5, 5);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}
}

