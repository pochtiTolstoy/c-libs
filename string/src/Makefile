NAME = s21_string
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
OS = $(shell uname)
ifeq ($(OS),Linux)
	TESTS_FLAGS = -lcheck -lsubunit -lrt -pthread -lm -w
else 
	TESTS_FLAGS = -lcheck
endif
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
SRCS = $(wildcard ./core/*.c ./core/s21_sprintf/*.c ./core/converter/*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
INCLUDE = s21_string.h

## Makefile help
help: 
	@awk 'BEGIN {FS = ":.*"} /^##/ {comment=substr($$0, 4); next} /^[a-zA-Z_-]+:/ {printf "\033[35m%-20s\033[33m ---> %s\n", $$1, comment; comment=""}' $(MAKEFILE_LIST)

## clean and build library s21_string.a 
all: clean s21_string.a

## run tests
test: s21_string.a
ifeq ($(OS),Linux)
	$(CC) $(CFLAGS) tests/*.c $(TESTS_FLAGS) -L. -l:s21_string.a -o run_tests.out
else
	make clean
	echo "$(TESTS_FLAGS)"
	$(CC) $(CFLAGS) tests/*.c $(TESTS_FLAGS) core/*.c -o run_tests.out
endif
	./run_tests.out

## report of tests in html and automaticly open 
gcov_report:  s21_string.a
ifeq ($(OS),Linux)
	$(CC) $(CFLAGS) $(SRCS) tests/*.c -L. -l:s21_string.a $(TESTS_FLAGS) $(GCOV_FLAGS) -o gcov.out
else
	$(CC) $(CFLAGS) $(SRCS) tests/*.c -L. s21_string.a $(TESTS_FLAGS) $(GCOV_FLAGS) -o gcov.out
endif
	./gcov.out
	lcov -t "Report" -c -d . --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/
	open ./report/index.html
	rm -rf *.gcno *.gcda *.info gcov.out *.dSYM

## build lib s21_string.a
lib: s21_string.a

## build lib s21_string.a
s21_string.a: $(OBJS) $(INCLUDE)
ifeq ($(OS),Linux)
	ar rcs s21_string.a $(OBJS)
	ranlib s21_string.a
	rm -rf *.o
else
	ar rcs libs21_string $(OBJS)
	mv libs21_string s21_string.a
	rm -rf *.o
endif

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o ./$@

## clean project from garbage
clean: 
	rm -rf *.o ./*/*.o ./*/*/*.o *.a ./*/*.a *.out ./*/*.out ./report/*
	rm -rf *.gcno *.gcda *.info gcov.out
	rm -rf *.dSYM

## clang-format check
check: 
	find ./ -iname '*.h' -o -iname '*.c' | xargs clang-format -style=Google -n

## make code beautiful

format: 
	find ./ -iname '*.h' -o -iname '*.c' | xargs clang-format -style=Google -i
## check leaks of test 
valgrind:
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./run_tests.out
