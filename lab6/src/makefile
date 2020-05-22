CC=gcc
CCFLAGS=-I.

all : client server

client : MultModulo.o MultModulo.h
	$(CC) -o client MultModulo.o client.c -lpthread $(CCFLAGS)

server : MultModulo.o MultModulo.h
	$(CC) -o server MultModulo.o server.c -lpthread $(CCFLAGS)

MultModulo.o : MultModulo.h
	$(CC) -o MultModulo.o -c MultModulo.c $(CCFLAGS)

clean :
	rm client server MultModulo.o