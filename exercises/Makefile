CC = gcc

all: ex_strassen ex_chain_mult

ex_strassen:
	$(CC) strassen/main.c strassen/matrix.c strassen/strassen.c strassen/homework.c -o strassen_test

ex_chain_mult:
	$(CC) chain_mat_mult/main.c chain_mat_mult/matrix.c chain_mat_mult/chain_mm.c -o chain_mult

clean: 
	find . -type f -executable -exec rm '{}' \;

.PHONY: all clean