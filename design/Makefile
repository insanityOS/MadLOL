PROJECT_ROOT := $(realpath ..)
MAKE_INC      = $(PROJECT_ROOT)/MakeInc

include $(MAKE_INC)/options.mk

all:
	@mkdir -p $(DIAG_DIR)
	@printf "\e[33m$(PUML) $(PUML_OPTS) $(PUML_SRC)\e[0m\n"
	@$(PUML) $(PUML_OPTS) $(PUML_SRC)

clean:
	rm -rf $(DIAG_DIR)
