all: aresta.o lista.o caminho.o main.o
	gcc aresta.o lista.o caminho.o main.o -o main
aresta.o:
	gcc aresta.c -Wall -std=c99 -c
lista.o:
	gcc lista.c -Wall -std=c99 -c
caminho.o:
	gcc caminho.c -Wall -std=c99 -c
main.o:
	gcc main.c -Wall -std=c99 -c
clear:
	rm -f *.o main
run:
	./main