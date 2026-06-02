PROJECT_ROOT  = $(realpath ../..)
MAKE_INC      = $(PROJECT_ROOT)/MakeInc
TARGET        = AxLOL_test
BUILD_DIR    := build
CFLAGS       += -g -O0

.DEFAULT_GOAL := test


include $(MAKE_INC)/options.mk
include $(MAKE_INC)/default_goals.mk

$(BUILD_DIR)/$(TARGET).elf:\
	$(BUILD_DIR)/$(TARGET).o\
	$(BUILD_DIR)/AxLOL_char.o\
	$(BUILD_DIR)/AxLOL_string.o\
	$(BUILD_DIR)/AxLOL_ref_setColor.o\
	$(BUILD_DIR)/AxLOL_primitive.o\
	$(BUILD_DIR)/AxLOL_bmp.o

test: $(BUILD_DIR)/$(TARGET).elf
	@rm -f test_image.bmp
	@printf "\e[31m\nExecuting $(TARGET).elf\n\n\e[0m"
	@./build/$(TARGET).elf
