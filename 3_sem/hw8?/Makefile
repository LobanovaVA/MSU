CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -O3
#CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -g -fsanitize=address

a.out: main.o b_tree.o student.o
	g++ -g $^ -o a.out
	#g++ -g $^ -fsanitize=address -o a.out
main.o: main.cpp b_tree.h
	g++  $< $(CFLASGS) 
student.o: student.cpp student.h
	g++ $< $(CFLASGS) 
b_tree.o: b_tree.cpp b_tree.h b_tree_node.h addition.h 
	g++ $< $(CFLASGS)
clean:
	rm -rf *.o *.out main?
