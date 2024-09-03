################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/batch/cold1.c \
../Core/batch/cold2.c \
../Core/batch/happy1.c \
../Core/batch/hot1.c \
../Core/batch/hot2.c \
../Core/batch/normal.c \
../Core/batch/sleep1.c \
../Core/batch/sleep2.c \
../Core/batch/sleep3.c \
../Core/batch/sleep_water.c \
../Core/batch/water1.c \
../Core/batch/water1_night.c \
../Core/batch/water2.c \
../Core/batch/water2_night.c \
../Core/batch/water3.c \
../Core/batch/water3_night.c 

C_DEPS += \
./Core/batch/cold1.d \
./Core/batch/cold2.d \
./Core/batch/happy1.d \
./Core/batch/hot1.d \
./Core/batch/hot2.d \
./Core/batch/normal.d \
./Core/batch/sleep1.d \
./Core/batch/sleep2.d \
./Core/batch/sleep3.d \
./Core/batch/sleep_water.d \
./Core/batch/water1.d \
./Core/batch/water1_night.d \
./Core/batch/water2.d \
./Core/batch/water2_night.d \
./Core/batch/water3.d \
./Core/batch/water3_night.d 

OBJS += \
./Core/batch/cold1.o \
./Core/batch/cold2.o \
./Core/batch/happy1.o \
./Core/batch/hot1.o \
./Core/batch/hot2.o \
./Core/batch/normal.o \
./Core/batch/sleep1.o \
./Core/batch/sleep2.o \
./Core/batch/sleep3.o \
./Core/batch/sleep_water.o \
./Core/batch/water1.o \
./Core/batch/water1_night.o \
./Core/batch/water2.o \
./Core/batch/water2_night.o \
./Core/batch/water3.o \
./Core/batch/water3_night.o 


# Each subdirectory must supply rules for building sources it contributes
Core/batch/%.o Core/batch/%.su Core/batch/%.cyclo: ../Core/batch/%.c Core/batch/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-batch

clean-Core-2f-batch:
	-$(RM) ./Core/batch/cold1.cyclo ./Core/batch/cold1.d ./Core/batch/cold1.o ./Core/batch/cold1.su ./Core/batch/cold2.cyclo ./Core/batch/cold2.d ./Core/batch/cold2.o ./Core/batch/cold2.su ./Core/batch/happy1.cyclo ./Core/batch/happy1.d ./Core/batch/happy1.o ./Core/batch/happy1.su ./Core/batch/hot1.cyclo ./Core/batch/hot1.d ./Core/batch/hot1.o ./Core/batch/hot1.su ./Core/batch/hot2.cyclo ./Core/batch/hot2.d ./Core/batch/hot2.o ./Core/batch/hot2.su ./Core/batch/normal.cyclo ./Core/batch/normal.d ./Core/batch/normal.o ./Core/batch/normal.su ./Core/batch/sleep1.cyclo ./Core/batch/sleep1.d ./Core/batch/sleep1.o ./Core/batch/sleep1.su ./Core/batch/sleep2.cyclo ./Core/batch/sleep2.d ./Core/batch/sleep2.o ./Core/batch/sleep2.su ./Core/batch/sleep3.cyclo ./Core/batch/sleep3.d ./Core/batch/sleep3.o ./Core/batch/sleep3.su ./Core/batch/sleep_water.cyclo ./Core/batch/sleep_water.d ./Core/batch/sleep_water.o ./Core/batch/sleep_water.su ./Core/batch/water1.cyclo ./Core/batch/water1.d ./Core/batch/water1.o ./Core/batch/water1.su ./Core/batch/water1_night.cyclo ./Core/batch/water1_night.d ./Core/batch/water1_night.o ./Core/batch/water1_night.su ./Core/batch/water2.cyclo ./Core/batch/water2.d ./Core/batch/water2.o ./Core/batch/water2.su ./Core/batch/water2_night.cyclo ./Core/batch/water2_night.d ./Core/batch/water2_night.o ./Core/batch/water2_night.su ./Core/batch/water3.cyclo ./Core/batch/water3.d ./Core/batch/water3.o ./Core/batch/water3.su ./Core/batch/water3_night.cyclo ./Core/batch/water3_night.d ./Core/batch/water3_night.o ./Core/batch/water3_night.su

.PHONY: clean-Core-2f-batch

