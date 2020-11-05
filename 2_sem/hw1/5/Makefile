prog.out: main.o f.o edit.o
	gcc $^ -o prog.out
main.o: main.c f.h edit.h
	gcc -c $<
f.o: f.c f.h
	gcc -c $<
edit.o: edit.c edit.h
	gcc -c $<
