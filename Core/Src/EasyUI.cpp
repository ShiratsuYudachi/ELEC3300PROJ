#include "EasyUI.hpp"
#define SHOW_LOCATION 1
UIElement* UIElement::allElements[MAX_UI_ELEMENTS] = {};
uint8_t UIElement::elementNum = 0;

void UIElement::updateAllElements(){
    strType_XPT2046_Coordinate touch;
    XPT2046_Get_TouchedPoint(&touch, &strXPT2046_TouchPara);
    #if SHOW_LOCATION
    char str[20];
    LCD_DrawString(0, 0, "                     ");
    sprintf(str, "x=%d, y=%d", touch.x, touch.y);
    LCD_DrawString(0, 0, str);
    #endif
    for (int i=0; i<elementNum; i++){
        allElements[i]->update(touch.x, touch.y);
    }
    // Update all UI elements
}