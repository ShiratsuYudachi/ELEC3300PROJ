#include "SERVO42C.hpp"
#include "interface.hpp"
#include "usart.h"
#include "EasyUI.hpp"
#include "utils.hpp"
#include "main.h"

#include <stdio.h>

// create UI
Button testButton(170, 50, "YStep", 40, 40);
Button test2Button(170, 0, "SetPos", 40, 40);
Button CCWButton(30, 50, "YCCW", 40, 40);
Button CWButton(100, 50, "YCW", 40, 40);
Button test3Button(120, 0, "GetPos", 40, 40);
Slider testSlider(200, 120, 100);
TouchPad testTouchPad(0, 120);

PulseMotor xPulseMotor(&htim3, TIM_CHANNEL_1, GPIOA, GPIO_PIN_4);
// uint32_t PulseDMABuff[2560];



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
  xServo.step_UART(xdir, xSpeed, 10);
}


void myfunc()
{
  for (int i = 0; i < 2560; i++)
  {
    PulseDMABuff[i] = 36;
  }

  CWButton.onPressed = [](){yServo.spinClockwise(50);};
  CWButton.onReleased = [](){yServo.spinClockwise(0);};
  CCWButton.onPressed = [](){yServo.spinCounterClockwise(50);};
  CCWButton.onReleased = [](){yServo.spinCounterClockwise(0);};
  testButton.onPressed = [](){
    xPulseMotor.setFrequency(200);
    xPulseMotor.pulse(200);
    // PulseDMABuff[200] = 0;
    // __HAL_TIM_SET_PRESCALER(&htim3, 1000-1);
    // HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t*)PulseDMABuff, 201);
    // xServo.receiveEncoder();
    // printToLCD("x Encoder" + String(xServo.getEncoder()), 1);
  };
  test2Button.onPressed = [](){
    // xServo.receiveErrorAngle();
    // char str[20];
    // sprintf(str, "ErrorAngle: %.3f", xServo.getErrorAngle());
    // printToLCD(str, 2);
    // yServo.setPosition(testSlider.getValue());
    // debugLog(String(testTouchPad.getXRatio()*264),19);
    // xServo.setPosition(testTouchPad.getXRatio()*264);
    setPosition3d(testTouchPad.getXRatio()*264, testTouchPad.getYRatio()*146, 0);
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

  // printToLCD("Aligning Motor X", 1);
  // xServo.alignAbsolutePosition(0);
  // printToLCD("Aligning Motor Y", 1);
  // yServo.alignAbsolutePosition(0);
  // printToLCD("Aligning Motor Z", 1);
  // zServo.alignAbsolutePosition(0);
  
  
  
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