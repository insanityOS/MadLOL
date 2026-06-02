PROJECT_ROOT ?= $(realpath .)
DESIGN_DIR    = $(PROJECT_ROOT)/design
TESTS        := $(shell dirname $(shell find tests/unit -mindepth 2 -name Makefile))

FORMAT_DIRS   = ./src/ ./inc/ ./tests/
FORMAT_PAT    = -iname "*.h" -o -iname "*.c"

include $(PROJECT_ROOT)/MakeInc/options.mk

tests:
	@$(foreach test, $(TESTS), make -C $(test) || exit $?;)
	@printf "\e[5m\e[90;103mTESTS COMPLETE\e[0m\n"

lcov: 
	@mkdir -p build/lcov
	@touch ./build/all_test_coverage.info
	@$(foreach test, $(TESTS), printf "\e[35mCollecting coverage data for $(test)\e[0m\n"; make -C $(test) lcov || exit $?;)
	@lcov --ignore-errors empty --rc branch_coverage=1 -a build/coverage/\* -o ./build/all_test_coverage.info >/dev/null
	@genhtml ./build/all_test_coverage.info --branch-coverage --output-directory build/lcov
	@printf "\e[5m\e[34m\e[22mYOUR COVERAGE IS READY, SIR\e[0m\a\n"


diagrams:
	@make -C $(DESIGN_DIR)

format:
	@find $(FORMAT_DIRS) $(FORMAT_PAT) | xargs clang-format -i --style=file:.clang-format

check-format:
	@find $(FORMAT_DIRS) $(FORMAT_PAT) | xargs clang-format --dry-run -Werror --style=file:.clang-format

clean:
	@$(foreach test, $(TESTS), make -C $(test) clean || exit $?;)
	rm -rf build

.PHONY: tests
