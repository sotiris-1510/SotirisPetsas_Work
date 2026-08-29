CC = gcc
CFLAGS = -pthread -Wall

all: ex1/ex1 ex2/ex2

ex1/ex1: ex1/ex1.c ex1/ex1_monitor.c ex1/ex1_monitor.h
	$(CC) $(CFLAGS) -o ex1/ex1 ex1/ex1.c

ex2/ex2: ex2/ex2.c ex2/ex2_monitor.c ex2/ex2_monitor.h
	$(CC) $(CFLAGS) -o ex2/ex2 ex2/ex2.c

clean:
	rm -f ex1/ex1 ex2/ex2

.PHONY: all clean
