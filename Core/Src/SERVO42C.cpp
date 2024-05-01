#include "SERVO42C.hpp"
#include "math.h"
// #include "usart.h"

uint32_t PulseDMABuff[DMA_BUFFER_SIZE + 1]; // the max number of steps can be perfomed once
// auto CallbackFunctions[3] = {};

SERVO42C_Pulse xPulseMotor(&htim3, TIM_CHANNEL_1, GPIOA, GPIO_PIN_4); // tim, tim channel, dir gpio, dir gpio pin
SERVO42C_Pulse yPulseMotor(&htim4, TIM_CHANNEL_1, GPIOB, GPIO_PIN_7);
SERVO42C_Pulse zPulseMotor(&htim8, TIM_CHANNEL_1, GPIOA, GPIO_PIN_7);

// speed: mm/s
// WARNING: max stepCount = DMA_BUFFER_SIZE for each axis!!!!
void step3d(uint32_t xStepCount, uint8_t xDir, uint32_t yStepCount, uint8_t yDir, uint32_t zStepCount, uint8_t zDir, float speed)
{
    float xDistance = xPulseMotor.stepcountToDistance(xStepCount);
    float yDistance = yPulseMotor.stepcountToDistance(yStepCount);
    float zDistance = zPulseMotor.stepcountToDistance(zStepCount);
    float linearDistance = sqrt(xDistance * xDistance + yDistance * yDistance + zDistance * zDistance); // mm
    if (abs(linearDistance) < 0.0001)
    {
        return;
    }
    float timeConsumed = linearDistance / speed;
    float speedX = xPulseMotor.stepcountToDistance(xStepCount) / timeConsumed;
    float speedY = yPulseMotor.stepcountToDistance(yStepCount) / timeConsumed;
    float speedZ = zPulseMotor.stepcountToDistance(zStepCount) / timeConsumed;
    
    float originalSpeedX = xPulseMotor.getSpeed();
    float originalSpeedY = yPulseMotor.getSpeed();
    float originalSpeedZ = zPulseMotor.getSpeed();

    xPulseMotor.setSpeed(speedX);
    yPulseMotor.setSpeed(speedY);
    zPulseMotor.setSpeed(speedZ);

    xPulseMotor.step(xDir, xStepCount);
    yPulseMotor.step(yDir, yStepCount);
    zPulseMotor.step(zDir, zStepCount);

    HAL_Delay(timeConsumed * 1000 * 1.2 + 25);// 1.2 is a factor to make sure the motor has enough time to finish the movement
    xPulseMotor.setSpeed(originalSpeedX);
    yPulseMotor.setSpeed(originalSpeedY);
    zPulseMotor.setSpeed(originalSpeedZ); 
}

// TODO: add a step_inf3d function based on step_inf
// NOT COMPLETED YET!!!!!!!
void step_inf3d(uint32_t xStepCount, uint8_t xDir, uint32_t yStepCount, uint8_t yDir, uint32_t zStepCount, uint8_t zDir, float speed)
{
    float xDistance = xPulseMotor.stepcountToDistance(xStepCount);
    float yDistance = yPulseMotor.stepcountToDistance(yStepCount);
    float zDistance = zPulseMotor.stepcountToDistance(zStepCount);
    float linearDistance = sqrt(xDistance * xDistance + yDistance * yDistance + zDistance * zDistance); // mm
    if (abs(linearDistance) < 0.0001)
    {
        return;
    }
    float timeConsumed = linearDistance / speed;
    float speedX = xPulseMotor.stepcountToDistance(xStepCount) / timeConsumed;
    float speedY = yPulseMotor.stepcountToDistance(yStepCount) / timeConsumed;
    float speedZ = zPulseMotor.stepcountToDistance(zStepCount) / timeConsumed;

    xPulseMotor.setSpeed(speedX);
    yPulseMotor.setSpeed(speedY);
    zPulseMotor.setSpeed(speedZ);
    // the above code is the same as step3d



    HAL_Delay(timeConsumed * 1000 * 1.2 + 10); ////1.2 is a factor to make sure the motor has enough time to finish the movement
}

void setPosition3d(float x, float y, float z, float speed)
{
    uint8_t xDir = 0;
    uint32_t xStepCount = xPulseMotor.getStepCountFromTargetPosition(x, xDir);
    uint8_t yDir = 0;
    uint32_t yStepCount = yPulseMotor.getStepCountFromTargetPosition(y, yDir);
    uint8_t zDir = 0;
    uint32_t zStepCount = zPulseMotor.getStepCountFromTargetPosition(z, zDir);
    step3d(xStepCount, xDir, yStepCount, yDir, zStepCount, zDir, speed);
}