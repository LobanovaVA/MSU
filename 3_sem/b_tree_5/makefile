all: prog.exe

prog.exe: main.o student.o tree.o
	g++  main.o student.o tree.o -o a.out
main.o: main.cpp tree.h
	g++ -c -O3 main.cpp
student.o: student.cpp student.h
	g++ -c -O3 student.cpp
tree.o: tree.cpp tree.h
	g++ -c -O3 tree.cpp