CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic

kruscal: main.c
	$(CC) $(CFLAGS) -o kruscal main.c
