CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic  -O3

a.out: main.o operation.o parser.o
	g++ -g $^ -o a.out
main.o: main.cpp 
	g++ $< $(CFLASGS) 
operation.o: operation.cpp
	g++ $< $(CFLASGS) 
parser.o: parser.cpp
	g++ $< $(CFLASGS) 
clean:
	rm -rf *.o *.out
