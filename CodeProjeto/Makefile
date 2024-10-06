all: projeto.o pilha.o item.o
	gcc -Wall -std=c99 projeto.o pilha.o item.o -o projeto

projeto.o: projeto.c pilha.h item.h
	gcc -c projeto.c

item.o: item.c item.h
	gcc -c item.c

pilha.o: pilha.c pilha.h
	gcc -c pilha.c

run: projeto
	./projeto
	
clean:
	rm -f *.o projeto