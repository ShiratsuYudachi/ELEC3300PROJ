#include "SERVO42C.hpp"
#include "interface.hpp"
#include "usart.h"
#include "EasyUI.hpp"
#include "utils.hpp"

#include <stdio.h>



SERVO42C xServo(0xe0, &huart2);
SERVO42C yServo(0xe1, &huart2);
SERVO42C zServo(0xe2, &huart2);

// create UI
Button testButton(170, 50, "YStep", 40, 40);
Button test2Button(170, 0, "SetPos", 40, 40);
Button CCWButton(30, 50, "YCCW", 40, 40);
Button CWButton(100, 50, "YCW", 40, 40);
Button test3Button(120, 0, "GetPos", 40, 40);
Slider testSlider(200, 120, 100);
TouchPad testTouchPad(0, 120);

void MoveXY(TouchPad *touchPad, int x, int y)
{
  uint8_t xdir = 1, ydir = 1;
  if (x-touchPad->width/2 < 0)
  {
    xdir = 0;
  }
  if (y-touchPad->height/2 < 0)
  {
    ydir = 0;
  }
  int a = (x-touchPad->width/2);
  a < 0 ? a = -a : a = a;
  uint8_t xSpeed = a/(touchPad->height/2)*7;
  xServo.step(xdir, xSpeed, 10);
}


void myfunc()
{
  CWButton.onPressed = [](){yServo.spinClockwise(50);};
  CWButton.onReleased = [](){yServo.spinClockwise(0);};
  CCWButton.onPressed = [](){yServo.spinCounterClockwise(50);};
  CCWButton.onReleased = [](){yServo.spinCounterClockwise(0);};
  testButton.onPressed = [](){
    yServo.stepClockwise(6400);
    // xServo.receiveEncoder();
    // printToLCD("x Encoder" + String(xServo.getEncoder()), 1);
  };
  test2Button.onPressed = [](){
    // xServo.receiveErrorAngle();
    // char str[20];
    // sprintf(str, "ErrorAngle: %.3f", xServo.getErrorAngle());
    // printToLCD(str, 2);
    yServo.setPosition(testSlider.getValue());
    debugLog(String(testTouchPad.getXRatio()*400),19);
    xServo.setPosition(testTouchPad.getXRatio()*400);
  };
  test3Button.onPressed = [](){
    yServo.receiveEncoder();
    char str[20];
    sprintf(str, "yPos=%.2f", yServo.getPosition());
    printToLCD(str, 2);
  };

  

  strType_XPT2046_Coordinate touch;
  printToLCD("Hello World 1", 1);
  
  // xServo.stop();

  // xServo.spinCounterClockwise(100);

  yServo.alignAbsolutePosition(0);
  xServo.alignAbsolutePosition(0);
  
  
  while (1)
  {
    // yServo.receiveEncoder();
      
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // XPT2046_Get_TouchedPoint(&touch, &strXPT2046_TouchPara);

    // sprintf(str, "x=%d, y=%d", touch.x, touch.y);
    // LCD_DrawString(0, 0, str);

    // uint8_t data[3] = {};
    // HAL_UART_Receive(&huart2, data, 3, 500) == HAL_OK;
    // char str[3] = {};
    // sprintf(str, "%02X", data[0]);

    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    UIElement::updateAllElements();
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    // HAL_Delay(500);
  }
}