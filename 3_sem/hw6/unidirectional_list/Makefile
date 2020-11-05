CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -g -O3
#CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -g -fsanitize=address

a.out: main.o list.o student.o
	g++ -g $^ -o a.out
	#g++ -g $^ -fsanitize=address -o a.out
main.o: main.cpp list.h
	g++  $< $(CFLASGS)
list.o: list.cpp list.h list_node.h addition.h
	g++ $< $(CFLASGS)
student.o: student.cpp student.h
	g++ $< $(CFLASGS) 

clean:
	rm -rf *.o *.out
