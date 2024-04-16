#include "SERVO42C.hpp"
#include "interface.hpp"
#include "usart.h"
#include "EasyUI.hpp"

#include <stdio.h>


void myfunc(){
  SERVO42C servo(0xe0, &huart2);

  Button testButton(150, 100, "Test");
  testButton.render();
  char str[20];
  strType_XPT2046_Coordinate touch;
  LCD_DrawString(0, 0, "Hello World");
  

  
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // XPT2046_Get_TouchedPoint(&touch, &strXPT2046_TouchPara);

    // sprintf(str, "x=%d, y=%d", touch.x, touch.y);
    // LCD_DrawString(0, 0, str);

    
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
    
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); 
    UIElement::updateAllElements();
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); 
    // HAL_Delay(500);
  }
}