CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -O3 -g

a.out: main.o student.o queue.o 
	g++ -g $^ -o a.out
main.o: main.cpp student.h addition.h queue.h queue_node.h
	g++ $< $(CFLASGS) 
student.o: student.cpp student.h addition.h
	g++ $< $(CFLASGS) 
queue.o: queue.cpp queue.h queue_node.h addition.h student.h
	g++ $< $(CFLASGS) 
clean:
	rm -rf *.o *.out
