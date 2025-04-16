NAME = s21_decimal
CC = gcc
CFLAGS =-c -Wall -Wextra -Werror -pedantic -std=c11
OFLAGS=-Wall -Wextra -Werror -pedantic -std=c11
GCOVFLAGS=-fprofile-arcs -ftest-coverage
TESTS_FLAGS =-Wall -Wextra -Werror -std=c11 -lcheck -lsubunit -lrt -pthread -lm

SOURCE_DIR = .
CORE_DIR = ./core
TEST_DIR = ./tests
TESTS_SCRIPTS_DIR = ./tests/tests_scripts
TESTS_LOGS_DIR = ./tests/tests_logs
BUILD_DIR = ../build

TARGET_NAME = s21_decimal.a
TEST_NAME = unittest

COVERAGE_NAME = coverage.info

INCLUDE_FLAGS = -I$(SOURCE_DIR) 

SOURCES = $(shell find $(CORE_DIR) -type f -name "*.c" -not -path "$(TEST_DIR)/*")
TEST_SOURCES = $(shell find $(TEST_DIR) -type f -iname "*.c")
TEST_SOURCES = $(shell find $(TEST_DIR) \
    -type d \( \
        -path "*/tests_scripts" -o \
        -path "*/tests_logs" \
    \) -prune \
    -o \
    -type f -iname "*.c" \
    -print)

OBJECTS = $(patsubst $(CORE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SOURCES))

all: $(TARGET_NAME)

$(TARGET_NAME):  $(OBJECTS)
	ar -rs $@ $(OBJECTS)
	ranlib $(TARGET_NAME)

$(BUILD_DIR)/%.o: $(CORE_DIR)/%.c
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(shell pkg-config --cflags check) $< -o $@

test: install_dependence rebuild unittest
	./$(TEST_NAME)

leaks_test: unittest
	@bash ./scripts/leak_test.sh
	
unittest: $(TARGET_NAME)
	$(CC) tests/*.c $(TESTS_FLAGS) $(INCLUDE_FLAGS) -L. -l:s21_decimal.a -o unittest

gcov_report: clean install_dependence install_coverage_dependence  $(TEST_OBJECTS)
	$(CC) $(OFLAGS) $(GCOVFLAGS) $(INCLUDE_FLAGS) $(TEST_OBJECTS) $(SOURCES) $(shell pkg-config --libs check) -L . -o $(TEST_NAME)
	./$(TEST_NAME)
	lcov -t "gcov_report" -o $(COVERAGE_NAME) -c -d $(SOURCE_DIR) 
	genhtml -q -s -o ./report $(COVERAGE_NAME)

rebuild: clean s21_decimal.a

install_dependence:
	@bash ./scripts/install_pkg_config.sh
	@bash ./scripts/install_check.sh

install_coverage_dependence:
	bash ./scripts/install_gcov.sh

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(SOURCE_DIR)/$(TARGET_NAME)
	@rm -rf $(TEST_NAME)
	@rm -rf $(SOURCE_DIR)/report
	@rm -rf $(SOURCE_DIR)/$(COVERAGE_NAME)
	@find . -name '*.gcov' -delete
	@find . -name '*.gcda' -delete
	@find . -name '*.gcno' -delete
	
rebuild: clean all

style: 
	find $(SOURCE_DIR) -type f -name "*.[c,h]" -exec clang-format -n -style=Google {} +
	! find $(SOURCE_DIR) -type f -name "*.[c,h]" -exec grep -n '[А-Яа-яЁё]' {} +

style_fix:
	find $(SOURCE_DIR) -type f -name "*.[c,h]" -exec clang-format -i -style=Google {} +

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem -I $(SOURCE_DIR)

comments:
	find $(SOURCE_DIR) -type f -name "*.[c,h]" -exec grep -n '// ' {} +
