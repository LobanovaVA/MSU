CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -O3

a.out: main.o student.o
	g++ -g $^ -o a.out
main.o: main.cpp 
	g++ $< $(CFLASGS) 
student.o: student.cpp
	g++ $< $(CFLASGS) 
clean:
	rm -rf *.o *.out
