################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/GCC/_syscalls.c 

S_UPPER_SRCS += \
../CMSIS/GCC/startup_M451Series.S 

OBJS += \
./CMSIS/GCC/_syscalls.o \
./CMSIS/GCC/startup_M451Series.o 

S_UPPER_DEPS += \
./CMSIS/GCC/startup_M451Series.d 

C_DEPS += \
./CMSIS/GCC/_syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/GCC/%.o: ../CMSIS/GCC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/M451Series/Include" -I"../Library/StdDriver/inc" -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/M451Series/Include" -I"../Library/StdDriver/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/GCC/%.o: ../CMSIS/GCC/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -x assembler-with-cpp -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/M451Series/Include" -I"../Library/StdDriver/inc" -I"../Library/CMSIS/Include" -I"../Library/Device/Nuvoton/M451Series/Include" -I"../Library/StdDriver/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


