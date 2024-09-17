CC = g++
FLAGS = -Wall -Wextra -Werror -g --std=c++17
GCOV = -coverage
UNAME := $(shell uname)

TEST_FLAGS=-lgtest -lpthread

TREE_DIR=s21_binary_tree
TEST_DIR = tests/

all: test

test : $(wildcard tests/*.cc)
	$(CC) $(FLAGS) $+ -o s21_$@ $(TEST_FLAGS)
	./s21_$@

gcov_report:FLAGS += $(GCOV)
gcov_report: clean test
	lcov -t "gcov_report" --no-external -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open ./report/index.html

valgrind: test
ifeq ($(UNAME), Linux)
	valgrind --leak-check=full  ./s21_test
else
	leaks --atExit  ./s21_test
endif

clean:
	rm -rf objects *.gcno *.gcda *.o *.info report s21_test ../s21_binary_tree/*.gch 
