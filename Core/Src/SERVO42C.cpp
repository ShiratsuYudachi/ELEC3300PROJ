#include "SERVO42C.hpp"
// #include "usart.h"

uint32_t PulseDMABuff[DMA_BUFFER_SIZE]; // the max number of steps can be perfomed once


SERVO42C_Pulse xPulseMotor(&htim3, TIM_CHANNEL_1, GPIOA, GPIO_PIN_4); // tim, tim channel, dir gpio, dir gpio pin
SERVO42C_Pulse yPulseMotor(&htim4, TIM_CHANNEL_1, GPIOB, GPIO_PIN_7);
SERVO42C_Pulse zPulseMotor(&htim8, TIM_CHANNEL_1, GPIOA, GPIO_PIN_7);

void step3d(uint32_t xStepCount, uint8_t xDir, uint32_t yStepCount, uint8_t yDir, uint32_t zStepCount, uint8_t zDir){
    uint32_t maxStepCount = MAX(MAX(xStepCount, yStepCount), zStepCount);
    SERVO42C_Pulse* pMaxServo;
    if (maxStepCount == xStepCount){
        pMaxServo = &xPulseMotor;
    }else if (maxStepCount == yStepCount){
        pMaxServo = &yPulseMotor;
    }else{
        pMaxServo = &zPulseMotor;
    }
    

    float maxTimeConsumed = pMaxServo->stepcountToDistance(maxStepCount) / pMaxServo->getSpeed();
    float speedX = xPulseMotor.stepcountToDistance(xStepCount) / maxTimeConsumed;
    float speedY = yPulseMotor.stepcountToDistance(yStepCount) / maxTimeConsumed;
    float speedZ = zPulseMotor.stepcountToDistance(zStepCount) / maxTimeConsumed;
    
    xPulseMotor.setSpeed(speedX);
    yPulseMotor.setSpeed(speedY);
    zPulseMotor.setSpeed(speedZ);
    
    xPulseMotor.step(xDir, xStepCount);
    yPulseMotor.step(yDir, yStepCount);
    zPulseMotor.step(zDir, zStepCount);
}

void setPosition3d(float x, float y, float z){
    uint8_t xDir = 0;
    uint32_t xStepCount =  xPulseMotor.getStepCountFromTargetPosition(x, xDir);
    uint8_t yDir = 0;
    uint32_t yStepCount =  yPulseMotor.getStepCountFromTargetPosition(y, yDir);
    uint8_t zDir = 0;
    uint32_t zStepCount =  zPulseMotor.getStepCountFromTargetPosition(z, zDir);
    step3d(xStepCount, xDir, yStepCount, yDir, zStepCount, zDir);
    // todo, block thread until done
}