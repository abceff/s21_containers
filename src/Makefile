CC+FLAGS = g++ -std=c++17 -Wall -Werror -Wextra
OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -lm -pthread -lrt -lsubunit -g
else
	CHECK_FLAGS = -lgtest
endif

TEST_COMPILE = $(CC+FLAGS) tests.cpp $(CHECK_FLAGS)

all: clean s21_matrix_oop.a test

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM

rebuild: clean all

test:
	$(TEST_COMPILE)
	./a.out

s21_matrix_oop.o:
	$(CC+FLAGS) -c s21*.cpp

lo:
	for i in `seq 100 $(OP)`;	do ./a.out; done;

check:
	python3 ../materials/linters/cpplint.py --extensions=c *.cpp *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind ./a.out --leak-check=full
endif
	make clean
