CC=gcc
CFLAGS=-I. -pthread -std=c99 -lpthread

semaphores: semaphores.c
	$(CC) -o $@ $^ $(CFLAGS)

example: example.c
	$(CC) -o $@ $^ $(CFLAGS)

