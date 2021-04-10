################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/1_blink_led_push_pull.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/1_blink_led_push_pull.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/1_blink_led_push_pull.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/1_blink_led_push_pull.o: ../Src/1_blink_led_push_pull.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/HCSR04_Ultrasonice_Sensor/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/LCD_HD44780_Driver/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/1_blink_led_push_pull.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/HCSR04_Ultrasonice_Sensor/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/LCD_HD44780_Driver/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/HCSR04_Ultrasonice_Sensor/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/LCD_HD44780_Driver/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

