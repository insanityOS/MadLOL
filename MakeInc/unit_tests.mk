# Unit test Makefiles may include this at the end to define almost all goals and variables.
# In turn, the Makefile must define a few variables and targets. Specifically $(UUT) must be defined as the unit under
# test- that is, which source file is being tested. The test source must also be named according to the $(UUT)_tests.c
# convention. The ELF goal must be defined with the mock objects, the tests themselves, and the UUT. The tests must
# contain a definition to main() in addition to setUp() and tearDown() as required by Unity. See the Unity and CMock
# submodules for more information.
#
# The mock source must also be accordingly defined in the unit test Makefile according to the recipe below.

MAKE_INC         = $(PROJECT_ROOT)/MakeInc
LCOV_COLLECTION  = $(PROJECT_ROOT)/build/coverage
LCOV_BASE        = $(BUILD_DIR)/coverage_base.info
LCOV_TEST        = $(BUILD_DIR)/coverage_test.info
LCOV_EXCLUDES   += --exclude "*tests*" --exclude "*CMock*" --exclude "*Unity*" 
MOCK_DIR         = $(BUILD_DIR)/mocks
MOCK_RB          = $(PROJECT_ROOT)/CMock/lib/cmock.rb

INC             += -I$(PROJECT_ROOT)/Unity/src
INC             += -I$(PROJECT_ROOT)/CMock/src
INC             += -I$(MOCK_DIR)
VPATH           += $(PROJECT_ROOT)/Unity/src
VPATH           += $(PROJECT_ROOT)/CMock/src
VPATH           += $(MOCK_DIR)

CFLAGS          += -g --coverage 
LDFLAGS         += --coverage

test: $(BUILD_DIR)/$(TEST).elf
	@lcov --capture --initial --directory $(BUILD_DIR) --output-file $(LCOV_BASE) >/dev/null
	@printf "\e[31m\nExecuting $(TEST).elf\n\n\e[0m"
	@./build/$(TEST).elf

# This is the expected goal recipe that must be specified for each mock.
$(MOCK_DIR)/mock%.h $(MOCK_DIR)/mock%.c:
	@mkdir -p $(MOCK_DIR)
	@printf "\e[33mGenerating mock for $^\e[0m\n"
	@printf "require '$(MOCK_RB)'\nCMock.new(:plugins => [:ignore, :ignore_arg, :expect_any_args, :array, :callback, :return_thru_ptr], :mock_path => \"$(MOCK_DIR)\").setup_mocks([\"$<\"])\n" | ruby >/dev/null

lcov: test
	@mkdir -p $(LCOV_COLLECTION)
	@printf "\e[32mCollecting coverage data\e[0m\n"
	@lcov --capture $(LCOV_OPTS) --directory $(BUILD_DIR) --output-file $(LCOV_TEST) >/dev/null
	@lcov $(LCOV_OPTS) -a $(LCOV_BASE) -a $(LCOV_TEST) $(LCOV_EXCLUDES) --output-file $(LCOV_COLLECTION)/$(UUT)_coverage.info >/dev/null
