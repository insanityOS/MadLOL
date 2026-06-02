PROJECT_ROOT := $(realpath ..)
MAKE_INC      = $(PROJECT_ROOT)/MakeInc

include $(MAKE_INC)/options.mk

all:
	mkdir -p $(DIAG_DIR)
	$(PUML) $(PUML_OPTS) $(PUML_SRC)

clean:
	rm -rf $(DIAG_DIR)
