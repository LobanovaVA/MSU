CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -O3 -g 

a.out: main.o
	g++ -g $^ -o a.out

main.o: main.cpp
	g++ $< $(CFLASGS)
	
clean:
	rm -rf *.o *.out
