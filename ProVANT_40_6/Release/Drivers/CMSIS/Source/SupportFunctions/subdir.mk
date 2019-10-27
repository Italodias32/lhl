################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Source/SupportFunctions/arm_copy_f32.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_copy_q15.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_copy_q31.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_copy_q7.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_fill_f32.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_fill_q15.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_fill_q31.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_fill_q7.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_float_to_q15.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_float_to_q31.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_float_to_q7.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_q15_to_float.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_q15_to_q31.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_q15_to_q7.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_q31_to_float.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_q31_to_q15.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_q31_to_q7.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_q7_to_float.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_q7_to_q15.c \
../Drivers/CMSIS/Source/SupportFunctions/arm_q7_to_q31.c 

OBJS += \
./Drivers/CMSIS/Source/SupportFunctions/arm_copy_f32.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_copy_q15.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_copy_q31.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_copy_q7.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_fill_f32.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_fill_q15.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_fill_q31.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_fill_q7.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_float_to_q15.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_float_to_q31.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_float_to_q7.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_q15_to_float.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_q15_to_q31.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_q15_to_q7.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_q31_to_float.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_q31_to_q15.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_q31_to_q7.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_q7_to_float.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_q7_to_q15.o \
./Drivers/CMSIS/Source/SupportFunctions/arm_q7_to_q31.o 

C_DEPS += \
./Drivers/CMSIS/Source/SupportFunctions/arm_copy_f32.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_copy_q15.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_copy_q31.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_copy_q7.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_fill_f32.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_fill_q15.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_fill_q31.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_fill_q7.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_float_to_q15.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_float_to_q31.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_float_to_q7.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_q15_to_float.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_q15_to_q31.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_q15_to_q7.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_q31_to_float.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_q31_to_q15.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_q31_to_q7.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_q7_to_float.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_q7_to_q15.d \
./Drivers/CMSIS/Source/SupportFunctions/arm_q7_to_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Source/SupportFunctions/%.o: ../Drivers/CMSIS/Source/SupportFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F767xx -I"/home/arthur/workspace3/ProVANT_40_6/Inc" -I"/home/arthur/workspace3/ProVANT_40_6/provant_lib/Controllers" -I"/home/arthur/workspace3/ProVANT_40_6/provant_lib" -I"/home/arthur/workspace3/ProVANT_40_6/provant_lib/Protocol" -I"/home/arthur/workspace3/ProVANT_40_6/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/arthur/workspace3/ProVANT_40_6/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"/home/arthur/workspace3/ProVANT_40_6/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/arthur/workspace3/ProVANT_40_6/Drivers/CMSIS/Include" -I"/home/arthur/workspace3/ProVANT_40_6/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/arthur/workspace3/ProVANT_40_6/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/arthur/workspace3/ProVANT_40_6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1"  -include"/home/arthur/workspace3/ProVANT_40_6/provant_lib/Controllers/LQR4.h" -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


