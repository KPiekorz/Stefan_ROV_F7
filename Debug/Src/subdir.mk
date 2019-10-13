################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ROV_Tasks.c \
../Src/adc.c \
../Src/dma.c \
../Src/eth.c \
../Src/freertos.c \
../Src/gpio.c \
../Src/main.c \
../Src/mpu6500.c \
../Src/spi.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_hal_timebase_tim.c \
../Src/stm32f7xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f7xx.c \
../Src/tim.c \
../Src/usart.c \
../Src/usb_otg.c 

OBJS += \
./Src/ROV_Tasks.o \
./Src/adc.o \
./Src/dma.o \
./Src/eth.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/main.o \
./Src/mpu6500.o \
./Src/spi.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_hal_timebase_tim.o \
./Src/stm32f7xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f7xx.o \
./Src/tim.o \
./Src/usart.o \
./Src/usb_otg.o 

C_DEPS += \
./Src/ROV_Tasks.d \
./Src/adc.d \
./Src/dma.d \
./Src/eth.d \
./Src/freertos.d \
./Src/gpio.d \
./Src/main.d \
./Src/mpu6500.d \
./Src/spi.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_hal_timebase_tim.d \
./Src/stm32f7xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f7xx.d \
./Src/tim.d \
./Src/usart.d \
./Src/usb_otg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -I"D:/Stefan_ROV/Stefan_ROV_F7/Inc" -I"D:/Stefan_ROV/Stefan_ROV_F7/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Stefan_ROV/Stefan_ROV_F7/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Stefan_ROV/Stefan_ROV_F7/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/Stefan_ROV/Stefan_ROV_F7/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/Stefan_ROV/Stefan_ROV_F7/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1" -I"D:/Stefan_ROV/Stefan_ROV_F7/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Stefan_ROV/Stefan_ROV_F7/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


