################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32f446xx_driver/Src/stm32f446xx_gpio_driver.c 

OBJS += \
./stm32f446xx_driver/Src/stm32f446xx_gpio_driver.o 

C_DEPS += \
./stm32f446xx_driver/Src/stm32f446xx_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
stm32f446xx_driver/Src/stm32f446xx_gpio_driver.o: ../stm32f446xx_driver/Src/stm32f446xx_gpio_driver.c stm32f446xx_driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/STM32F446RE_Driver_with_Bootloader/Bootloader/Inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/STM32F446RE_Driver_with_Bootloader/stm32f446xx_driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32f446xx_driver/Src/stm32f446xx_gpio_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

