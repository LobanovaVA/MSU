#CFLAGS=-Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -Werror
prog.out: main.o solve.o matrix.o
	gcc  $^ -o prog.out
main.o: main.c h.h
	gcc  -c $<
solve.o: solve.c h.h
	gcc  -c $<
matrix.o: matrix.c h.h
	gcc  -c $<
