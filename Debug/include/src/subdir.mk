################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/src/my_database.c \
../include/src/my_linkedList.c \
../include/src/my_process.c \
../include/src/my_socket.c \
../include/src/my_usb.c \
../include/src/test.c 

OBJS += \
./include/src/my_database.o \
./include/src/my_linkedList.o \
./include/src/my_process.o \
./include/src/my_socket.o \
./include/src/my_usb.o \
./include/src/test.o 

C_DEPS += \
./include/src/my_database.d \
./include/src/my_linkedList.d \
./include/src/my_process.d \
./include/src/my_socket.d \
./include/src/my_usb.d \
./include/src/test.d 


# Each subdirectory must supply rules for building sources it contributes
include/src/%.o: ../include/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Users\Saeed\eclipse-workspace\Advanced-Embedded\include\inc" -I"D:\Users\Saeed\eclipse-workspace\Advanced-Embedded\src" -O0 -g3 -Wall -c -fmessage-length=0  -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


