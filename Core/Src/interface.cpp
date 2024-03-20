#include "SERVO42C.hpp"
#include "interface.hpp"
#include "usart.h"
#include "lcd.h"
#include <stdio.h>

void myfunc(){
  SERVO42C servo(0xe0, &huart2);
  
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    servo.step0(10);
    uint8_t data[3] = {};
    HAL_UART_Receive(&huart2, data, 3, 500) == HAL_OK;
    char str[3] = {};
    sprintf(str, "%02X", data[0]);
    LCD_DrawString(0,0,str);
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); 
    HAL_Delay(1000);
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); 
    // HAL_Delay(500);
  }
}