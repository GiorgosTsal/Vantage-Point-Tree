################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp \
../src/vptree_cilk.cpp \
../src/vptree_openmp.cpp \
../src/vptree_sequential.cpp 

OBJS += \
./src/main.o \
./src/vptree_cilk.o \
./src/vptree_openmp.o \
./src/vptree_sequential.o 

CPP_DEPS += \
./src/main.d \
./src/vptree_cilk.d \
./src/vptree_openmp.d \
./src/vptree_sequential.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


