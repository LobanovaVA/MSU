CFLASGS = -c -std=c++14 -O3 -g -DZACHET
WARNINGS = -Wall -Wextra -pedantic -Werror

all: server client

server: main.o server.o Printf_Readf.o command.o record.o data_base.o list.o avl_tree.o group_avl_tree_node.o group_avl_tree.o
	g++ -g $^ -o server
server.o: server.cpp
	g++ $< $(CFLASGS) $(WARNINGS)
main.o: main.cpp
	g++ $< $(CFLASGS) $(WARNINGS)
data_base.o: data_base.cpp
	g++ $< $(CFLASGS) $(WARNINGS)
group_avl_tree.o: group_avl_tree.cpp
	g++ $< $(CFLASGS) $(WARNINGS)
group_avl_tree_node.o: group_avl_tree_node.cpp
	g++ $< $(CFLASGS) $(WARNINGS)
avl_tree.o: avl_tree.cpp
	g++ $< $(CFLASGS) $(WARNINGS)
list.o: list.cpp
	g++ $< $(CFLASGS) $(WARNINGS)
command.o: command.cpp
	g++ $< $(CFLASGS) $(WARNINGS)
record.o: record.cpp
	g++ $< $(CFLASGS) $(WARNINGS)

client: client.o Printf_Readf.o
	g++ -g $^ -o client
client.o: client.cpp
	g++ $< $(CFLASGS) $(WARNINGS)

Printf_Readf.o: Printf_Readf.cpp
	g++ $< $(CFLASGS) $(WARNINGS)

clean:
	rm -rf *.o *.out client server
