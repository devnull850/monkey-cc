OBJ=main.o lexer.o token.o util.o repl.o

all: monkey-cc

monkey-cc: $(OBJ)
	gcc -Wall -Werror -o monkey-cc $(OBJ)

main.o: main.c
	gcc -c main.c

lexer.o: lexer.c
	gcc -c lexer.c

token.o: token.c
	gcc -c token.c

util.o: util.c
	gcc -c util.c

repl.o: repl.c
	gcc -c repl.c

.PHONY:
clean:
	rm monkey-cc $(OBJ)