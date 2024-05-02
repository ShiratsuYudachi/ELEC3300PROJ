#include "SERVO42C.hpp"
#include "interface.hpp"
#include "usart.h"
#include "EasyUI.hpp"
#include "utils.hpp"
#include "main.h"
#include "gcode.h"

#include <stdio.h>
#include <cmath>
#include "PathPreview.hpp"

#include "WS2812.hpp"
#include "LightControler.hpp"


// create UI
Button switchButton(170, 50, "Motor?", 40, 40);
// Button test2Button(170, 0, "SetPos", 40, 40);
Button CCWButton(10, 50, "YCCW", 40, 40);
Button CWButton(65, 50, "YCW", 40, 40);
Button test3Button(120, 50, "START", 40, 40);
Button resetButton(120, 0, "REST", 40, 40);
Slider xSlider(180, 120, 100);
// Slider ySlider(180, 120, 100);
Slider zSlider(220, 120, 100);
// PreviewDisplay3D previewDisplay(0, 170, 120, 120);
//TouchPad testTouchPad(0, 120);



// uint32_t PulseDMABuff[2560];


SERVO42C_Pulse* pTargetMotor = &xPulseMotor;
void printTargetMotor(){
  char str[32];
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
void printPosition(){
  char str[32];
    sprintf(str, "x=%.1f y=%.1f z=%.1f",xPulseMotor.getPosition(), yPulseMotor.getPosition(), zPulseMotor.getPosition());
    printToLCD(str, 1);
}

void myfunc()
{
  blankAll();
  HAL_Delay(500);
  playStartAnimation();

  // config: AAC set to max, 1042, max freq 2200
  xPulseMotor.setFrequency(1000);
  yPulseMotor.setFrequency(1000);
  zPulseMotor.setFrequency(1000);
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
  // test2Button.onPressed = [](){
    
  //   // setPosition3d(testTouchPad.getXRatio()*100, testTouchPad.getYRatio()*100, testSlider.getValue()*100);
  //   xPulseMotor.step_inf(1,15000);
    
  // };
  test3Button.onPressed = [](){
    // 奇怪沙漏
    // setPosition3d(0, 0, 0, speed);
    // setPosition3d(50, 50, 0, speed);
    // setPosition3d(0, 50, 0, speed);
    // setPosition3d(50, 0, 0, speed);
    // setPosition3d(0, 0, 0, speed);

    // H
    // setPosition3d(0, 0, 0, speed);
    // setPosition3d(0, -50, 0, speed);
    // setPosition3d(0, -50, 10, speed);
    // setPosition3d(0, -25, 10, speed);
    // setPosition3d(0, -25, 0, speed);
    // setPosition3d(25, -25, 0, speed);
    // setPosition3d(25, -25, 10, speed);
    // setPosition3d(25, 0, 10, speed);
    // setPosition3d(25, 0, 0, speed);
    // setPosition3d(25, -50, 0, speed);
    for (float* cmd = (float*)gcode; cmd < (float*)gcode+gcodeLegth*4; cmd+=4){
      setPosition3d(cmd[0], cmd[1], cmd[2], cmd[3]/60.0); // divide by 60 to convert to seconds
      printPosition();
    }
  };
  resetButton.onPressed = [](){
    xPulseMotor.setDirection(0);
    xPulseMotor.spinStart();
    yPulseMotor.setDirection(0);
    yPulseMotor.spinStart();
    // zPulseMotor.setDirection(0);
    // zPulseMotor.spinStart();
  };

  


  

  strType_XPT2046_Coordinate touch;
  printToLCD("Hello World 1", 1);
  // HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, PulseDMABuff, 2560);
  for (int i = 0; i < 84; i++)
  {
    // setColor(i, r, g, b);
  }
  // HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_1);
  
  // xServo.stop();

  // xServo.spinCounterClockwise(100);

  // printToLCD("Aligning Motor X", 1);
  // xServo.alignAbsolutePosition(0);
  // printToLCD("Aligning Motor Y", 1);
  // yServo.alignAbsolutePosition(0);
  // printToLCD("Aligning Motor Z", 1);
  // zServo.alignAbsolutePosition(0);
  
  
  // loop();

  blankAll();
  while (1)
  {
    updateStandbyAnimation();
    
    // HAL_Delay(100);
    // for (int i = 0; i < 84; i++) {
    //   setColor(i, 255, 255, 255);      // 设置颜色
    // }
    
    int startTick = HAL_GetTick();
    // map2d();
    rotateAngleX = xSlider.getValue() * 90;
    // rotateAngleY = ySlider.getValue() * 90;
    rotateAngleZ = zSlider.getValue() * 90;
    // yServo.receiveEncoder();
    // printPosition();
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
    debugLog(String(HAL_GetTick() - startTick), 7);
  }
}
