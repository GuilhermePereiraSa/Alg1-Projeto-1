back: item.o pilha.o back.o
	gcc -Wall -std=c99 item.o pilha.o back.o -o backtracking

back.o:
	gcc -c back.c

time-back: item.o pilha.o time-back-perm.o
	gcc -Wall -std=c99 item.o pilha.o time-back-perm.o -o time-backtracking

time-back-perm.o:
	gcc -c time-back-perm.c

item.o: ../item.c ../item.h
	gcc -c ../item.c

pilha.o: ../pilha.c ../pilha.h
	gcc -c ../pilha.c

run-back:
	./backtracking

run-time-back:
	./time-backtracking

clean:
	rm -f *.o backtracking time-backtracking

