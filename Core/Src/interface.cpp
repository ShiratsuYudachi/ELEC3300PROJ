#include "SERVO42C.hpp"
#include "interface.hpp"
#include "usart.h"
#include "EasyUI.hpp"
#include "utils.hpp"
#include "main.h"

#include <stdio.h>

// create UI
Button switchButton(170, 50, "Motor?", 40, 40);
Button test2Button(170, 0, "SetPos", 40, 40);
Button CCWButton(30, 50, "YCCW", 40, 40);
Button CWButton(100, 50, "YCW", 40, 40);
Button test3Button(120, 0, "GetPos", 40, 40);
Slider testSlider(200, 120, 100);
TouchPad testTouchPad(0, 120);

SERVO42C_Pulse xPulseMotor(&htim3, TIM_CHANNEL_1, GPIOA, GPIO_PIN_4); // tim, tim channel, dir gpio, dir gpio pin
SERVO42C_Pulse yPulseMotor(&htim4, TIM_CHANNEL_1, GPIOB, GPIO_PIN_7);
SERVO42C_Pulse zPulseMotor(&htim8, TIM_CHANNEL_1, GPIOA, GPIO_PIN_7);

// uint32_t PulseDMABuff[2560];


SERVO42C_Pulse* pTargetMotor = &xPulseMotor;
void printTargetMotor(){
  char str[20];
  if (pTargetMotor == &xPulseMotor)
  {
    sprintf(str, "Target: X");
  }
  else if (pTargetMotor == &yPulseMotor)
  {
    sprintf(str, "Target: Y");
  }
  else
  {
    sprintf(str, "Target: Z");
  }
  printToLCD(str, 2);

}
void myfunc()
{
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);

  for (int i = 0; i < 2560; i++)
  {
    PulseDMABuff[i] = 36;
  }
  

  // config: AAC set to max, 1042
  xPulseMotor.setFrequency(2200);
  yPulseMotor.setFrequency(2200);
  zPulseMotor.setFrequency(2200);
  printTargetMotor();

  

  CWButton.onPressed = [](){
    pTargetMotor->setDirection(0);
    pTargetMotor->spinStart();
  };
  CWButton.onReleased = [](){
    pTargetMotor->spinStop();
  };
  CCWButton.onPressed = [](){
    pTargetMotor->setDirection(1);
    pTargetMotor->spinStart();
    
  };
  CCWButton.onReleased = [](){
    pTargetMotor->spinStop();
  };
  
  switchButton.onPressed = [](){
    if (pTargetMotor == &xPulseMotor)
    {
      pTargetMotor = &yPulseMotor;
    }
    else if (pTargetMotor == &yPulseMotor)
    {
      pTargetMotor = &zPulseMotor;
    }
    else
    {
      pTargetMotor = &xPulseMotor;
    }
    printTargetMotor();
  };
  test2Button.onPressed = [](){
    // xServo.receiveErrorAngle();
    // char str[20];
    // sprintf(str, "ErrorAngle: %.3f", xServo.getErrorAngle());
    // printToLCD(str, 2);
    // yServo.setPosition(testSlider.getValue());
    // debugLog(String(testTouchPad.getXRatio()*264),19);
    // xServo.setPosition(testTouchPad.getXRatio()*264);
    // setPosition3d(testTouchPad.getXRatio()*264, testTouchPad.getYRatio()*146, 0);
  };
  test3Button.onPressed = [](){
    // yServo.receiveEncoder();
    char str[20];
    // sprintf(str, "yPos=%.2f", yServo.getPosition());
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