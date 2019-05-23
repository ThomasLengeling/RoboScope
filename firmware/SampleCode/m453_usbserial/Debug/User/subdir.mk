################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/cdc_serial.c \
../User/descriptors.c \
../User/main.c 

OBJS += \
./User/cdc_serial.o \
./User/descriptors.o \
./User/main.o 

C_DEPS += \
./User/cdc_serial.d \
./User/descriptors.d \
./User/main.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/M451Series/Include" -I"../Library/StdDriver/inc" -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/M451Series/Include" -I"../Library/StdDriver/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


