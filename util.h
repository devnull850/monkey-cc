#ifndef UTIL_H
#define UTIL_H

struct Map {
    char *key;
    char *value;
};

struct ByteStream {
    char *buf;
    size_t len;
};

struct ByteStream *get_file_stream(char *);
void free_bytes(struct ByteStream *);

#endif /* UTIL_H */