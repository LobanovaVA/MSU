prog.out: main.o f.o read_array.o
	gcc $^ -o prog.out
main.o: main.c f.h 
	gcc -c $<
f.o: f.c f.h
	gcc -c $<
read_array.o: read_array.c f.h
	gcc -c $<
