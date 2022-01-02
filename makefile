CC = gcc
FLAGS= -Wall -g
all: graph
graph: new_graph.o
	$(CC) $(FLAGS) -o graph new_graph.o
new_graph.o: new_graph.c
	$(CC) $(FLAGS) -c new_graph.c
.PHONY: clean all
clean:
	rm -f *.o *.a graph
