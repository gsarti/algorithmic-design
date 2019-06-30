CC = gcc
OPT = -O4

all: strassen chain_mult

strassen:
	$(CC) $(OPT) 01_strassen/main.c 01_strassen/strassen.c 01_strassen/homework.c utility.c -o strassen.x

chain_mult:
	$(CC) $(OPT) 02_chain_mult/main.c 02_chain_mult/chain_mm.c utility.c -o chain_mult.x

clean: 
	@rm *.x

.PHONY: all clean