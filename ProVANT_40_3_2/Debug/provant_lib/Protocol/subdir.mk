################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../provant_lib/Protocol/c_common_frame.c \
../provant_lib/Protocol/c_common_ringbuffer.c \
../provant_lib/Protocol/c_io_protocolP2P.c \
../provant_lib/Protocol/frame_pilha.c \
../provant_lib/Protocol/uart.c 

OBJS += \
./provant_lib/Protocol/c_common_frame.o \
./provant_lib/Protocol/c_common_ringbuffer.o \
./provant_lib/Protocol/c_io_protocolP2P.o \
./provant_lib/Protocol/frame_pilha.o \
./provant_lib/Protocol/uart.o 

C_DEPS += \
./provant_lib/Protocol/c_common_frame.d \
./provant_lib/Protocol/c_common_ringbuffer.d \
./provant_lib/Protocol/c_io_protocolP2P.d \
./provant_lib/Protocol/frame_pilha.d \
./provant_lib/Protocol/uart.d 


# Each subdirectory must supply rules for building sources it contributes
provant_lib/Protocol/%.o: ../provant_lib/Protocol/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F767xx -I"/home/arthur/workspace2/ProVANT_40_3/Inc" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib/Controllers" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib" -I"/home/arthur/workspace2/ProVANT_40_3/provant_lib/Protocol" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/arthur/workspace2/ProVANT_40_3/Drivers/CMSIS/Include" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/include" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/CMSIS_RTOS" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM7/r0p1" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/Config" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/OS" -I"/home/arthur/workspace2/ProVANT_40_3/Middlewares/Third_Party/SEGGER/SEGGER"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


