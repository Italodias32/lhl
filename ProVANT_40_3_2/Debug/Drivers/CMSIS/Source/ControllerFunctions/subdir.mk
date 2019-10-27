################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Source/ControllerFunctions/arm_pid_init_f32.c \
../Drivers/CMSIS/Source/ControllerFunctions/arm_pid_init_q15.c \
../Drivers/CMSIS/Source/ControllerFunctions/arm_pid_init_q31.c \
../Drivers/CMSIS/Source/ControllerFunctions/arm_pid_reset_f32.c \
../Drivers/CMSIS/Source/ControllerFunctions/arm_pid_reset_q15.c \
../Drivers/CMSIS/Source/ControllerFunctions/arm_pid_reset_q31.c \
../Drivers/CMSIS/Source/ControllerFunctions/arm_sin_cos_f32.c \
../Drivers/CMSIS/Source/ControllerFunctions/arm_sin_cos_q31.c 

OBJS += \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_init_f32.o \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_init_q15.o \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_init_q31.o \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_reset_f32.o \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_reset_q15.o \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_reset_q31.o \
./Drivers/CMSIS/Source/ControllerFunctions/arm_sin_cos_f32.o \
./Drivers/CMSIS/Source/ControllerFunctions/arm_sin_cos_q31.o 

C_DEPS += \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_init_f32.d \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_init_q15.d \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_init_q31.d \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_reset_f32.d \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_reset_q15.d \
./Drivers/CMSIS/Source/ControllerFunctions/arm_pid_reset_q31.d \
./Drivers/CMSIS/Source/ControllerFunctions/arm_sin_cos_f32.d \
./Drivers/CMSIS/Source/ControllerFunctions/arm_sin_cos_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Source/ControllerFunctions/%.o: ../Drivers/CMSIS/Source/ControllerFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F767xx -I"/home/arthur/workspace2/ProVANT_40_3/Inc" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib/Controllers" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib/Protocol" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/CMSIS/Include" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/include" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/CMSIS_RTOS" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM7/r0p1" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/Config" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/OS" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/SEGGER"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


