#include <stdio.h>
#include <stdlib.h>

#include "util.h"

const char MODE[] = "rb";

struct ByteStream *get_file_stream(char *filename) {
    FILE *fd;
    char *buf;
    size_t len;
    struct ByteStream *bytes;

    if ((fd = fopen(filename, MODE)) == NULL) {
        fprintf(stderr, "error opening file [%s]\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(fd, 0, SEEK_END);
    len = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    if ((buf = malloc(len+1)) == NULL) {
        fprintf(stderr, "malloc failed [buf]\n");
        exit(EXIT_FAILURE);
    }

    if (fread(buf, 1, len, fd) != len) {
        fprintf(stderr, "error reading file [%s]\n", filename);
        exit(EXIT_FAILURE);
    }

    buf[len] = 0;

    if (fclose(fd) == EOF) {
        fprintf(stderr, "error closing file [%s]\n", filename);
        exit(EXIT_FAILURE);
    }

    if ((bytes = malloc(sizeof(struct ByteStream))) == NULL) {
        fprintf(stderr, "malloc failed [ByteStream]\n");
        exit(EXIT_FAILURE);
    }

    bytes->buf = buf;
    bytes->len = len;

    return bytes;
}

void free_bytes(struct ByteStream *bytes) {
    if (!bytes) {
        fprintf(stderr, "invalid pointer state [ByteStream]\n");
        exit(EXIT_FAILURE);
    }

    free(bytes->buf);
    free(bytes);
}

void print_token(struct Token *tok) {
    printf("{type: %s, literal: %s}\n", tok->type, tok->literal);
}