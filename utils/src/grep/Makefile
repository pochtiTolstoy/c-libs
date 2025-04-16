CC=gcc
FLAGS=-std=c11 -Wall -Wextra -Werror -g
PROJ=s21_grep

all: build

build: ${PROJ}

s21_grep: s21_grep.o
	${CC} s21_grep.o -o ${PROJ}

s21_grep.o: s21_grep.c
	${CC} -c s21_grep.c ${FLAGS} -o s21_grep.o

rebuild: clean build

clean: 
	rm -rf *.o ${PROJ}

test: build run_tests.sh
	./run_tests.sh
