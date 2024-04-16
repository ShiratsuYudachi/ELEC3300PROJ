extern "C"{
#include "lcdtp.h"
#include "xpt2046.h"
}
#include <cstring>
#include <stdint.h>

#define TEXT_CHAR_NUM 16
#define MAX_UI_ELEMENTS 32


class UIElement
{
public:
    static UIElement* allElements[MAX_UI_ELEMENTS];
    static uint8_t elementNum;

    virtual void render() = 0;
    virtual void update(uint16_t x, uint16_t y) = 0;

    static void updateAllElements();

protected:
    uint16_t x, y;
    uint16_t width, height;
    UIElement(uint16_t x, uint16_t y, uint16_t width, uint16_t height){
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        allElements[elementNum++] = this;
    }
    bool checkTouch(uint16_t x, uint16_t y){
        return x>=this->x && x<=this->x+width && y>=this->y && y<=this->y+height;
    }
};


class Button : public UIElement
{
private:
    uint16_t last_color = 0;
    uint16_t initialColor;
    uint16_t color;
    uint16_t textColor;
    char text[TEXT_CHAR_NUM];
public:
    bool isPressed = false;
    void (*onPressed)();

    Button(uint16_t x, uint16_t y, char text[TEXT_CHAR_NUM], void (*onPressed)() = nullptr, uint16_t width = 85, uint16_t height = 50, uint16_t color = CYAN, uint16_t textColor = BLACK)
    : UIElement(x, y, width, height)
    {
        this->initialColor = color;
        this->color = color;
        this->textColor = textColor;
        strcpy(this->text, text);
        this->onPressed = onPressed;
    }

    void render() override
    {
        // render background
        // for (int i=y; height<y?i<y+height:i>y-height; height<y?i++:i--)
        // {
        //     LCD_DrawLine(x, i, x+width, i, color);
        // }
        LCD_OpenWindow(x, y, width, height);
        LCD_FillColor(width*height, color);

        // render text
        LCD_DrawString_Color(x+width/3, y+height/3, text, color, textColor);
    }

    
    void update(u_int16_t x, u_int16_t y) override
    {
        if (checkTouch(x, y)){
            color = YELLOW;
            if (!isPressed){
                isPressed = true;
                if (onPressed) onPressed();
            }
        }
        else{
            color = initialColor;
            isPressed = false;
        }
        if (last_color != color){
            render();
            last_color = color;
        }
    }
};


