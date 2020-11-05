prog.out: main.o f.o test.o
	gcc $^ -o prog.out
main.o: main.c f.h test.h
	gcc -c $<
f.o: f.c f.h
	gcc -c $<
test.o: test.c test.h
	gcc -c $<
