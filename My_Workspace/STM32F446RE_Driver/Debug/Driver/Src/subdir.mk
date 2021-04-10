################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Src/STM32F446RE_GPIO_Driver.c 

OBJS += \
./Driver/Src/STM32F446RE_GPIO_Driver.o 

C_DEPS += \
./Driver/Src/STM32F446RE_GPIO_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Src/STM32F446RE_GPIO_Driver.o: ../Driver/Src/STM32F446RE_GPIO_Driver.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Driver/Src/STM32F446RE_GPIO_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

