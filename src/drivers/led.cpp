#include "./led.h"

extern DMA_HandleTypeDef hdma_tim2_up;

LEDClass::LEDClass() = default;

void LEDClass::Init() {
  GPIO_InitTypeDef GPIO_InitStruct;
  static uint16_t data[] = {0b1100000000, 0b100000000};

  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
                        GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 |
                        GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
                        GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  hdma_tim2_up.Instance = DMA1_Channel2;
  hdma_tim2_up.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_tim2_up.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_tim2_up.Init.MemInc = DMA_MINC_ENABLE;
  hdma_tim2_up.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdma_tim2_up.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  hdma_tim2_up.Init.Mode = DMA_CIRCULAR;
  hdma_tim2_up.Init.Priority = DMA_PRIORITY_LOW;
  HAL_DMA_Init(&hdma_tim2_up);

  GPIOE->ODR = 0b0000000000000000;

  // @TODO we could use the callback when the DMA has written data to change
  // data for the next step
  HAL_DMA_Start(&hdma_tim2_up, (uint32_t)data, (uint32_t)&GPIOE->ODR, 2);
}

LEDClass LED;
