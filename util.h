#ifndef UTIL_H
#define UTIL_H

#include "token.h"

struct ByteStream {
    char *buf;
    size_t len;
};

struct ByteStream *get_file_stream(char *);
void free_bytes(struct ByteStream *);

void print_token(struct Token *);

#endif /* UTIL_H */