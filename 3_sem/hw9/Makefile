CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -O3

a.out: main.o queue.o list.o tree.o student.o
	g++ -g $^ -o a.out
main.o: main.cpp student.h addition.h queue.h queue_node.h
	g++ $< $(CFLASGS) 
student.o: student.cpp student.h addition.h
	g++ $< $(CFLASGS) 
queue.o: queue.cpp queue.h queue_node.h addition.h list.h
	g++ $< $(CFLASGS) 
list.o: list.cpp list.h list_node.h addition.h tree.h
	g++ $< $(CFLASGS) 
tree.o: tree.cpp tree.h tree_node.h addition.h student.h
	g++ $< $(CFLASGS) 
clean:
	rm -rf *.o *.out
