CFLAGS= -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -Werror -lm'
prog.out: main.o solve.o matrix.o
	gcc -$(CFLAGS) $^ -o prog.out
main.o: main.c h.h
	gcc -$(CFLAGS) $<
solve.o: solve.c h.h
	gcc -$(CFLAGS) $<
matrix.o: matrix.c h.h
	gcc -$(CFLAGS) $<
