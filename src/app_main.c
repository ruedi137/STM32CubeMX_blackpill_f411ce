/**
  ******************************************************************************
  * @file    main.c
  * @author  rw
  * @brief   Serial printf for blackpill V2.0
  ******************************************************************************
*/

#include <stdio.h>

#include "app_main.h"
#include "serial_printf.h"

int app_main(void) {
  
  myprintf("Systemstart auf STM32F411CE. Frequenz: %lu MHz\r\n", HAL_RCC_GetSysClockFreq() / 1000000);
  
  while (1)
  {
    myprintf("Heartbeat: Tick %lu\r\n", HAL_GetTick());
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
    HAL_Delay(500);
      }
}

// void SysTick_Handler(void) {
//   HAL_IncTick();
// }

/* void LED_Init() {
  LED_GPIO_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
} */
