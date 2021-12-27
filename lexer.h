#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

#include "token.h"

struct Lexer {
    char *input;
    size_t position;
    size_t read_position;
    char ch;
};

struct Lexer *new_lexer(char *);
void free_lexer(struct Lexer *);

struct Token *next_token(struct Lexer *);

#endif /* LEXER_H */