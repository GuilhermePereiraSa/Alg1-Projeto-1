all: item.o lista.o main.o
	gcc -Wall -std=c99 item.o lista.o main.o -o principal

item.o:
	gcc -c ../EDs/item.c

lista.o:
	gcc -c ../EDs/lista.c 

main.o:
	gcc -c main.c

clear:
	rm *.o principal

run:
	./principal  < ../testes/input_04.in