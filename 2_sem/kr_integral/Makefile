prog.out: main.o solve.o integral.o f.o
	gcc $^ -o prog.out
main.o: main.c h.h
	gcc -c $<
solve.o: solve.c h.h
	gcc -c $<
integral.o: integral.c h.h
	gcc -c $<
f.o: f.c h.h
	gcc -c $<
