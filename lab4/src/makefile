CC=gcc
CFLAGS=-I.


parallel_sum : libsum.a 
	$(CC) -pthread -o parallel_sum parallel_sum.c libsum.a $(CFLAGS)

libsum.a : utils.o Sum.o utils.h Sum.h
	ar rcs -o libsum.a utils.o Sum.o

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

Sum.o : Sum.h
	$(CC) -o Sum.o -c Sum.c $(CFLAGS)

clean :
	rm utils.o Sum.o libsum.a parallel_sum