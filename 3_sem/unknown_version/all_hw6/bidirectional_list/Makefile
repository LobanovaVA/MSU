CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -g
#-g -O3
#CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -g -fsanitize=address

a.out: main.o bi_list.o student.o
	g++ -g $^ -o a.out
	#g++ -g $^ -fsanitize=address -o a.out
main.o: main.cpp bi_list.h
	g++  $< $(CFLASGS)
bi_list.o: bi_list.cpp bi_list.h bi_list_node.h addition.h
	g++ $< $(CFLASGS)
student.o: student.cpp student.h
	g++ $< $(CFLASGS) 

clean:
	rm -rf *.o *.out
