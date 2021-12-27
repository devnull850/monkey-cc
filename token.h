#ifndef TOKEN_H
#define TOKEN_H

extern const char ILLEGAL[];
extern const char END_OF_FILE[];

extern const char IDENT[];
extern const char INT[];

extern const char ASSIGN[];
extern const char PLUS[];

extern const char COMMA[];
extern const char SEMICOLON[];

extern const char LPAREN[];
extern const char RPAREN[];
extern const char LBRACE[];
extern const char RBRACE[];

extern const char FUNCTION[];
extern const char LET[];

struct Token {
    char *type;
    char *literal;
};

struct Map {
    char *key;
    char *value;
};

extern const struct Map keywords[];

struct Token *new_token(const char *, char *);
void free_token(struct Token *);

const char *lookup_ident(char *);

#endif /* TOKEN_H */