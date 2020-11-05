prog.out: main.o f.o slova.o
	gcc $^ -o prog.out
main.o: main.c f.h slova.h
	gcc -c $<
f.o: f.c f.h
	gcc -c $<
slova.o: slova.c slova.h
	gcc -c $<
