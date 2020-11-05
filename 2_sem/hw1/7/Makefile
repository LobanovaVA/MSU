prog.out: main.o f.o 
	gcc $^ -o prog.out
main.o: main.c f.h
	gcc -c $<
f.o: f.c f.h
	gcc -c $<