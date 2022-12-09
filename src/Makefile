.PHONY: all clean test gcov_report linter cppcheck style_check
SHELL := /bin/bash

CC = g++
CFLAGS = -std=c++17 -lstdc++ -Wall -Werror -Wextra
EXTRAWARN_FLAGS = -Wpedantic -Wshadow -Wuninitialized 
DEBUG_FLAG = -g
GCOVFLAG = --coverage
LDFLAGS = -lgtest
TEST_SRCS = tests.cpp

OS := $(shell uname)
ifeq ($(OS), Linux)
LDFLAGS += -lgtest_main -lpthread
endif

ifeq ($(OS),Darwin)
BREW := ${HOME}/homebrew/brew/bin/brew
endif

all: clean test

clean:
	rm -rf *.o *.a *.gcno test ./report ./*.dSYM test.info *.out *.gcda gcov_report *.info
	rm -rf tests draw.dot
	@clear

test: clean
	$(CC) $(CFLAGS) $(TEST_SRCS) -I./ -L./ $(LDFLAGS) -o test 
	./test

gcov_report: clean
	$(CC) $(CFLAGS) $(GCOVFLAG) $(CFLAGS) $(TEST_SRCS) -I./ -L./ $(LDFLAGS) -o test
	./test
	lcov -t test -o test.info -c -d . --no-external
	genhtml test.info -o report

.IGNORE: linter
linter:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h
	rm -rf CPPLINT.cfg

cppcheck:
	cppcheck --enable=all --language=c++ --std=c++17 --suppress=missingIncludeSystem *.h *.cpp

style_check: linter cppcheck

debug:
	$(CC) $(CFLAGS) $(TEST_SRCS) $(LIB_NAME) -I./ -L./ $(LDFLAGS) -o debug.out -ggdb3

check: clean debug style_check
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./debug.out
else
	valgrind -q --tool=memcheck --leak-check=full --leak-resolution=med ./debug.out
endif
