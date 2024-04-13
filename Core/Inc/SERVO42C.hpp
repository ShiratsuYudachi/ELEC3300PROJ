/*
 * motor.h
 *
 *  Created on: Mar 20, 2024
 *      Author: Nico
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_
#include "main.h"

class SERVO42C {
private:
    UART_HandleTypeDef* pUART;
    uint8_t address;
    uint16_t encoder = 0;
    uint32_t encoderCarry = 0;
    
    uint8_t stepSpeed = 3;
    

    static uint8_t getCHK(uint8_t instruction[], uint8_t len){
        uint16_t result = 0;
        for (int i=0; i<len; i++){
            result+=instruction[i];
        }
        return result & 0xFF;
    }

public:
    SERVO42C(uint8_t address, UART_HandleTypeDef* pUART) : address(address), pUART(pUART){}

    // direction : 1 or 0
    // speed: 0~7
    // stepCount: each stepCount/stepDivision for 1.8 deg, currently stepDivision=1
    void step(uint8_t direction, uint8_t speed, uint32_t stepCount){
        uint8_t instruction[8] = {};
        instruction[0] = address;
        instruction[1] = 0xfd;
        instruction[2] = (direction<<7)|(speed & 0x7F);
        for (int i=0; i<4; i++){
            instruction[6-i] = (stepCount & (0xFF << 8*i))>>8*i;
        }
        instruction[7] = getCHK(instruction, 8);
        HAL_UART_Transmit(pUART, instruction, 8, 100);
    }
    void stepClockwise(uint8_t stepCount){
        step(0, stepSpeed, stepCount);
    }
    void stepCounterClockwise(uint8_t stepCount){
        step(1, stepSpeed, stepCount);
    }
};

#endif /* INC_MOTOR_H_ */
