CC=gcc -Wall -g

all: prog

stack.o: stack.h
image.o: image.h
lecture.o : lecture.h
ordre.o : ordre.h
main.o: main.c


prog: main.o ordre.o lecture.o image.o stack.o
	$(CC) -o $@ $^ -lm