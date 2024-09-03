################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/EasyUI.cpp \
../Core/Src/LightController.cpp \
../Core/Src/SERVO42C.cpp \
../Core/Src/WS2812.cpp \
../Core/Src/interface.cpp \
../Core/Src/utils.cpp 

C_SRCS += \
../Core/Src/SERVO42C_IT.c \
../Core/Src/adc.c \
../Core/Src/bsp_usart.c \
../Core/Src/buzzer.c \
../Core/Src/dht11.c \
../Core/Src/dma.c \
../Core/Src/esp8266.c \
../Core/Src/fsmc.c \
../Core/Src/gpio.c \
../Core/Src/lcdtp.c \
../Core/Src/main.c \
../Core/Src/pet.c \
../Core/Src/printf.c \
../Core/Src/ring_buffer.c \
../Core/Src/rtc.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c \
../Core/Src/timer.c \
../Core/Src/usart.c \
../Core/Src/xpt2046.c 

C_DEPS += \
./Core/Src/SERVO42C_IT.d \
./Core/Src/adc.d \
./Core/Src/bsp_usart.d \
./Core/Src/buzzer.d \
./Core/Src/dht11.d \
./Core/Src/dma.d \
./Core/Src/esp8266.d \
./Core/Src/fsmc.d \
./Core/Src/gpio.d \
./Core/Src/lcdtp.d \
./Core/Src/main.d \
./Core/Src/pet.d \
./Core/Src/printf.d \
./Core/Src/ring_buffer.d \
./Core/Src/rtc.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d \
./Core/Src/timer.d \
./Core/Src/usart.d \
./Core/Src/xpt2046.d 

OBJS += \
./Core/Src/EasyUI.o \
./Core/Src/LightController.o \
./Core/Src/SERVO42C.o \
./Core/Src/SERVO42C_IT.o \
./Core/Src/WS2812.o \
./Core/Src/adc.o \
./Core/Src/bsp_usart.o \
./Core/Src/buzzer.o \
./Core/Src/dht11.o \
./Core/Src/dma.o \
./Core/Src/esp8266.o \
./Core/Src/fsmc.o \
./Core/Src/gpio.o \
./Core/Src/interface.o \
./Core/Src/lcdtp.o \
./Core/Src/main.o \
./Core/Src/pet.o \
./Core/Src/printf.o \
./Core/Src/ring_buffer.o \
./Core/Src/rtc.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o \
./Core/Src/timer.o \
./Core/Src/usart.o \
./Core/Src/utils.o \
./Core/Src/xpt2046.o 

CPP_DEPS += \
./Core/Src/EasyUI.d \
./Core/Src/LightController.d \
./Core/Src/SERVO42C.d \
./Core/Src/WS2812.d \
./Core/Src/interface.d \
./Core/Src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/EasyUI.cyclo ./Core/Src/EasyUI.d ./Core/Src/EasyUI.o ./Core/Src/EasyUI.su ./Core/Src/LightController.cyclo ./Core/Src/LightController.d ./Core/Src/LightController.o ./Core/Src/LightController.su ./Core/Src/SERVO42C.cyclo ./Core/Src/SERVO42C.d ./Core/Src/SERVO42C.o ./Core/Src/SERVO42C.su ./Core/Src/SERVO42C_IT.cyclo ./Core/Src/SERVO42C_IT.d ./Core/Src/SERVO42C_IT.o ./Core/Src/SERVO42C_IT.su ./Core/Src/WS2812.cyclo ./Core/Src/WS2812.d ./Core/Src/WS2812.o ./Core/Src/WS2812.su ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/bsp_usart.cyclo ./Core/Src/bsp_usart.d ./Core/Src/bsp_usart.o ./Core/Src/bsp_usart.su ./Core/Src/buzzer.cyclo ./Core/Src/buzzer.d ./Core/Src/buzzer.o ./Core/Src/buzzer.su ./Core/Src/dht11.cyclo ./Core/Src/dht11.d ./Core/Src/dht11.o ./Core/Src/dht11.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/esp8266.cyclo ./Core/Src/esp8266.d ./Core/Src/esp8266.o ./Core/Src/esp8266.su ./Core/Src/fsmc.cyclo ./Core/Src/fsmc.d ./Core/Src/fsmc.o ./Core/Src/fsmc.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/interface.cyclo ./Core/Src/interface.d ./Core/Src/interface.o ./Core/Src/interface.su ./Core/Src/lcdtp.cyclo ./Core/Src/lcdtp.d ./Core/Src/lcdtp.o ./Core/Src/lcdtp.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pet.cyclo ./Core/Src/pet.d ./Core/Src/pet.o ./Core/Src/pet.su ./Core/Src/printf.cyclo ./Core/Src/printf.d ./Core/Src/printf.o ./Core/Src/printf.su ./Core/Src/ring_buffer.cyclo ./Core/Src/ring_buffer.d ./Core/Src/ring_buffer.o ./Core/Src/ring_buffer.su ./Core/Src/rtc.cyclo ./Core/Src/rtc.d ./Core/Src/rtc.o ./Core/Src/rtc.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/timer.cyclo ./Core/Src/timer.d ./Core/Src/timer.o ./Core/Src/timer.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/utils.cyclo ./Core/Src/utils.d ./Core/Src/utils.o ./Core/Src/utils.su ./Core/Src/xpt2046.cyclo ./Core/Src/xpt2046.d ./Core/Src/xpt2046.o ./Core/Src/xpt2046.su

.PHONY: clean-Core-2f-Src

