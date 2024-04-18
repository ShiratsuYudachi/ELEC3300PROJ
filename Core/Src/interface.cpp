#include "SERVO42C.hpp"
#include "interface.hpp"
#include "usart.h"
#include "EasyUI.hpp"
#include "utils.hpp"

#include <stdio.h>


SERVO42C xServo(0xe0, &huart2);
SERVO42C yServo(0xe1, &huart2);
SERVO42C zServo(0xe2, &huart2);
void onTestButtonPress(Button* button, int x, int y){
  xServo.receiveEncoder();
  printToLCD("x Encoder"+String(xServo.getEncoder()), 1);
}

void myfunc(){
  // create UI
  Button testButton(150, 50, "Test",onTestButtonPress);
  Slider testSlider(200,120,100);
  TouchPad testTouchPad(0, 120);

  


  
  strType_XPT2046_Coordinate touch;
  printToLCD("Hello World", 1s);
  

  
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // XPT2046_Get_TouchedPoint(&touch, &strXPT2046_TouchPara);

    // sprintf(str, "x=%d, y=%d", touch.x, touch.y);
    // LCD_DrawString(0, 0, str);
    


    
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET){
      xServo.stepCounterClockwise(10);
    }
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET){
      xServo.stepClockwise(10);
    }


    uint8_t data[3] = {};
    // HAL_UART_Receive(&huart2, data, 3, 500) == HAL_OK;
    char str[3] = {};
    sprintf(str, "%02X", data[0]);
    
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); 
    UIElement::updateAllElements();
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); 
    // HAL_Delay(500);
  }
}