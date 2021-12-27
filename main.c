#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "token.h"

const char FILENAME[] = "sample";
const char MODE[] = "rb";

static void print_token(struct Token *tok) {
    printf("{type: %s, literal: %s}\n", tok->type, tok->literal);
}

int main(void) {
    char *buf;
    long len;
    struct Lexer *lex;
    struct Token *tok;
    FILE *fd;

    if ((fd = fopen(FILENAME, MODE)) == NULL) {
        fprintf(stderr, "error opening file [%s]\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    fseek(fd, 0, SEEK_END);
    len = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    if ((buf = malloc(len)) == NULL) {
        fprintf(stderr, "malloc failed [buf]\n");
        exit(EXIT_FAILURE);
    }

    if (fread(buf, 1, len, fd) != len) {
        fprintf(stderr, "error reading file [%s]\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    if (fclose(fd) == EOF) {
        fprintf(stderr, "error closing file [%s]\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    lex = new_lexer(buf);
    free(buf);

    for (tok = next_token(lex);
            strncmp(tok->type, END_OF_FILE, strlen(END_OF_FILE));
            tok = next_token(lex)) {
        print_token(tok);
        free_token(tok);
    }

    free_lexer(lex);
}