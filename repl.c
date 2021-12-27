#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "repl.h"
#include "util.h"

#define LEN 0x100

const char QUIT[] = "quit";

void repl_loop(void) {
    char buf[LEN];
    struct Lexer *lex;
    struct Token *tok;

    puts("Welcome to the Monkey programming language");
    puts("Feel free to enter commands");

    while (1) {
        printf(">> ");
        fgets(buf, LEN-1, stdin);

        if (!strncmp(buf, QUIT, strlen(QUIT))) {
            break;
        }

        lex = new_lexer(buf);

        for (tok = next_token(lex);
                strncmp(tok->type, END_OF_FILE, strlen(END_OF_FILE));
                tok = next_token(lex)) {
            print_token(tok);
            free_token(tok);
        }

        free_token(tok);
        free_lexer(lex);
    }
}