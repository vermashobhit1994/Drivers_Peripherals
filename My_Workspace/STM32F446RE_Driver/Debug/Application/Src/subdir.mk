################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Src/LED_ON_SOME_TIME_Btn_Press.c \
../Application/Src/main.c \
../Application/Src/syscalls.c \
../Application/Src/sysmem.c 

OBJS += \
./Application/Src/LED_ON_SOME_TIME_Btn_Press.o \
./Application/Src/main.o \
./Application/Src/syscalls.o \
./Application/Src/sysmem.o 

C_DEPS += \
./Application/Src/LED_ON_SOME_TIME_Btn_Press.d \
./Application/Src/main.d \
./Application/Src/syscalls.d \
./Application/Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Src/LED_ON_SOME_TIME_Btn_Press.o: ../Application/Src/LED_ON_SOME_TIME_Btn_Press.c Application/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/Src/LED_ON_SOME_TIME_Btn_Press.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/Src/main.o: ../Application/Src/main.c Application/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/Src/syscalls.o: ../Application/Src/syscalls.c Application/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/Src/sysmem.o: ../Application/Src/sysmem.c Application/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

