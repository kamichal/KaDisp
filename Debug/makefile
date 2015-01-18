################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /km/ti/ccsv5/tools/compiler/c5500_4.4.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./eZ_include/usbstk5515_led.obj" \
"./eZ_include/usbstk5515_i2c.obj" \
"./eZ_include/usbstk5515_gpio.obj" \
"./eZ_include/usbstk5515.obj" \
"./kadisp/ssd1780_oled_cntrl.obj" \
"./kadisp/kadisp_tests.obj" \
"./kadisp/kadisp.obj" \
"./kadisp/font_8x6_philippe.obj" \
"./src/main.obj" \
"./src/kairq.obj" \
"../C5515.cmd" \
-l/km/ti/c55xx_csl/build/C55XXCSL_LP.lib \
-l"rts55x.lib" \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include kadisp/subdir_vars.mk
-include eZ_include/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include kadisp/subdir_rules.mk
-include eZ_include/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: kadev.out

# Tool invocations
kadev.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C5500 Linker'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 -z -m"kadev.map" --stack_size=0x200 --heap_size=0x400 -i"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/lib" -i"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --reread_libs --display_error_number --warn_sections --xml_link_info="kadev_linkInfo.xml" --rom_model --sys_stacksize=0x200 -o "kadev.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C5500_EXECUTABLE_OUTPUTS__QUOTED) "kadev.out"
	-$(RM) "src/kairq.pp" "src/main.pp" "kadisp/font_8x6_philippe.pp" "kadisp/kadisp.pp" "kadisp/kadisp_tests.pp" "kadisp/ssd1780_oled_cntrl.pp" "eZ_include/usbstk5515.pp" "eZ_include/usbstk5515_gpio.pp" "eZ_include/usbstk5515_i2c.pp" "eZ_include/usbstk5515_led.pp" 
	-$(RM) "src/kairq.obj" "src/main.obj" "kadisp/font_8x6_philippe.obj" "kadisp/kadisp.obj" "kadisp/kadisp_tests.obj" "kadisp/ssd1780_oled_cntrl.obj" "eZ_include/usbstk5515.obj" "eZ_include/usbstk5515_gpio.obj" "eZ_include/usbstk5515_i2c.obj" "eZ_include/usbstk5515_led.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

