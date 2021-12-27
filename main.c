#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "token.h"
#include "util.h"

static void print_token(struct Token *tok) {
    printf("{type: %s, literal: %s}\n", tok->type, tok->literal);
}

int main(void) {
    struct ByteStream *bytes;
    struct Lexer *lex;
    struct Token *tok;

    bytes = get_file_stream("sample");
    lex = new_lexer(bytes->buf);
    free_bytes(bytes);

    for (tok = next_token(lex);
            strncmp(tok->type, END_OF_FILE, strlen(END_OF_FILE));
            tok = next_token(lex)) {
        print_token(tok);
        free_token(tok);
    }

    free_token(tok);
    free_lexer(lex);
}