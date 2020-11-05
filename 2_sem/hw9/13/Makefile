CFLAGS= -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -Werror
#CFLAGS= -c
prog.out: main.o solve.o norm.o matrix.o
	gcc $(CFLAGS) $^ -o  prog.out
main.o: main.c h.h
	gcc $(CFLAGS) -c -O3 $<
solve.o: solve.c h.h
	gcc $(CFLAGS) -c -O3 $<
norm.o: norm.c h.h
	gcc $(CFLAGS) -c -O3 $<
matrix.o: matrix.c h.h
	gcc $(CFLAGS) -c -O3 $<
