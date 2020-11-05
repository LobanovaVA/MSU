CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror

a.out: main.o solve.o student.o list.o 
	g++ -g $^ -o a.out
main.o: main.cpp student.h addition.h list.h list_node.h
	g++ $< $(CFLASGS) 
student.o: student.cpp student.h addition.h
	g++ $< $(CFLASGS) 
solve.o: solve.cpp student.h addition.h list.h list_node.h
	g++ $< $(CFLASGS) 
list.o: list.cpp list.h list_node.h addition.h student.h
	g++ $< $(CFLASGS) 
clean:
	rm -rf *.o *.out
