CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror 
#-g -O3
#CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -g -fsanitize=address

a.out: main.o v_tree.o student.o
	g++ -g $^ -o a.out
	#g++ -g $^ -fsanitize=address -o a.out
main.o: main.cpp v_tree.h
	g++  $< $(CFLASGS) 
student.o: student.cpp student.h
	g++ $< $(CFLASGS) 
v_tree.o: v_tree.cpp v_tree.h v_tree_node.h addition.h 
	g++ $< $(CFLASGS)
clean:
	rm -rf *.o *.out main?
