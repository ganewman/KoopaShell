all: main.o parse.o command.o
	gcc main.o parse.o command.o

main.o: main.c parse.h command.h
	gcc -c main.c

parse.o: parse.c parse.h
	gcc -c parse.c

command.o: command.c command.h
	gcc -c command.c

run: all
	./a.out
