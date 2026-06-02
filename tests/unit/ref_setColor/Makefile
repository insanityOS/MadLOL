PROJECT_ROOT  = $(realpath ../../..)
MAKE_INC      = $(PROJECT_ROOT)/MakeInc
UUT           = AxLOL_ref_setColor
TEST          = $(UUT)_tests
BUILD_DIR    := build

.DEFAULT_GOAL := test

$(BUILD_DIR)/$(TEST).elf: \
	$(BUILD_DIR)/$(UUT).o\
	$(BUILD_DIR)/$(TEST).o\
	$(BUILD_DIR)/unity.o\
	$(BUILD_DIR)/cmock.o

include $(MAKE_INC)/unit_tests.mk
include $(MAKE_INC)/options.mk
include $(MAKE_INC)/default_goals.mk

mocks:
