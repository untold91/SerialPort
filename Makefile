############################################################################################################################
##												MAKE SOURCE FILE														  ##
############################################################################################################################
 # Project    : Serial Port
 # File Name  : Makefile
 # Author     : Dhanush.K (dhanushsandy91@gmail.com)
 # Date       : 30/11/2021
 # 
 # Revised on : 22/01/2023
 # Version    : V0.0.1
 # 
 # Brief      : 
 #              Build		: ~$ make (or) make	all
 #				Build & Run	: ~$ make run
 #				Clean		: ~$ make clean
 # 
 # Reference  : 
 # 
 ##
############################################################################################################################
 # Licence    : MIT
 # Copyright (c) 2021 Dhanush.K
 ##
############################################################################################################################

# Project Directory
PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# Project Name
PROJECT_NAME = Serial Port

# Application Name
APP = serialPort

# Project files
C_MAIN  += Main.c

C_FILES += src/serialPort.c

H_FILES +=

# Load Library, Shared/Dynamic Library, ".so" file.
LDLIBS += -lpthread

# Linker Flags, Static Library, ".a" file.
LDFLAGS +=

# Feature Test Macros Arguments,
MARCO_ARUG += -D_GNU_SOURCE

# Run time Auguments
RUN_ARUG +=

############################################################################################################################
 # >>> WARNING <<<
 # - Do not change anything from here.
 ##
############################################################################################################################
 # Default Variables
############################################################################################################################

# Compiler Options
CC_C = gcc
# CC_x86_32 =
# CC_x64_64 =
# CC_ARM_32 =
# CC_ARM_64 =

# Build Directory
BUILD_DIR = ./build

# Objects Directory
OBJ_DIR = $(BUILD_DIR)/obj

# Local install path
INSTALL_PATH =

# Local installation script
INSTALL_SCRIPT =

# Object Files
OBJECTS 		:= $(addprefix $(OBJ_DIR)/default/, $(C_FILES:%.c=%.o))
# OBJECTS_x86_32 	:= $(addprefix $(OBJ_DIR)/x86_32/, 	$(C_FILES:%.c=%.o))
# OBJECTS_x86_64 	:= $(addprefix $(OBJ_DIR)/x86_64/, 	$(C_FILES:%.c=%.o))
# OBJECTS_ARM_32 	:= $(addprefix $(OBJ_DIR)/arm_32/, 	$(C_FILES:%.c=%.o))
# OBJECTS_ARM_64 	:= $(addprefix $(OBJ_DIR)/arm_64/, 	$(C_FILES:%.c=%.o))

# C Standards
STD_VAR = c11

# Build Arguments
CFLAGS += -Wall
CFLAGS += -std=$(STD_VAR)
# CFLAGS += -O3

############################################################################################################################
 # >>> WARNING <<<
 # - Enable the below flag only in the final Release.
 ##
############################################################################################################################
ifeq ($(BUILD_TYP), RELEASE)
CFLAGS += -fno-stack-protector # Stack Protector, to overcome "Stack Smashed" issue.
endif

############################################################################################################################
 # Makefile Targets
############################################################################################################################

# Main Build target
target: start $(APP) end

# Build for all cross compiler targets
# all: start $(APP) end

start:
	@echo "Building $(APP)..."

end:
	@echo "Build Finish.!"

# Default build traget
$(APP): $(BUILD_DIR)/$(APP)

$(BUILD_DIR)/$(APP): $(C_MAIN) $(OBJECTS) $(H_FILES)
	@echo "\n---> Default <---\n"
	$(CC_C) $(MARCO_ARUG) $(CFLAGS) -g $(C_MAIN) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/default/%.o: %.c %.h $(H_FILES)
	@mkdir -p $(@D)
	$(CC_C) $(MARCO_ARUG) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

# Build traget x86_32 compiler.

# Build traget x64_64 compiler.

# Build traget ARM_32 compiler.

# Build traget ARM_64 compiler.

# Run the application
run: target
	@echo "\nRunning the $(APP)"
	$(BUILD_DIR)/$(APP) $(RUN_ARUG)
	@echo "\nThank you..!\n"

# Clean build folder
clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: clean run

############################################################################################################################
##														End of File														  ##
############################################################################################################################
