################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/org/Source/croutine.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/event_groups.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/list.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/queue.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/tasks.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/timers.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/org/Source/croutine.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/event_groups.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/list.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/queue.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/tasks.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/timers.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/org/Source/croutine.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/event_groups.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/list.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/queue.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/tasks.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/org/Source/%.o: ../Middlewares/Third_Party/FreeRTOS/org/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F767xx -I"/home/arthur/workspace2/ProVANT_40_3/Inc" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib/Controllers" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib/Protocol" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/CMSIS/Include" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/include" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/CMSIS_RTOS" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM7/r0p1" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/Config" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/OS" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/SEGGER"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


