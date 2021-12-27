#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "lexer.h"

static void read_char(struct Lexer *this) {
    this->ch = this->read_position < strlen(this->input) ? this->input[this->read_position] : 0;
    this->position = this->read_position;
    ++this->read_position;
}

static struct Token *generate_token(const char *type, char ch) {
    char *s;
    struct Token *t;

    if ((s = malloc(2)) == NULL) {
        fprintf(stderr, "malloc failed [generate_token]\n");
        exit(EXIT_FAILURE);
    }

    s[0] = ch;
    s[1] = 0;

    t = new_token(type, s);

    free(s);

    return t;
}

static struct Token *read_identifier(struct Lexer *this) {
    size_t pos, len;
    char *s;
    struct Token *tok;

    pos = this->position;
    while (isalnum(this->ch) || this->ch == '_') {
        read_char(this);
    }

    len = this->position - pos;

    if ((s = malloc(len+1)) == NULL) {
        fprintf(stderr, "malloc failed [read_identifier]\n");
        exit(EXIT_FAILURE);
    }

    strncpy(s, this->input + pos, len);
    s[len] = 0;

    tok = new_token(lookup_ident(s), s);

    free(s);

    return tok;
}

static struct Token *read_number(struct Lexer *this) {
    size_t pos, len;
    char *s;
    struct Token *tok;

    pos = this->position;

    while (isdigit(this->ch)) {
        read_char(this);
    }

    len = this->position - pos;

    if ((s = malloc(len+1)) == NULL) {
        fprintf(stderr, "malloc failed [read_number]\n");
        exit(EXIT_FAILURE);
    }

    strncpy(s, this->input + pos, len);
    s[len] = 0;

    tok = new_token(INT, s);

    free(s);

    return tok;
}

static int is_whitespace(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}

static char peek_char(struct Lexer *this) {
    return this->read_position < strlen(this->input) ? this->input[this->read_position] : 0;
}

static int is_quotation(char ch) {
    return ch == '"';
}

static struct Token *read_string(struct Lexer *this) {
    size_t pos, len;
    char *s;
    struct Token *tok;

    pos = this->position;
    read_char(this);

    while (!is_quotation(this->ch)) {
        read_char(this);
    }

    read_char(this); // capture last '"'

    len = this->position - pos;

    if ((s = malloc(len+1)) == NULL) {
        fprintf(stderr, "malloc failed [read_string]\n");
        exit(EXIT_FAILURE);
    }

    strncpy(s, this->input + pos, len);
    s[len] = 0;

    tok = new_token(STRING, s);

    free(s);

    return tok;
}

struct Lexer *new_lexer(char *input) {
    struct Lexer *this;
    size_t len;

    if ((this = malloc(sizeof(struct Lexer))) == NULL) {
        fprintf(stderr, "malloc failed [new_lexer]\n");
        exit(EXIT_FAILURE);
    }

    len = strlen(input);

    if ((this->input = malloc(len+1)) == NULL) {
        fprintf(stderr, "malloc failed [struct Lexer, input]\n");
        exit(EXIT_FAILURE);
    }

    strncpy(this->input, input, len);
    this->input[len] = 0;

    this->read_position = 0;
    read_char(this);

    return this;
}

void free_lexer(struct Lexer *this) {
    if (!this) {
        fprintf(stderr, "invalid pointer state [struct Lexer]\n");
        exit(EXIT_FAILURE);
    }

    free(this->input);
    free(this);
}

struct Token *next_token(struct Lexer *this) {
    struct Token *tok;

    while (is_whitespace(this->ch)) {
        read_char(this);
    }

    switch (this->ch) {
        case '=':
            if (peek_char(this) == '=') {
                char ch;
                char *s;

                ch = this->ch;
                read_char(this);

                if ((s = malloc(3)) == NULL) {
                    fprintf(stderr, "malloc failed [next_token, '==']\n");
                    exit(EXIT_FAILURE);
                }

                s[0] = ch;
                s[1] = this->ch;
                s[2] = 0;

                tok = new_token(EQ, s);

                free(s);
            }
            else {
                tok = generate_token(ASSIGN, this->ch);
            }
            break;
        case '-':
            tok = generate_token(MINUS, this->ch);
            break;
        case '!':
            if (peek_char(this) == '=') {
                char ch;
                char *s;

                ch = this->ch;
                read_char(this);
                
                if ((s = malloc(3)) == NULL) {
                    fprintf(stderr, "malloc failed [next_token, '!=']\n");
                    exit(EXIT_FAILURE);
                }

                s[0] = ch;
                s[1] = this->ch;
                s[2] = 0;

                tok = new_token(NOT_EQ, s);

                free(s);
            }
            else {
                tok = generate_token(BANG, this->ch);
            }
            break;
        case '*':
            tok = generate_token(ASTERISK, this->ch);
            break;
        case '/':
            tok = generate_token(SLASH, this->ch);
            break;
        case '<':
            tok = generate_token(LT, this->ch);
            break;
        case '>':
            tok = generate_token(GT, this->ch);
            break;
        case ';':
            tok = generate_token(SEMICOLON, this->ch);
            break;
        case '(':
            tok = generate_token(LPAREN, this->ch);
            break;
        case ')':
            tok = generate_token(RPAREN, this->ch);
            break;
        case ',':
            tok = generate_token(COMMA, this->ch);
            break;
        case '+':
            tok = generate_token(PLUS, this->ch);
            break;
        case '{':
            tok = generate_token(LBRACE, this->ch);
            break;
        case '}':
            tok = generate_token(RBRACE, this->ch);
            break;
        case 0:
            tok = new_token(END_OF_FILE, "");
            break;
        default:
            if (isalpha(this->ch)) {
                tok = read_identifier(this);
                return tok;
            }
            else if (isdigit(this->ch)) {
                tok = read_number(this);
                return tok;
            }
            else if (is_quotation(this->ch)) {
                tok = read_string(this);
                return tok;
            }
            else {
                tok = generate_token(ILLEGAL, this->ch);
            }
    }

    read_char(this);
    return tok;
}