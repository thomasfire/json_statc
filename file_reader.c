//
// Created by thomasf on 2020/09/27.
//

#include "file_reader.h"

#include <stdlib.h>
#include <stdio.h>

StringContainer *ReadFile(const char *filename) {
    char *buffer = NULL;
    unsigned int string_size, read_size;
    FILE *handler = fopen(filename, "r");

    if (!handler)
        return NULL;

    fseek(handler, 0, SEEK_END);
    string_size = ftell(handler);
    rewind(handler);

    buffer = (char *) malloc(sizeof(char) * (string_size + 1));
    if (!buffer) {
        fclose(handler);
        return NULL;
    }

    read_size = fread(buffer, sizeof(char), string_size, handler);

    buffer[string_size] = '\0';

    if (string_size != read_size) {
        free(buffer);
        buffer = NULL;
    }

    fclose(handler);

    StringContainer *str = CreateStringContainer(buffer, string_size + 1);
    if (buffer)
        free(buffer);

    return str;
}
