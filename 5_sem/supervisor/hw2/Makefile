CFLASGS = -c -Wall -Wextra -pedantic -Werror -O3 -g 
SHELL = /bin/sh

FUNC = func.o sub_func.o

all: 1.out 2.out 3.out 4.out 5.out 6.out 7.out 8.out 9.out

# Functions
func.o: func.c 
	gcc $< $(CFLASGS) 
sub_func.o: sub_func.c
	gcc $< $(CFLASGS) 

# Main
1.out: main1.o $(FUNC)
	gcc -g $^ -o $@
main1.o: main1.c
	gcc $< $(CFLASGS) 

2.out: main2.o $(FUNC)
	gcc -g $^ -o $@
main2.o: main2.c
	gcc $< $(CFLASGS) 

3.out: main3.o $(FUNC)
	gcc -g $^ -o $@
main3.o: main3.c
	gcc $< $(CFLASGS) 

4.out: main4.o $(FUNC)
	gcc -g $^ -o $@
main4.o: main4.c
	gcc $< $(CFLASGS) 

5.out: main5.o $(FUNC)
	gcc -g $^ -o $@
main5.o: main5.c
	gcc $< $(CFLASGS) 

6.out: main6.o $(FUNC)
	gcc -g $^ -o $@
main6.o: main6.c
	gcc $< $(CFLASGS) 

7.out: main7.o $(FUNC)
	gcc -g $^ -o $@
main7.o: main7.c
	gcc $< $(CFLASGS) 

8.out: main8.o $(FUNC)
	gcc -g $^ -o $@
main8.o: main8.c
	gcc $< $(CFLASGS) 

9.out: main9.o $(FUNC)
	gcc -g $^ -o $@
main9.o: main9.c
	gcc $< $(CFLASGS)


clean:
	rm -rf *.o *.out 