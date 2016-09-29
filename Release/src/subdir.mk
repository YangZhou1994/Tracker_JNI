################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tracking.cpp \
../src/read_conf.cpp 

OBJS += \
./src/Tracking.o \
./src/read_conf.o 

CPP_DEPS += \
./src/Tracking.d \
./src/read_conf.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/lib/jvm/default-java/include/linux -I/usr/lib/jvm/default-java/include -I"/home/zy/workspace/Tracking_JNI/inc" -I"/home/zy/workspace/Tracking_JNI/lib" -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


