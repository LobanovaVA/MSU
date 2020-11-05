CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -O3 -g 
a.out: main.o command.o record.o data_base.o list.o avl_tree.o
	g++ -g $^ -o a.out
main.o: main.cpp
	g++ $< $(CFLASGS)
data_base.o: data_base.cpp
	g++ $< $(CFLASGS)
list.o: list.cpp
	g++ $< $(CFLASGS)
avl_tree.o: avl_tree.cpp
	g++ $< $(CFLASGS)
record.o: record.cpp
	g++ $< $(CFLASGS)
command.o: command.cpp
	g++ $< $(CFLASGS)
clean:
	rm -rf *.o *.out
