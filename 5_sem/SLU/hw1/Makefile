CFLASGS = -c -Wall -Wextra -pedantic -Werror -O3 -g
SHELL = /bin/sh

all: a.out

a.out: main.o func.o
	gcc -g $^ -o $@
main.o: main.c
	gcc $< $(CFLASGS) 
func.o: func.c
	gcc $< $(CFLASGS) 

clean:
	rm -rf *.o *.out 