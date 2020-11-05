prog.out: main.o f.o prob.o
	gcc $^ -o prog.out
main.o: main.c f.h prob.h
	gcc -c $<
f.o: f.c f.h
	gcc -c $<
prob.o: prob.c prob.h
	gcc -c $<
