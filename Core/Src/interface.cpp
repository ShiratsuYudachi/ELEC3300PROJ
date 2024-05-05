#include "SERVO42C.hpp"
#include "interface.hpp"
#include "usart.h"
#include "EasyUI.hpp"
#include "utils.hpp"
#include "main.h"


#include <stdio.h>
#include <cmath>

#include "PathPreview.hpp"
#include "WS2812.hpp"
#include "LightController.hpp"

#include "gcode.h"
#include "gcode_inbuilt.h"


// create UI
Screen *allScreens[MAX_UI_ELEMENTS];
uint8_t screenNum;

Screen mainScreen;
Button switchButton(&mainScreen, 170, 50, "Motor?", 40, 40);
Button CCWButton(&mainScreen, 10, 50, "YCCW", 40, 40);
Button CWButton(&mainScreen, 65, 50, "YCW", 40, 40);
Button startButton(&mainScreen, 120, 50, "START", 40, 40);
Button resetButton(&mainScreen, 200, 270, "REST", 40, 40);
Joystick testJoystick(&mainScreen, 0, 120);


Screen operationScreen;
PreviewDisplay previewDisplay(&operationScreen,0, 0, 120, 120);
Slider scaleSlider(&operationScreen, 180, 20, 100);
Joystick previewJoystick(&operationScreen, 20 , 160, 100, 100);
Button selectGcodeButton(&operationScreen, 170, 170, "GCODE", 40, 40);


Screen gcodeSelectScreen;
Button item1Button(&gcodeSelectScreen, 10, 40, "ENTRPRZ", 40, 60);
Button item2Button(&gcodeSelectScreen, 70, 40, "GENSHIN", 40, 60);
Button item3Button(&gcodeSelectScreen, 130, 40, "PYRAMID", 40, 60);
Button itemExternalButton(&operationScreen, 160, 40, "EXTRN", 40, 40);




// uint32_t PulseDMABuff[2560];

