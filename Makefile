CC     = gcc
CFLAGS = -Wall -Wextra -g

build: tema1.c
	$(CC) $(CFLAGS) -o tema1 tema1.c

run:
	./tema1

clean:
	rm -f tema1 tema1.out