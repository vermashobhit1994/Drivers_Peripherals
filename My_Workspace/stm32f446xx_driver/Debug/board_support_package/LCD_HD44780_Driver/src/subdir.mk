################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_I2C.c \
../board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_bsp.c 

OBJS += \
./board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_I2C.o \
./board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_bsp.o 

C_DEPS += \
./board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_I2C.d \
./board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_bsp.d 


# Each subdirectory must supply rules for building sources it contributes
board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_I2C.o: ../board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_I2C.c board_support_package/LCD_HD44780_Driver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/HCSR04_Ultrasonice_Sensor/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/LCD_HD44780_Driver/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_I2C.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_bsp.o: ../board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_bsp.c board_support_package/LCD_HD44780_Driver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/HCSR04_Ultrasonice_Sensor/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/LCD_HD44780_Driver/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"board_support_package/LCD_HD44780_Driver/src/LCD_HD44780_bsp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

