CC=gcc
CFLAGS=-I.
all : dead parallel_f mutex_w mutex_wo

dead :
	$(CC) -o dead dead.c -lpthread $(CFLAGS)

parallel_f :
	$(CC) -o parallel_f parallel_f.c -lpthread $(CFLAGS)

mutex_wo : 
	$(CC) -o mutex_wo mutex_wo.c -lpthread $(CFLAGS)

mutex_w: 
	$(CC) -o mutex_w mutex_w.c -lpthread $(CFLAGS)

clean :
	rm dead parallel_f mutex_w mutex_wo