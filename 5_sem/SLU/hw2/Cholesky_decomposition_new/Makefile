CFLASGS = -c -Wall -Wextra -pedantic -Werror -O3 -g -pg
SHELL = /bin/sh

all: a.out

a.out: main.o solve.o in_out.o norm.o matr_operation.o block_action.o
	g++ -g -pg $^ -o $@
main.o: main.cpp solve.h
	g++ $< $(CFLASGS) 
solve.o: solve.cpp solve.h in_out.h norm.h block_action.h matr_operation.h addition.h
	g++ $< $(CFLASGS) 
matr_operation.o: matr_operation.cpp matr_operation.h addition.h
	g++ $< $(CFLASGS) 
block_action.o: block_action.cpp block_action.h addition.h
	g++ $< $(CFLASGS) 
norm.o: norm.cpp norm.h addition.h
	g++ $< $(CFLASGS)	
in_out.o: in_out.cpp in_out.h addition.h
	g++ $< $(CFLASGS)

clean:
	rm -rf *.o *.out 
