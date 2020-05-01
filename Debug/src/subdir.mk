################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Advanced-Embedded.c 

OBJS += \
./src/Advanced-Embedded.o 

C_DEPS += \
./src/Advanced-Embedded.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Users\Saeed\eclipse-workspace\Advanced-Embedded\include\inc" -I"D:\Users\Saeed\eclipse-workspace\Advanced-Embedded\src" -O0 -g3 -Wall -c -fmessage-length=0  -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


