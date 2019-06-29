CC = gcc
OPT = -O4

all: 01_strassen 02_chain_mult

01_strassen:
	$(CC) $(OPT) strassen/main.c strassen/matrix.c strassen/strassen.c strassen/homework.c -o strassen.x

02_chain_mult:
	$(CC) $(OPT) chain_mult/main.c chain_mult/matrix.c chain_mult/chain_mm.c -o chain_mult.x

clean: 
	@rm *.x

.PHONY: all clean