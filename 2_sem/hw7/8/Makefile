prog.out: main.o solve.o matrix.o
	gcc $^ -o prog.out
main.o: main.c h.h
	gcc -c $<
solve.o: solve.c h.h
	gcc -c $<
matrix.o: matrix.c h.h
	gcc -c $<
