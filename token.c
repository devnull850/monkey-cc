#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

const char ILLEGAL[] = "ILLEGAL";
const char END_OF_FILE[] = "EOF";

const char IDENT[] = "IDENT";
const char INT[] = "INT";

const char ASSIGN[] = "=";
const char PLUS[] = "+";

const char COMMA[] = ",";
const char SEMICOLON[] = ";";

const char LPAREN[] = "(";
const char RPAREN[] = ")";
const char LBRACE[] = "{";
const char RBRACE[] = "}";

const char FUNCTION[] = "FUNCTION";
const char LET[] = "LET";

const struct Map keywords[] = {
    {.key = "fn", .value = "FUNCTIONS"},
    {.key = "let", .value = "LET"}
};

static const size_t NUM_KEYWORDS = 2;

struct Token *new_token(const char *type, char *literal) {
    struct Token *tok;
    size_t len;

    if ((tok = malloc(sizeof(struct Token))) == NULL) {
        fprintf(stderr, "malloc failed [struct Token]\n");
        exit(EXIT_FAILURE);
    }

    len = strlen(type);

    if ((tok->type = malloc(len+1)) == NULL) {
        fprintf(stderr, "malloc failed [struct Token, type]\n");
        exit(EXIT_FAILURE);
    }

    strncpy(tok->type, type, len);
    tok->type[len] = 0;

    len = strlen(literal);

    if ((tok->literal = malloc(len+1)) == NULL) {
        fprintf(stderr, "malloc failed [struct Token, literal]\n");
        exit(EXIT_FAILURE);
    }

    strncpy(tok->literal, literal, len);
    tok->literal[len] = 0;

    return tok;
}

void free_token(struct Token *tok) {
    if (!tok) {
        fprintf(stderr, "invalid pointer state [struct Token]\n");
        exit(EXIT_FAILURE);
    }

    free(tok->literal);
    free(tok->type);
    free(tok);
}

const char *lookup_ident(char *id) {
    for (size_t i = 0; i < NUM_KEYWORDS; ++i) {
        if (!strncmp(id, keywords[i].key, strlen(keywords[i].key))) {
            return keywords[i].value;
        }
    }

    return IDENT;
}