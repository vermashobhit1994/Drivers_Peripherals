################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/delay.c \
../drivers/Src/stm32f446xx_spi_driver.c \
../drivers/Src/stm32f44xx_gpio_driver.c \
../drivers/Src/stm32f44xx_i2c_driver.c \
../drivers/Src/stm32f44xx_uart_driver.c 

OBJS += \
./drivers/Src/delay.o \
./drivers/Src/stm32f446xx_spi_driver.o \
./drivers/Src/stm32f44xx_gpio_driver.o \
./drivers/Src/stm32f44xx_i2c_driver.o \
./drivers/Src/stm32f44xx_uart_driver.o 

C_DEPS += \
./drivers/Src/delay.d \
./drivers/Src/stm32f446xx_spi_driver.d \
./drivers/Src/stm32f44xx_gpio_driver.d \
./drivers/Src/stm32f44xx_i2c_driver.d \
./drivers/Src/stm32f44xx_uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/delay.o: ../drivers/Src/delay.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/HCSR04_Ultrasonice_Sensor/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/LCD_HD44780_Driver/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/delay.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/Src/stm32f446xx_spi_driver.o: ../drivers/Src/stm32f446xx_spi_driver.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/HCSR04_Ultrasonice_Sensor/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/LCD_HD44780_Driver/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/stm32f446xx_spi_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/Src/stm32f44xx_gpio_driver.o: ../drivers/Src/stm32f44xx_gpio_driver.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/HCSR04_Ultrasonice_Sensor/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/LCD_HD44780_Driver/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/stm32f44xx_gpio_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/Src/stm32f44xx_i2c_driver.o: ../drivers/Src/stm32f44xx_i2c_driver.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/HCSR04_Ultrasonice_Sensor/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/LCD_HD44780_Driver/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/stm32f44xx_i2c_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/Src/stm32f44xx_uart_driver.o: ../drivers/Src/stm32f44xx_uart_driver.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/HCSR04_Ultrasonice_Sensor/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/board_support_package/LCD_HD44780_Driver/inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/stm32f446xx_driver/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/stm32f44xx_uart_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

