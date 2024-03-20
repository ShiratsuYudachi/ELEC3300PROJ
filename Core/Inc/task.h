#include "main.h"
#include "motor.hpp"
void myTask(){
    SERVO42C servo(0xe0, &huart2);
    while(1){
        servo.step(10);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); 
        HAL_Delay(500);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); 
        HAL_Delay(500);
    }
}