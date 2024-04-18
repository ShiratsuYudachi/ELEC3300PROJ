/*
 * motor.h
 *
 *  Created on: Mar 20, 2024
 *      Author: Nico
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_
#include "main.h"
#include "utils.hpp"

class SERVO42C {
private:
    UART_HandleTypeDef* pUART;
    uint8_t address;

    uint16_t encoder = 0;
    uint16_t zeroEncoder = 0;
    int32_t encoderCarry = 0;
    int32_t zeroEncoderCarry = 0;

    int16_t errorAngleRaw = 0; // 0~0xFFFF corresponds to 0~360 degree
    float errorAngle = 0; // 0~360 degree
    bool isShaftProtected = false;
    bool enableAbsolutePosControl = false; // only allow pos control after zero position aligned

    
    // configs
    uint8_t stepSpeed = 3;
    uint8_t stepDivision = 1;
    float stepAngle = 1.8; // degree, depends on motor type, the version we are using is 1.8
    

    

    static uint8_t getCRC(uint8_t instruction[], uint8_t len){
        uint16_t result = 0;
        for (int i=0; i<len; i++){
            result+=instruction[i];
        }
        return result & 0xFF;
    }

    // WARNING: remember to check for nullptr, which means receive failed
    uint8_t* receiveUART(uint8_t len){
        static uint8_t data[16] = {};
        HAL_UART_Receive(pUART, data, len+1, 50);
        uint8_t offset = 0;
        if (data[0] == address){
            offset = 0;
        }else if (data[1] == address){
            offset = 1;
        }

        if (data[len-1] == getCRC(data+offset, len-1)){
            // printToLCD("Check Success", 3);

            // move forward by the offset
            if (offset == 1){
                for (int i=0; i<len; i++){
                    data[i] = data[i+1];
                }
            }
            return data;
        }else{
            // printToLCD("Check fail", 3);
            //printToLCD(String(data,9), 7);
            return nullptr;
        }
    }
public:
    SERVO42C(uint8_t address, UART_HandleTypeDef* pUART) : address(address), pUART(pUART){}

    // reset zero position by turning the motor CW/CCW(0/1)
    // once the motor stops turnning, it reaches the zero position
    // WARN: this will block the program until the motor stops
    void alignAbsolutePosition(int direction = 0){
        while (errorAngle < 1.5){
            step(direction, 3, 1);
            receiveErrorAngle();
        }
        while (errorAngle > 0.3){
            step(!direction, 3, 1);
            receiveErrorAngle();
        }
        zeroEncoder = encoder;
        zeroEncoderCarry = encoderCarry;
        enableAbsolutePosControl = true;
    }

    // position : difference of degrees from zero position
    float getPosition(){ // to test
        if (enableAbsolutePosControl){
            float position = 0;
            position = (encoder - zeroEncoder + (encoderCarry - zeroEncoderCarry)*0xFFFF)/(float)0xFFFF*360;
        }
        return -1;
    }

    // position: 0~0xFFFF
    void setPosition(int16_t position){ // to test
        if (enableAbsolutePosControl){
            float currentPosition = getPosition();
            float error = position - currentPosition;
            uint8_t direction = error>0?0:1;
            error = error>0?error:-error;
            uint32_t stepCount = error/(stepAngle/stepDivision);
            step(direction, stepSpeed, stepCount);
        }
    }

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
        instruction[7] = getCRC(instruction, 8);
        HAL_UART_Transmit(pUART, instruction, 8, 100);
    }
    void stepClockwise(uint8_t stepCount){
        step(0, stepSpeed, stepCount);
    }
    void stepCounterClockwise(uint8_t stepCount){
        step(1, stepSpeed, stepCount);
    }

    // speed: 0~0x7f i.e. 0~127
    void spin(uint8_t direction, uint8_t speed){
        uint8_t instruction[4] = {};
        instruction[0] = address;
        instruction[1] = 0xf6;
        instruction[2] = (direction<<7)|(speed & 0x7F);
        instruction[3] = getCRC(instruction, 3);
        HAL_UART_Transmit(pUART, instruction, 4, 100);
    }
    void spinClockwise(uint8_t speed){
        spin(0, speed);
    }
    void spinCounterClockwise(uint8_t speed){
        spin(1, speed);
    }

    

    bool receiveEncoder(){ // To test
        uint8_t* data = nullptr;
        while (data==nullptr){
            uint8_t instruction[3] = {};
            instruction[0] = address;
            instruction[1] = 0x30;
            instruction[2] = getCRC(instruction, 2);
            HAL_UART_Transmit(pUART, instruction, 3, 50);
            data = receiveUART(8);
            debugLog("Fetching encoder");
        }
        encoder = data[5]<<8 | data[6];
        encoderCarry = data[1]<<24 | data[2]<<16 | data[3]<<8 | data[4];
    }

    void receiveErrorAngle(){ // todo
        uint8_t instruction[3] = {};
        instruction[0] = address;
        instruction[1] = 0x39;
        instruction[2] = getCRC(instruction, 2);
        HAL_UART_Transmit(pUART, instruction, 3, 50);
        uint8_t data[4] = {};
        HAL_UART_Receive(pUART, data, 4, 50);
        if (data[3] == getCRC(data, 3)){
            errorAngleRaw = data[1]<<8 | data[2];
            errorAngle = errorAngleRaw/(float)0xFFFF*360;
        }
    }

    void receiveShaftProtectionState(){ //todo
        uint8_t instruction[3] = {};
        instruction[0] = address;
        instruction[1] = 0x3E;
        instruction[2] = getCRC(instruction, 2);
        HAL_UART_Transmit(pUART, instruction, 3, 50);
        uint8_t data[3] = {};
        HAL_UART_Receive(pUART, data, 3, 50);
        if (data[2] == getCRC(data, 2)){
            isShaftProtected = data[1]==0x1;
        }
    }

    uint16_t getEncoder(){
        return encoder;
    }
    int32_t getEncoderCarry(){
        return encoderCarry;
    }
    int16_t getErrorAngleRaw(){
        return errorAngleRaw;
    }
    float getErrorAngle(){
        return errorAngle;
    }
    bool getShaftProtectionState(){
        return isShaftProtected;
    }
    






};



#endif /* INC_MOTOR_H_ */
