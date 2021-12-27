#ifndef TOKEN_H
#define TOKEN_H

#include "util.h"

extern const char ILLEGAL[];
extern const char END_OF_FILE[];

extern const char IDENT[];
extern const char INT[];

extern const char ASSIGN[];
extern const char PLUS[];
extern const char MINUS[];
extern const char BANG[];
extern const char ASTERISK[];
extern const char SLASH[];

extern const char EQ[];
extern const char NOT_EQ[];
extern const char LT[];
extern const char GT[];

extern const char COMMA[];
extern const char SEMICOLON[];

extern const char LPAREN[];
extern const char RPAREN[];
extern const char LBRACE[];
extern const char RBRACE[];

extern const char FUNCTION[];
extern const char LET[];
extern const char TRUE[];
extern const char FALSE[];
extern const char IF[];
extern const char ELSE[];
extern const char RETURN[];

extern const struct Map keywords[];

struct Token {
    char *type;
    char *literal;
};

struct Token *new_token(const char *, char *);
void free_token(struct Token *);

const char *lookup_ident(char *);

#endif /* TOKEN_H */