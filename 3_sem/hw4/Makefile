CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -O3
#CFLASGS = -c -std=c++14 -Wall -Wextra -pedantic -Werror -g -fsanitize=address

#a.out: main.o student.o list.o 
	#g++ -g $^ -o a.out
	#g++ -g $^ -fsanitize=address -o a.out

all: main1 main2 main5 main3 main4

main1: main1.o tree.o student.o
	g++ -g $^ -o main1
main1.o: main1.cpp tree.h
	g++  $< $(CFLASGS) 
	
main2: main2.o tree.o student.o
	g++ -g $^ -o main2
main2.o: main2.cpp tree.h
	g++  $< $(CFLASGS) 
	
main3: main3.o tree.o student.o
	g++ -g $^ -o main3
main3.o: main3.cpp tree.h
	g++  $< $(CFLASGS) 
	
main4: main4.o tree.o student.o
	g++ -g $^ -o main4
main4.o: main4.cpp tree.h
	g++  $< $(CFLASGS) 	

main5: main5.o tree.o student.o
	g++ -g $^ -o main5
main5.o: main5.cpp tree.h
	g++  $< $(CFLASGS) 
	

student.o: student.cpp student.h
	g++ $< $(CFLASGS) 
tree.o: tree.cpp tree.h tree_node.h addition.h 
	g++ $< $(CFLASGS)
clean:
	rm -rf *.o *.out main?
