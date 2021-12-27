all: main

main: main.o lexer.o token.o
	gcc -Wall -Werror -o main main.o lexer.o token.o

main.o: main.c
	gcc -c main.c

lexer.o: lexer.c
	gcc -c lexer.c

token.o: token.c
	gcc -c token.c

.PHONY:
clean:
	rm main main.o lexer.o token.o