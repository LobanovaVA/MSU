CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror

a.out: main.o student.o sort.o addition.o
	g++ -g $^ -o a.out
student.o: student.cpp student.h addition.h
	g++ $< $(CFLASGS) 
sort.o: sort.cpp sort.h student.h
	g++ $< $(CFLASGS) 
addition.o: addition.cpp addition.h student.h
	g++ $< $(CFLASGS) 
clean:
	rm -rf *.o *.out
