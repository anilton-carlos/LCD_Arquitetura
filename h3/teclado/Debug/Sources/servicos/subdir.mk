################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/servicos/Cozimento.cpp \
../Sources/servicos/EditService.cpp \
../Sources/servicos/IncrementService.cpp 

OBJS += \
./Sources/servicos/Cozimento.o \
./Sources/servicos/EditService.o \
./Sources/servicos/IncrementService.o 

CPP_DEPS += \
./Sources/servicos/Cozimento.d \
./Sources/servicos/EditService.d \
./Sources/servicos/IncrementService.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/servicos/%.o: ../Sources/servicos/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


