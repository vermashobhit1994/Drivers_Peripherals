################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bootloader/Src/bootloader.c \
../Bootloader/Src/syscalls.c \
../Bootloader/Src/sysmem.c 

OBJS += \
./Bootloader/Src/bootloader.o \
./Bootloader/Src/syscalls.o \
./Bootloader/Src/sysmem.o 

C_DEPS += \
./Bootloader/Src/bootloader.d \
./Bootloader/Src/syscalls.d \
./Bootloader/Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Bootloader/Src/bootloader.o: ../Bootloader/Src/bootloader.c Bootloader/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/STM32F446RE_Driver_with_Bootloader/Bootloader/Inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/STM32F446RE_Driver_with_Bootloader/stm32f446xx_driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Bootloader/Src/bootloader.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Bootloader/Src/syscalls.o: ../Bootloader/Src/syscalls.c Bootloader/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/STM32F446RE_Driver_with_Bootloader/Bootloader/Inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/STM32F446RE_Driver_with_Bootloader/stm32f446xx_driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Bootloader/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Bootloader/Src/sysmem.o: ../Bootloader/Src/sysmem.c Bootloader/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/STM32F446RE_Driver_with_Bootloader/Bootloader/Inc" -I"/home/aayush/Shobhit_Verma_Practise/stmcubeide_workspace/STM32F446RE_Driver_with_Bootloader/stm32f446xx_driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Bootloader/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

