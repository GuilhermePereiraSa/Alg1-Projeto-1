CC = gcc
CFLAGS = -std=c99 -Wall -lm -g
IMPLEMETATIONS := $(wildcard *.c)
HEADERS = *.h
OBJS = $(IMPLEMETATIONS:.c=.o)

all: main

main: $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $<
run:
	@./main

zip:
	@zip -r main.zip $(IMPLEMETATIONS) $(HEADERS) Makefile

clean:
	@rm main *.zip *.o
# end

# end