SERVO42C_Pulse *pTargetMotor = &xPulseMotor;
void printTargetMotor()
{
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

void printPosition()
{
  char str[32];
  sprintf(str, "x=%.1f y=%.1f z=%.1f", xPulseMotor.getPosition(), yPulseMotor.getPosition(), zPulseMotor.getPosition());
  printToLCD(str, 1);
}


bool isMotorStuck_X(){
  return HAL_GPIO_ReadPin(SWITCH_X_0_GPIO_Port, SWITCH_X_0_Pin) == GPIO_PIN_RESET;
}
bool isMotorStuck_Y(){
  return HAL_GPIO_ReadPin(SWITCH_Y_0_GPIO_Port, SWITCH_Y_0_Pin) == GPIO_PIN_RESET;
}
bool isMotorStuck_Z(){
  return HAL_GPIO_ReadPin(SWITCH_Z_0_GPIO_Port, SWITCH_Z_0_Pin) == GPIO_PIN_RESET;
}

void setActiveScreen0(){
    mainScreen.setActive();
}

void setActiveScreen1(){
    operationScreen.setActive();
}

const float (*targetGcode)[4] = nullptr;
int targetGcodeLength = 0;
const float* targetGcodeCenterOfMass = nullptr;

enum GCODE_SOURCE{
  ENTERPRIZE,
  HKUST,
  PYRAMID,
  GENSHIN,
  EXTERNAL
};
GCODE_SOURCE gcodeSource = ENTERPRIZE;

void setGcodeSource(GCODE_SOURCE target){
  gcodeSource = target;
  switch (gcodeSource){
    case ENTERPRIZE:
      targetGcode = gcode_ENTERPRIZE;
      targetGcodeLength = gcodeLength_ENTERPRIZE;
      targetGcodeCenterOfMass = gcodeCenterOfMass_ENTERPRIZE;
      break;
    case HKUST:
      // targetGcode = gcode_HKUST;
      // targetGcodeLength = gcodeLength_HKUST;
      // targetGcodeCenterOfMass = gcodeCenterOfMass_HKUST;
      break;
    case PYRAMID:
      targetGcode = gcode_PYRAMID;
      targetGcodeLength = gcodeLength_PYRAMID;
      targetGcodeCenterOfMass = gcodeCenterOfMass_PYRAMID;
      break;
    case GENSHIN:
      targetGcode = gcode_GENSHIN;
      targetGcodeLength = gcodeLength_GENSHIN;
      targetGcodeCenterOfMass = gcodeCenterOfMass_GENSHIN;
      break;
    case EXTERNAL:
      targetGcode = gcode;
      targetGcodeLength = gcodeLength;
      targetGcodeCenterOfMass = gcodeCenterOfMass;
      break;
  }
}



void setupUI(){
  CWButton.onPressed = [](){
    pTargetMotor->setFrequency(1000);
    pTargetMotor->setDirection(0);
    pTargetMotor->spinStart();
  };

  CWButton.onReleased = []()
  {
    pTargetMotor->spinStop();
  };

  CCWButton.onPressed = []()
  {
    pTargetMotor->setDirection(1);
    pTargetMotor->spinStart();
  };

  CCWButton.onReleased = []()
  {
    pTargetMotor->spinStop();
  };

  switchButton.onPressed = []()
  {
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


  startButton.onPressed = [](){
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
    lightStatus = OPERATING;

    for (float* cmd = (float*)targetGcode; cmd < (float*)targetGcode+targetGcodeLength*4; cmd+=4){
      setPosition3d(cmd[0], cmd[1], cmd[2], cmd[3]/60.0); // divide by 60 to convert to seconds
      printPosition();
    }
    lightStatus = COMPLETE;
  };

  resetButton.onPressed = [](){
    lightStatus = RESETTING;
    xPulseMotor.setDirection(0);
    yPulseMotor.setDirection(0);
    
    isResetComplete_X = isMotorStuck_X();
    if (!isResetComplete_X){
      xPulseMotor.spinStart();
    }
    isResetComplete_Y = isMotorStuck_Y();
    if (!isResetComplete_Y){
      yPulseMotor.spinStart();
    }
    blankAll();
    while (!isResetComplete_X || !isResetComplete_Y){
      if (isMotorStuck_X()){
        xPulseMotor.spinStop();
        isResetComplete_X = true;
      }
      if (isMotorStuck_Y()){
        yPulseMotor.spinStop();
        isResetComplete_Y = true;
      }
      updateLightEffect();
    }
    lightStatus = COMPLETE;
    // zPulseMotor.setDirection(0);
    // zPulseMotor.spinStart();
  };



  testJoystick.whilePressing = [](){
    float xRatio = testJoystick.get_dX();
    char str[10];
    sprintf(str, "%.2f", xRatio);
    debugLog(str, 19);
    xPulseMotor.step(xRatio < 0 ? 0 : 1,abs(xRatio*300));
    float yRatio = testJoystick.get_dY();
    yPulseMotor.step(yRatio < 0 ? 0 : 1,abs(yRatio*300));
  };



  // operation screen
  operationScreen.onUpdate = [](){
    previewDisplay.previewScale = scaleSlider.getValue();
    previewDisplay.render2d();
  };

  previewJoystick.whilePressing = [](){
    
    float xRatio = previewJoystick.get_dX_dt() * 50;
    previewDisplay.xOffset += xRatio;
    float yRatio = previewJoystick.get_dY_dt() * 50;
    previewDisplay.yOffset += yRatio;
  };
  selectGcodeButton.onPressed = [](){
    gcodeSelectScreen.setActive();
  };


  // gcode select screen
  item1Button.onPressed = [](){
    setGcodeSource(ENTERPRIZE);
    operationScreen.setActive();
  };
  item2Button.onPressed = [](){
    setGcodeSource(GENSHIN);
    operationScreen.setActive();
  };
  item3Button.onPressed = [](){
    setGcodeSource(PYRAMID);
    operationScreen.setActive();
  };
  itemExternalButton.onPressed = [](){
    setGcodeSource(EXTERNAL);
    operationScreen.setActive();
  };
  




}

void myfunc()
{
  mainScreen.setActive();
  
  blankAll();
  HAL_Delay(500);
  playStartAnimation();

  setupUI();

  // config: AAC set to max, 1042, max freq 2200
  xPulseMotor.setFrequency(1000);
  yPulseMotor.setFrequency(1000);
  zPulseMotor.setFrequency(1000);
  printTargetMotor();

  
  // test2Button.onPressed = [](){
    
  //   // setPosition3d(testTouchPad.getXRatio()*100, testTouchPad.getYRatio()*100, testSlider.getValue()*100);
  //   xPulseMotor.step_inf(1,15000);
    
  // };

  strType_XPT2046_Coordinate touch;
  printToLCD("Hello World 1", 1);
  
  blankAll();
  while (1)
  {
    
    switch (lightStatus){
      case OPERATING:
        if ( isMotorStuck_X()){
          xPulseMotor.emergencyStop();
          lightStatus = FATAL;
        }else if ( isMotorStuck_Y()){
          yPulseMotor.emergencyStop();
          lightStatus = FATAL;
        }else if ( isMotorStuck_Z()){
          zPulseMotor.emergencyStop();
          lightStatus = FATAL;
        }
        break;
    }
    updateLightEffect();
    
    
  
    
    int startTick = HAL_GetTick();
    // rotateAngleX = xSlider.getValue() * 90;
    // rotateAngleZ = zSlider.getValue() * 90;

    // UIElement::updateAllElements(); // TODO: change to updateScreen
    // if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
    // {
    //   mainScreen.update();
    // }
    // else
    // {
    //   operationScreen.update();
    // }
    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    // HAL_Delay(500);
    

    UIElement::updateAllElements();
    debugLog(String(HAL_GetTick() - startTick), 20);
  }
}
