# Compiler and flags
CC = gcc
AR = ar
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic -I. -lm
ARFLAGS = rcs
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
ASAN_FLAGS = -fsanitize=address,undefined,leak,unreachable
CHECK_FLAGS = $(shell pkg-config --libs check)

# Build directories
BUILD_DIR = ../build
RELEASE_DIR = $(BUILD_DIR)/release
DEBUG_DIR = $(BUILD_DIR)/debug
TEST_DIR = $(BUILD_DIR)/test
COVERAGE_DIR = $(BUILD_DIR)/coverage
REPORT_HTML = $(COVERAGE_DIR)/report/index.html

# Root dir
ROOT_DIR = .

# Source files
SRC_DIR = core
SRCS = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c, $(RELEASE_DIR)/obj/%.o, $(SRCS))

# Test files
TEST_SRC_DIR = tests
TEST_SRCS = $(shell find $(TEST_SRC_DIR) -type f -name '*.c')
TEST_OBJS = $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_DIR)/%.o, $(TEST_SRCS))

# Targets
TARGET = s21_matrix
TEST_TARGET = unittests
TEST_DEBUG_TARGET = unittests_gdb

.PHONY: all debug test gcov_report clean

# Default target - build static library
all: $(TARGET)

$(TARGET): $(RELEASE_DIR)/$(TARGET)

# $(RELEASE_DIR)/$(TARGET): $(OBJS)
# 	@mkdir -p $(@D)
# 	$(AR) $(ARFLAGS) $(TARGET) $^
# 	@echo "[INFO] Static library built: $(ROOT_DIR)/$(TARGET)"
$(RELEASE_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $(TARGET)
	@echo "[INFO] program was built: $(ROOT_DIR)/$(TARGET)"

$(RELEASE_DIR)/obj/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build - tests with sanitizers
debug: CFLAGS += -g -O0 $(ASAN_FLAGS)
debug: LDFLAGS += $(ASAN_FLAGS) 
debug: clean $(DEBUG_DIR)/$(TEST_DEBUG_TARGET)

$(DEBUG_DIR)/$(TEST_DEBUG_TARGET): $(TEST_OBJS) $(ROOT_DIR)/$(TARGET)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(CHECK_FLAGS) -o $(ROOT_DIR)/$(TEST_DEBUG_TARGET)
	@echo "[INFO] Debug tests built: $(ROOT_DIR)/$(TEST_DEBUG_TARGET)"
	ASAN_OPTIONS=allocator_may_return_null=1 ./$(TEST_DEBUG_TARGET)

# Regular tests build
$(ROOT_DIR)/$(TEST_TARGET): $(TEST_DIR)/$(TEST_TARGET)
test: clean $(TEST_DIR)/$(TEST_TARGET)
	./$(TEST_TARGET)

$(ROOT_DIR)/$(TEST_TARGET): $(TEST_DIR)/$(TEST_TARGET)
$(TEST_TARGET): $(TEST_DIR)/$(TEST_TARGET)

$(TEST_DIR)/$(TEST_TARGET): $(TEST_OBJS) $(ROOT_DIR)/$(TARGET)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(CHECK_FLAGS) -o $(ROOT_DIR)/$(TEST_TARGET)
	@echo "[INFO] Tests built: $(ROOT_DIR)/$(TEST_TARGET)"

# Coverage report
gcov_report: CFLAGS += $(GCOV_FLAGS)
gcov_report: LDFLAGS += $(GCOV_FLAGS)
gcov_report: clean $(COVERAGE_DIR)/$(TEST_TARGET)
	@$(COVERAGE_DIR)/$(TEST_TARGET)
	@lcov --capture --directory $(COVERAGE_DIR) --output-file coverage.info
	@genhtml coverage.info --output-directory $(COVERAGE_DIR)/report
	@echo "[INFO] Coverage report: file:$(abspath $(COVERAGE_DIR)/report/index.html)"
	@echo "[INFO] Run make open_gcov_report to open index.html"
	@rm -f coverage.info
	@mv $(COVERAGE_DIR)/$(TEST_TARGET) $(ROOT_DIR)/$(TEST_TARGET)

$(COVERAGE_DIR)/$(TEST_TARGET): $(TEST_OBJS) $(SRCS)
	@mkdir -p $(@D)
		$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_OBJS) $(SRCS) $(LDFLAGS) $(CHECK_FLAGS) -o $@

# Common build rules
$(TEST_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR) *.gcda *.gcno coverage.info $(TARGET) a.out unittests* main
	@echo "[INFO] Build files cleaned"

link: main.c $(TARGET)
	@echo "[INFO] Link $(TARGET) with simple main.c and run it."
	@gcc main.c -L. -l:s21_matrix.a -o main
	@./main

open_gcov_report:
ifneq ($(wildcard $(REPORT_HTML)), )
		@echo "[INFO] Open $(REPORT_HTML)"
		@open $(REPORT_HTML)
else
		@echo "[ERROR] File $(REPORT_HTML) doesn't exist"
		@echo "[INFO] Run make gcov_report to generate code coverage report"
endif

valgrind: clean $(ROOT_DIR)/$(TEST_TARGET)
	@if [ "$(shell uname)" = "Linux" ]; then \
		valgrind --tool=memcheck --leak-check=yes ./$(ROOT_DIR)/$(TEST_TARGET); \
	elif [ "$(shell uname)" = "Darwin" ]; then \
		leaks -atExit -- ./$(ROOT_DIR)/$(TEST_TARGET); \
	fi

rebuild: clean all

style: 
	find $(ROOT_DIR) -type f -name "*.[c,h]" -exec clang-format -n -style=Google {} +
	! find $(ROOT_DIR) -type f -name "*.[c,h]" -exec grep -n '[А-Яа-яЁё]' {} +

style_fix: 
	find $(ROOT_DIR) -type f -name "*.[c,h]" -exec clang-format -i -style=Google {} +

comments:
	find $(SOURCE_DIR) -type f -name "*.[c,h]" -exec grep -n '//\|\/\*' {} +
