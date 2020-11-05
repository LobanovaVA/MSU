CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -g -O3
#CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -g -fsanitize=address
all: main 

main: main.o tree.o tree_node.o
	g++ -g $^ -o main
main.o: main.cpp tree.h
	g++  $< $(CFLASGS) 
tree.o: tree.cpp tree.h tree_node.h
	g++ $< $(CFLASGS)
tree_node.o: tree_node.cpp tree_node.h addition.h 
	g++ $< $(CFLASGS)
clean:
	rm -rf *.o *.out main?
