BUILD_DIR ?= $(PROJECT_ROOT)/build
DIAG_DIR  = $(BUILD_DIR)/diagrams

# Diagram options
PUML_SRC   = *.puml
PUML      := plantuml
PUML_OPTS += -tsvg -o $(DIAG_DIR)

# Source path options
INC   += -I$(PROJECT_ROOT)/inc
VPATH += $(PROJECT_ROOT)/src

# Compiler options
CC       = gcc
OBJCOPY  = objcopy
GDB      = gdb
CFLAGS  += -Wall -Werror
LDFLAGS += -Wl,-Map=$*.map

# Common coverage options
LCOV_OPTS += --rc branch_coverage=1 
