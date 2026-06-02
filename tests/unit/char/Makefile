PROJECT_ROOT  = $(realpath ../../..)
MAKE_INC      = $(PROJECT_ROOT)/MakeInc
UUT           = AxLOL_char
TEST          = $(UUT)_tests
BUILD_DIR    := build

.DEFAULT_GOAL := test

include $(MAKE_INC)/unit_tests.mk
include $(MAKE_INC)/options.mk
include $(MAKE_INC)/default_goals.mk

$(BUILD_DIR)/$(TEST).elf: \
	$(BUILD_DIR)/$(UUT).o\
	$(BUILD_DIR)/$(TEST).o\
	$(MOCK_DIR)/MockAxLOL_primitive.h\
	$(BUILD_DIR)/MockAxLOL_primitive.o\
	$(BUILD_DIR)/unity.o\
	$(BUILD_DIR)/cmock.o

mocks:\
	$(MOCK_DIR)/MockAxLOL_primitive.h


$(MOCK_DIR)/MockAxLOL_primitive.h $(MOCK_DIR)/MockAxLOL_primitive.c: $(INC_DIR)/AxLOL_primitive.h

.PHONY: mocks
