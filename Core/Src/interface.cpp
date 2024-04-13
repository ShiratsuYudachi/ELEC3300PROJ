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
    
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET){
      servo.stepCounterClockwise(10);
    }
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET){
      servo.stepClockwise(10);
    }


    uint8_t data[3] = {};
    HAL_UART_Receive(&huart2, data, 3, 500) == HAL_OK;
    char str[3] = {};
    sprintf(str, "%02X", data[0]);
    LCD_DrawString(0,0,str);
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); 
    HAL_Delay(100);
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); 
    // HAL_Delay(500);
  }
}