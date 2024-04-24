#include "SERVO42C.hpp"
#include "usart.h"

SERVO42C xServo(0xe0, &huart2);
SERVO42C yServo(0xe1, &huart2);
SERVO42C zServo(0xe2, &huart2);

void step3d(uint32_t xStepCount, uint8_t xDir, uint32_t yStepCount, uint8_t yDir, uint32_t zStepCount, uint8_t zDir){
    uint32_t maxStepCount = MAX(MAX(xStepCount, yStepCount), zStepCount);
    SERVO42C* pMaxServo;
    if (maxStepCount == xStepCount){
        pMaxServo = &xServo;
    }else if (maxStepCount == yStepCount){
        pMaxServo = &yServo;
    }else{
        pMaxServo = &zServo;
    }
    SERVO42C& maxServo = *pMaxServo;

    float maxTimeConsumed = maxServo.getDistanceOf(maxStepCount) / maxServo.getLinearSpeedOf(maxServo.stepSpeed);
    float linearSpeedX = xServo.getDistanceOf(xStepCount) / maxTimeConsumed;
    float linearSpeedY = yServo.getDistanceOf(yStepCount) / maxTimeConsumed;
    float linearSpeedZ = zServo.getDistanceOf(zStepCount) / maxTimeConsumed;

    float speedParamX = xServo.getSpeedParamOfLinearSpeed(linearSpeedX);
    float speedParamY = yServo.getSpeedParamOfLinearSpeed(linearSpeedY);
    float speedParamZ = zServo.getSpeedParamOfLinearSpeed(linearSpeedZ);

    xServo.step(xDir, speedParamX, xStepCount);
    yServo.step(yDir, speedParamY, yStepCount);
    zServo.step(zDir, speedParamZ, zStepCount);
}

void setPosition3d(float x, float y, float z){
    uint8_t xDir = 0;
    uint32_t xStepCount =  xServo.getStepCountFromTargetPosition(x, xDir);
    uint8_t yDir = 0;
    uint32_t yStepCount =  yServo.getStepCountFromTargetPosition(y, yDir);
    uint8_t zDir = 0;
    uint32_t zStepCount =  zServo.getStepCountFromTargetPosition(z, zDir);
    step3d(xStepCount, xDir, yStepCount, yDir, zStepCount, zDir);
    // todo, block thread until done
}