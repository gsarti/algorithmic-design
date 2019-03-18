CC = gcc

strassen:
	$(CC) 02_matrix_multiplication/main.c 02_matrix_multiplication/matrix.c 02_matrix_multiplication/strassen.c 02_matrix_multiplication/homework.c -o strassen_test

chain_mult:
	$(CC) 03_chain_matrix_multiplication/homework.c -o chain_mult

all: strassen chain_mult

clean: 
	find . -type f -executable -exec rm '{}' \;