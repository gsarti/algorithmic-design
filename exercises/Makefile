CC = gcc
C++ = g++
OPT = -O4

all: strassen chain_mult sorting heap dijkstra

strassen:
	$(CC) $(OPT) 01_strassen/main.c 01_strassen/strassen.c 01_strassen/homework.c utility.c -o strassen.x

chain_mult:
	$(CC) $(OPT) 02_chain_mult/main.c 02_chain_mult/chain_mm.c utility.c -o chain_mult.x

sorting:
	$(CC) $(OPT) 03_sorting/main_compare.c 03_sorting/sorting.c 03_sorting/vector.c 04_heap/heap.c utility.c -o compare.x
	$(CC) $(OPT) 03_sorting/main_edge_cases.c 03_sorting/sorting.c 03_sorting/vector.c 04_heap/heap.c utility.c -o edge_cases.x
	$(CC) $(OPT) 03_sorting/main_selection.c 03_sorting/sorting.c 03_sorting/vector.c 04_heap/heap.c utility.c -o selection.x

heap:
	$(CC) $(OPT) 04_heap/main.c 04_heap/heap.c utility.c -o heap.x

dijkstra:
	$(C++) $(OPT) 05_dijkstra/main.cpp 05_dijkstra/utility.cpp 05_dijkstra/heap.hpp 05_dijkstra/graph.cpp 05_dijkstra/dijkstra.cpp -o dijkstra.x

clean: 
	@rm *.x

.PHONY: all clean