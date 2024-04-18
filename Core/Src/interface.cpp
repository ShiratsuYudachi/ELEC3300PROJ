#include "SERVO42C.hpp"
#include "interface.hpp"
#include "usart.h"
#include "EasyUI.hpp"
#include "utils.hpp"

#include <stdio.h>

SERVO42C xServo(0xe0, &huart2);
SERVO42C yServo(0xe1, &huart2);
SERVO42C zServo(0xe2, &huart2);
void onTestButtonPress(Button *button, int x, int y)
{
  xServo.receiveEncoder();
  printToLCD("x Encoder" + String(xServo.getEncoder()), 1);
}

void CW(Button *button, int x, int y)
{
  xServo.stepClockwise(10);
}

void CCW(Button *button, int x, int y)
{
  xServo.stepCounterClockwise(10);
}

void myfunc()
{
  // create UI
  Button testButton(170, 50, "Read", onTestButtonPress, 40, 40);
  Button CWButton(30, 50, "CW", CW, 40, 40);
  Button CCWButton(100, 50, "CCW", CCW, 40, 40);
  Slider testSlider(200, 120, 100);
  TouchPad testTouchPad(0, 120);

  strType_XPT2046_Coordinate touch;
  printToLCD("Hello World", 0);

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // XPT2046_Get_TouchedPoint(&touch, &strXPT2046_TouchPara);

    // sprintf(str, "x=%d, y=%d", touch.x, touch.y);
    // LCD_DrawString(0, 0, str);

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