all: item.o lista.o caixeiro.o
	gcc -Wall -std=c99 item.o lista.o caixeiro.o -o caixeiro

item.o:
	gcc -c item.c

lista.o:
	gcc -c lista.c 

caixeiro.o:
	gcc -c caixeiro.c

clear:
	rm *.o caixeiro

run:
	./caixeiro  