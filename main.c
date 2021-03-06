#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "repl.h"
#include "token.h"
#include "util.h"

int main(int argc, char *argv[]) {
    struct ByteStream *bytes;
    struct Lexer *lex;
    struct Token *tok;

    if (argc == 1) {
        repl_loop();
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; ++i) {
        bytes = get_file_stream(argv[i]);
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
}