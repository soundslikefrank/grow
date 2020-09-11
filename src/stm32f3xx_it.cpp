#include "drivers/tim_ui.h"
#include "drivers/tim_metronome.h"

extern "C" {
void TIM2_IRQHandler(void) { HAL_TIM_IRQHandler(MetronomeTimer.GetTimer()); }
void TIM7_IRQHandler(void) { HAL_TIM_IRQHandler(UITimer.GetTimer()); }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) {
    MetronomeTimer.SetTick();
  }
  if (htim->Instance == TIM7) {
    UITimer.SetTick();
  }
}
}

