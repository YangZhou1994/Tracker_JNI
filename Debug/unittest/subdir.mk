################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../unittest/main.cpp \
../unittest/read_conf.cpp 

OBJS += \
./unittest/main.o \
./unittest/read_conf.o 

CPP_DEPS += \
./unittest/main.d \
./unittest/read_conf.d 


# Each subdirectory must supply rules for building sources it contributes
unittest/%.o: ../unittest/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/lib/jvm/default-java/include/linux -I/usr/lib/jvm/default-java/include -I"/home/zy/workspace/Tracking_JNI/inc" -I"/home/zy/workspace/Tracking_JNI/lib" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


