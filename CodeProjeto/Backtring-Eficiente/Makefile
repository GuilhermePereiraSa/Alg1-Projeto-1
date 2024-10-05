all: projeto

projeto: projeto.o pilha.o item.o
	gcc -Wall -std=c99 projeto.o pilha.o item.o -o projeto

projeto.o: projeto1alg.c pilha.h item.h
	gcc -Wall -std=c99 -c projeto1alg.c

item.o: item.c item.h
	gcc -c item.c

pilha.o: pilha.c pilha.h
	gcc -c pilha.c

run: projeto
	./projeto
	
clean:
	rm -f *.o projeto