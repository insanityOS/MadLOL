PROJECT_ROOT  = $(realpath ../../..)
MAKE_INC      = $(PROJECT_ROOT)/MakeInc
UUT           = MadLOL_string
TEST          = $(UUT)_tests
BUILD_DIR    := build

.DEFAULT_GOAL := test

include $(MAKE_INC)/unit_tests.mk
include $(MAKE_INC)/options.mk
include $(MAKE_INC)/default_goals.mk

$(BUILD_DIR)/$(TEST).elf: \
	$(BUILD_DIR)/$(UUT).o\
	$(BUILD_DIR)/$(TEST).o\
	$(MOCK_DIR)/MockMadLOL_char.h\
	$(BUILD_DIR)/MockMadLOL_char.o\
	$(BUILD_DIR)/unity.o\
	$(BUILD_DIR)/cmock.o

mocks:\
	$(MOCK_DIR)/MockMadLOL_char.h


$(MOCK_DIR)/MockMadLOL_char.h $(MOCK_DIR)/MockMadLOL_char.c: $(INC_DIR)/MadLOL_char.h

.PHONY: mocks
