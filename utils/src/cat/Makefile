CC=gcc
FLAGS= -Wall -Werror -Wextra -std=c11 -g
PROJ=s21_cat

all: build

build: s21_cat

s21_cat: s21_cat.o
	${CC} s21_cat.o -o ${PROJ}

s21_cat.o: s21_cat.c
	${CC} -c s21_cat.c ${FLAGS} -o s21_cat.o

clean:
	rm -rf ${PROJ} *.o

rebuild: clean build

test: build run_tests.sh
	./run_tests.sh
