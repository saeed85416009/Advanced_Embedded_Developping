################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/src/my_process.c 

OBJS += \
./include/src/my_process.o 

C_DEPS += \
./include/src/my_process.d 


# Each subdirectory must supply rules for building sources it contributes
include/src/%.o: ../include/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Users\Saeed\eclipse-workspace\Advanced-Embedded\include\inc" -O0 -g3 -Wall -c -fmessage-length=0  -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


