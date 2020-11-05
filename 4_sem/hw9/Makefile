CFLASGS = -c -std=c++14 -O3 -g -DZACHET
WARNINGS = -Wall -Wextra -pedantic -Werror


a.out: main.o command.o record.o data_base.o list.o avl_tree.o group_avl_tree_node.o group_avl_tree.o
	g++ -g $^ -o a.out
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
clean:
	rm -rf *.o *.out
