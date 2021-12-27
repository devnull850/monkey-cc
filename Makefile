all: main

main: main.o lexer.o token.o util.o
	gcc -Wall -Werror -o main main.o lexer.o token.o util.o

main.o: main.c
	gcc -c main.c

lexer.o: lexer.c
	gcc -c lexer.c

token.o: token.c
	gcc -c token.c

util.o: util.c
	gcc -c util.c

.PHONY:
clean:
	rm main main.o lexer.o token.o util.o