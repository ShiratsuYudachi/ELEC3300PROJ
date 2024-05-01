#include <cstdint>
#include "lcdtp.h"
#include "gcode.h"
#include "trigo.h"
#include "EasyUI.hpp"
#include <cstdlib>
#include <cmath>

constexpr uint32_t posX = 60;
constexpr uint32_t posY = 170;

float scale = 1.5f;

void transformPosition(uint32_t x, uint32_t y)
{
    x = x * scale;
    y = y * scale;
}

void map2d(float speedInterval = -1)
{
    bool enableDrawing = false;
    float lastPos[4] = {0, 0, 0};
    LCD_OpenWindow(posX, posY, 100, 100);
    LCD_FillColor(100 * 100, WHITE);
    LCD_DrawLine(posX ,posY, posX+ 100,posY+0,BLACK);
    LCD_DrawLine(posX + 0,posY+ -100, posX+ 0,posY+100,BLACK);
    if (speedInterval<0){
        for (float* cmd = (float*)gcode; cmd < (float*)gcode+gcodeLegth*4; cmd+=4){
            enableDrawing = cmd[2] <= 0.001;
            if (enableDrawing)
                LCD_DrawLine(posX + lastPos[0], posY - lastPos[1], posX + cmd[0], posY - cmd[1], RED);

            for (int i = 0; i < 3; i++){
            lastPos[i] = cmd[i];
            }
        }
    }else{
         for (float* cmd = (float*)gcode; cmd < (float*)gcode+gcodeLegth*4; cmd+=4){
            enableDrawing = cmd[2] <= 0.001;
            if (enableDrawing)
                LCD_DrawLine(posX + lastPos[0], posY - lastPos[1], posX + cmd[0], posY - cmd[1], RED);
            for (int i = 0; i < 3; i++){
            lastPos[i] = cmd[i];
            }
            HAL_Delay(speedInterval);
        }
    }
}

// 实现 sin 函数，考虑周期性和符号
float fastsin(int degree){
    degree = (degree % 360 + 360) % 360; // 首先将角度规约到 0-359 度
    if (degree < 90) {
        return sinTable[degree];
    } else if (degree < 180) {
        return sinTable[179 - degree];  // 90到179度
    } else if (degree < 270) {
        return -sinTable[degree - 180];  // 180到269度
    } else {
        return -sinTable[359 - degree];  // 270到359度
    }
}

// 实现 cos 函数，使用 sin 函数
float fastcos(int degree){
    return fastsin(degree + 90);  // 直接利用 sin 函数实现
}

struct Point3D {
    float x, y, z;
};

enum Axis {
    X, Y, Z
};

float sinUnderCurrentAngleX = 0;
float cosUnderCurrentAngleX = 0;
float sinUnderCurrentAngleY = 0;
float cosUnderCurrentAngleY = 0;
float sinUnderCurrentAngleZ = 0;
float cosUnderCurrentAngleZ = 0;

Point3D rotatePoint(const Point3D &point, Axis axis) {
    Point3D newPoint;
    switch (axis) {
        case X:
            newPoint.x = point.x;
            newPoint.y = point.y * cosUnderCurrentAngleX - point.z * sinUnderCurrentAngleX;
            newPoint.z = point.y * sinUnderCurrentAngleX + point.z * cosUnderCurrentAngleX;
            break;
        case Y:
            newPoint.x = point.x * cosUnderCurrentAngleY + point.z * sinUnderCurrentAngleY;
            newPoint.y = point.y;
            newPoint.z = -point.x * sinUnderCurrentAngleY + point.z * cosUnderCurrentAngleY;
            break;
        case Z:
            newPoint.x = point.x * cosUnderCurrentAngleZ - point.y * sinUnderCurrentAngleZ;
            newPoint.y = point.x * sinUnderCurrentAngleZ + point.y * cosUnderCurrentAngleZ;
            newPoint.z = point.z;
            break;
    }
    return newPoint;
}


float rotateAngleX = 0;
float rotateAngleY = 0;
float rotateAngleZ = 0;

const int r = 110;
uint8_t vRAM[r*r*2] = {};
void setPixel(int x, int y, uint16_t color, float alpha) {
    if (x < 0 || x >= r || y < 0 || y >= r) return;
    
    uint16_t bg_color = ((uint16_t*)vRAM)[x+y*r];
    uint8_t bg_red   = (bg_color >> 11) & 0x1F;
    uint8_t bg_green = (bg_color >> 5) & 0x3F;
    uint8_t bg_blue  = bg_color & 0x1F;

    uint8_t fg_red   = (color >> 11) & 0x1F;
    uint8_t fg_green = (color >> 5) & 0x3F;
    uint8_t fg_blue  = color & 0x1F;

    uint8_t red   = (uint8_t)(bg_red * (1 - alpha) + fg_red * alpha);
    uint8_t green = (uint8_t)(bg_green * (1 - alpha) + fg_green * alpha);
    uint8_t blue  = (uint8_t)(bg_blue * (1 - alpha) + fg_blue * alpha);

    ((uint16_t*)vRAM)[x+y*r] = (red << 11) | (green << 5) | blue;
}

