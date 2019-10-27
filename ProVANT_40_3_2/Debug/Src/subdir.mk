################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/code.c \
../Src/freertos.c \
../Src/main.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_hal_timebase_tim.c \
../Src/stm32f7xx_it.c \
../Src/system_stm32f7xx.c 

OBJS += \
./Src/code.o \
./Src/freertos.o \
./Src/main.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_hal_timebase_tim.o \
./Src/stm32f7xx_it.o \
./Src/system_stm32f7xx.o 

C_DEPS += \
./Src/code.d \
./Src/freertos.d \
./Src/main.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_hal_timebase_tim.d \
./Src/stm32f7xx_it.d \
./Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F767xx -I"/home/arthur/workspace2/ProVANT_40_3/Inc" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib/Controllers" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib/Protocol" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/CMSIS/Include" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/include" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/CMSIS_RTOS" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM7/r0p1" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/Config" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/OS" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/SEGGER"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


