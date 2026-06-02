PROJECT_ROOT ?= $(realpath .)
DESIGN_DIR    = $(PROJECT_ROOT)/design
INC_PATH     += $(PROJECT_ROOT)/inc
PATH         += $(PROJECT_ROOT)/src

diagrams:
	make -C $(DESIGN_DIR)
