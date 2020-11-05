prog.out: main.o f.o teilor.o
	gcc $^ -o prog.out
main.o: main.c h.h
	gcc -c $<
f.o: f.c h.h
	gcc -c $<
teilor.o: teilor.c h.h
	gcc -c $<
