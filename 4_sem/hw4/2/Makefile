CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -O3
a.out: main.o command.o record.o list.o
	g++ -g $^ -o a.out
main.o: main.cpp
	g++ $< $(CFLASGS)
list.o: list.cpp
	g++ $< $(CFLASGS)
record.o: record.cpp
	g++ $< $(CFLASGS)
command.o: command.cpp
	g++ $< $(CFLASGS)
clean:
	rm -rf *.o *.out
