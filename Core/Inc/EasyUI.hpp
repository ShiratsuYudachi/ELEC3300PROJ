extern "C"
{
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
    static UIElement *allElements[MAX_UI_ELEMENTS];
    static uint8_t elementNum;

    virtual void render() = 0;
    virtual void update(uint16_t x, uint16_t y) = 0;

    static void updateAllElements();

    uint16_t x, y;
    uint16_t width, height;

protected:
    UIElement(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        allElements[elementNum++] = this;
    }
    bool checkTouch(uint16_t x, uint16_t y)
    {
        return x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height;
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
    void (*onPressed)(Button *self, int x, int y);

    Button(uint16_t x, uint16_t y, char text[TEXT_CHAR_NUM], void (*onPressed)(Button *, int, int) = nullptr, uint16_t width = 85, uint16_t height = 50, uint16_t color = CYAN, uint16_t textColor = BLACK)
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
        LCD_FillColor(width * height, color);

        // render text
        LCD_DrawString_Color(x + width / 3, y + height / 3, text, color, textColor);
    }

    void update(u_int16_t x, u_int16_t y) override
    {
        if (checkTouch(x, y))
        {
            color = YELLOW;
            // if (!isPressed)
            //{ // only trigger once
            isPressed = true;
            render();
            last_color = color;
            if (onPressed)
                onPressed(this, x, y);
            //}
        }
        else
        {
            color = initialColor;
            isPressed = false;
        }
        if (last_color != color)
        {
            render();
            last_color = color;
        }
    }
};

class Slider : public UIElement
{
private:
    uint16_t barColor;
    float value;
    uint16_t maxValue;

    uint16_t draggerRadius = 20;
    bool isDragging = false;

    uint16_t draggerX;
    uint16_t draggerY;

public:
    Slider(
        uint16_t x,
        uint16_t y,
        uint16_t maxValue = 0,
        uint16_t width = 10,
        uint16_t height = 130,
        uint16_t barColor = CYAN) : UIElement(x, y, width, height)
    {
        this->maxValue = maxValue;
        this->barColor = barColor;
        draggerX = x + width / 2;
        draggerY = y + height / 2;
    }

    void render() override
    {
        // render bar
        LCD_OpenWindow(x, y, width, height);
        LCD_FillColor(width * height, barColor);

        // render dragger
        LCD_OpenWindow(x, draggerY, width, draggerRadius);
        LCD_FillColor(width * draggerRadius, RED);
    }

    uint16_t wrapY(u_int16_t y)
    {
        if (y > 500)
            return draggerY; // y=2048 if not touched
        if (y < this->y)
            return this->y;
        if (y > this->y + height - draggerRadius)
            return this->y + height - draggerRadius;
        return y;
    }

    void update(u_int16_t x, u_int16_t y) override
    {
        bool isDraggerTouched;
        if (isDragging)
        {
            draggerY = wrapY(y);
            render();
            isDraggerTouched = x >= draggerX - 3 * draggerRadius && x <= draggerX + 3 * draggerRadius && y >= draggerY - draggerRadius && y <= draggerY + draggerRadius;
        }
        else
        {
            isDraggerTouched = x >= draggerX - draggerRadius && x <= draggerX + draggerRadius && y >= draggerY - draggerRadius && y <= draggerY + draggerRadius;
        }
        isDragging = isDraggerTouched;
        value = (draggerY - this->y) * maxValue / height;
    }
};

class TouchPad : public UIElement
{
private:
    uint16_t color;
    uint16_t dotRadius = 10;

public:
    uint16_t dotX;
    uint16_t dotY;
    uint16_t lastDotX = 0;
    uint16_t lastDotY = 0;
    void (*onPressed)(TouchPad *, int, int) = nullptr;

    TouchPad(uint16_t x, uint16_t y, void (*onPressed)(TouchPad *, int, int) = nullptr, uint16_t width = 150, uint16_t height = 150, uint16_t color = CYAN)
        : UIElement(x, y, width, height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->color = color;
        dotX = width / 2;
        dotY = height / 2;
        this->onPressed = onPressed;
    }

    void render() override
    {
        // render background
        LCD_OpenWindow(x, y, width, height);
        LCD_FillColor(width * height, color);

        // render dot
        renderDot();
    }

    void clearDot()
    {
        LCD_OpenWindow(x + dotX, y + dotY, dotRadius, dotRadius);
        LCD_FillColor(dotRadius * dotRadius, color);
    }

    void renderDot()
    {
        LCD_OpenWindow(x + dotX, y + dotY, dotRadius, dotRadius);
        LCD_FillColor(dotRadius * dotRadius, RED);
    }

    uint16_t wrapX(u_int16_t x)
    {
        if (x > 500)
            return dotX; // x=2048 if not touched
        if (x < this->x)
            return this->x;
        if (x > this->x + width - dotRadius)
            return this->x + width - dotRadius;
        return x;
    }

    u_int16_t wrapY(u_int16_t y)
    {
        if (y > 500)
            return dotY; // y=2048 if not touched
        if (y < this->y)
            return this->y;
        if (y > this->y + height - dotRadius)
            return this->y + height - dotRadius;
        return y;
    }

    void update(u_int16_t x, u_int16_t y) override
    {
        // if the touchpad is not touched, do nothing
        if (x > 500 || y > 500)
            return;
        if (x < this->x || x > this->x + width || y < this->y || y > this->y + height)
            return;

        
        int _dotX = wrapX(x) - this->x;
        int _dotY = wrapY(y) - this->y;
        if (lastDotX != _dotX || lastDotY != _dotY)
        {
            clearDot();
            dotX = _dotX;
            dotY = _dotY;
            renderDot();
            lastDotX = dotX;
            lastDotY = dotY;
        } // render only when the coordinate changes

        // execute the function
        if (onPressed)
            onPressed(this, dotX, dotY);
    }
};