void drawLineToVRAM(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    bool steep = fabs(y1 - y0) > fabs(x1 - x0);
    if (steep) {
        uint16_t temp = x0;
        x0 = y0;
        y0 = temp;

        temp = x1;
        x1 = y1;
        y1 = temp;
    }
    if (x0 > x1) {
        uint16_t temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    float dx = x1 - x0;
    float dy = y1 - y0;
    float gradient = dy / dx;
    if (dx == 0.0) {
        gradient = 1;
    }

    float intery = y0 + gradient; // 初始交点的y坐标

    for (int x = x0 + 1; x <= x1; x++) {
        if (steep) {
            setPixel((int)intery, x, color, 1 - (intery - floor(intery)));
            setPixel((int)intery + 1, x, color, intery - floor(intery));
        } else {
            setPixel(x, (int)intery, color, 1 - (intery - floor(intery)));
            setPixel(x, (int)intery + 1, color, intery - floor(intery));
        }
        intery += gradient;
    }
}
void resetVRAM(){
    //memset(vRAM, 0, sizeof(vRAM));
    uint32_t color_32 = (CYAN << 16) | CYAN;
    for(int i = 0; i < r*r/2; i++)
    {
        ((uint32_t*)vRAM)[i] = color_32;
        i++;
        ((uint32_t*)vRAM)[i] = color_32;
        i++;
        ((uint32_t*)vRAM)[i] = color_32;
        i++;
        ((uint32_t*)vRAM)[i] = color_32;
        i++;
        ((uint32_t*)vRAM)[i] = color_32;
    }
}

void map3d(float posX, float posY) {
    resetVRAM();
    Point3D lastPos = {0, 0, 0};

    int centerPosX = posX + r/2;
    int centerPosY = posY + r/2;
    int vCenterX = r/2; // vRAM center
    int vCenterY = r/2; // vRAM center

    // draw circle
    sinUnderCurrentAngleX = fastsin(rotateAngleX);
    cosUnderCurrentAngleX = fastcos(rotateAngleX);
    sinUnderCurrentAngleY = fastsin(rotateAngleY);
    cosUnderCurrentAngleY = fastcos(rotateAngleY);
    sinUnderCurrentAngleZ = fastsin(rotateAngleZ);
    cosUnderCurrentAngleZ = fastcos(rotateAngleZ);
    
    for (float* cmd = (float*)gcode; cmd < (float*)gcode+gcodeLegth*4; cmd+=4){
        Point3D point = {cmd[0] - gcodeCenterOfMass[0], cmd[1] - gcodeCenterOfMass[1], cmd[2] - gcodeCenterOfMass[2]};
        point = rotatePoint(point, X);
        point = rotatePoint(point, Y);
        point = rotatePoint(point, Z);
        drawLineToVRAM(vCenterX + lastPos.x, vCenterY - lastPos.z, vCenterX + point.x, vCenterY - point.z, RED);
        lastPos = point;
    }
    LCD_OpenWindow(posX, posY, r, r);
    LCD_Write_Cmd ( CMD_SetPixel );	
    // for (int i = 0; i < r; i++) {
    //     // LCD_FillColor(10, BLUE);
    //     for (int j = 0; j < r; j++) {
    //         if (vRAM[j][i]) {
    //             LCD_Write_Data ( RED );
    //         } else {
    //             LCD_Write_Data ( CYAN );
    //         }
    //     }
    // }
    for(int i = 0; i < r*r; i++)
    {
        * ( __IO uint16_t * ) ( FSMC_Addr_LCD_DATA ) = ((uint16_t*)vRAM)[i];
        i++;
        * ( __IO uint16_t * ) ( FSMC_Addr_LCD_DATA ) = ((uint16_t*)vRAM)[i];
        i++;
        * ( __IO uint16_t * ) ( FSMC_Addr_LCD_DATA ) = ((uint16_t*)vRAM)[i];
        i++;
        * ( __IO uint16_t * ) ( FSMC_Addr_LCD_DATA ) = ((uint16_t*)vRAM)[i];
        i++;
        * ( __IO uint16_t * ) ( FSMC_Addr_LCD_DATA ) = ((uint16_t*)vRAM)[i];
    }

    // clear region
    
    
    
}

int lastX = 0;
int lastY = 0;
int lastTick = 0;
class PreviewDisplay3D : public UIElement
{
private:
    uint16_t color;

public:
    PreviewDisplay3D(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color = CYAN)
        : UIElement(x, y, width, height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->color = color;
    }
    
    void render() override
    {
        map3d(x,y);
    }

    void update(uint16_t x, uint16_t y) override
    {
        const float speedMultiplier = 1;
        if (isInvalidInput(x, y)){
            return;
        }
        if ((lastX == 0 && lastY == 0) || (HAL_GetTick() - lastTick > 100))
        {
            lastX = x;
            lastY = y;
            lastTick = HAL_GetTick();
            return;
        }
        int dX = x - lastX;
        int dY = y - lastY;
        // rotateAngleZ += dX * speedMultiplier;
        // rotateAngleX -= dY * speedMultiplier;
        render();
    }


    
};