BUILD_DIR  = $(PROJECT_ROOT)/build
DIAG_DIR   = $(BUILD_DIR)/diagrams

# Diagram options
PUML_SRC   = *.puml
PUML      := plantuml
PUML_OPTS += -tsvg -o $(DIAG_DIR)
