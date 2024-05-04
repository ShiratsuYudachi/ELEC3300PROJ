#include "EasyUI.hpp"
#include "utils.hpp"
#define SHOW_LOCATION 1
UIElement *UIElement::allElements[MAX_UI_ELEMENTS] = {};
uint8_t UIElement::elementNum = 0;

void UIElement::updateAllElements()
{
    static bool firstCall = false;
    if (!firstCall)
    {
        for (int i = 0; i < elementNum; i++)
        {
            allElements[i]->render();
        }
        printToLCD("x=   , y=   ", 0);
        firstCall = true;
    }
    strType_XPT2046_Coordinate touch;
    XPT2046_Get_TouchedPoint(&touch, &strXPT2046_TouchPara);
#if SHOW_LOCATION
    char str[STRING_LEN];
    // Refresh the coordinate only when touched
    // if ((touch.x < 230 || touch.y < 300) && (touch.x > 0 && touch.y > 0))
    // {
        // if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
        // {
            sprintf(str, "x=%d, y=%d", touch.x, touch.y);
            // printToLCD(str, 0);
        // }
    // }
#endif
    for (int i = 0; i < elementNum; i++)
    {
        allElements[i]->update(touch.x, touch.y);
    }
    touch.x = 0;
    touch.y = 0;
    // Update all UI elements
}