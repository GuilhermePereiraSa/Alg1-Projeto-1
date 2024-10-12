all: aresta.o lista.o caminho.o combinado.o
	gcc aresta.o lista.o caminho.o combinado.o -o combinado
aresta.o:
	gcc aresta.c -Wall -std=c99 -c
lista.o:
	gcc lista.c -Wall -std=c99 -c
caminho.o:
	gcc caminho.c -Wall -std=c99 -c
combinado.o:
	gcc combinado.c -Wall -std=c99 -c
clear:
	rm -f *.o combinado
run:
	./combinado