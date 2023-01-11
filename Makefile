############################################################################################################################
## MAKE SOURCE FILE                                                                                                       ##
############################################################################################################################
 # Project    : Serial Port
 # File Name  : Makefile
 # Author     : Dhanush.K (dhanushsandy98@gmail.com)
 # Date       : 30/11/2021
 # 
 # Revised on : 30/11/2021
 # Version    : V0.0.1
 # 
 # Brief      : Serial Port Communication (RS232) for UNIX envernment. 
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

# Application Name
APP = SERIAL_PORT

# Target files
TARGETS = \
Main.c \
src/serialPort.c

# Run time Auguments
RUN_ARUG = \
115200 \
/dev/ttyUSB0 \

# Macro Configuration Arguments
MARCO_ARUG = \
-D \
_DEFAULT_SOURCE

# Additinal Library Arguments
LIB_ARUG = \
-pthread \

# Compiler Options
CC_C = gcc

# Build Path
BUILD_PATH = ./build/

# Build Arguments
CFLAGS = -Wall -g -std=$(STD_VAR)
STD_VAR = c99

# Make commands
all: clean $(APP)

# Build Application
$(APP):
	@mkdir -p $(BUILD_PATH)
	$(CC_C) $(MARCO_ARUG) $(CFLAGS) $(TARGETS) -o $(BUILD_PATH)$(APP)_APP $(LIB_ARUG)

# Run the Application
run: all
	$(BUILD_PATH)$(APP)_APP $(RUN_ARUG)

# Clean Build
clean:
	rm -rf $(BUILD_PATH)*

############################################################################################################
##											End of File                                                   ##
############################################################################################################