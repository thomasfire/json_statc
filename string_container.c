//
// Created by thomasf on 2020/09/25.
//

#include "string_container.h"

#include <stdlib.h>
#include <string.h>

StringContainer *CreateStringContainer(const char *value, unsigned int size) {
    if (!value || !size)
        return NULL;

    StringContainer *buffer = (StringContainer *) malloc(sizeof(StringContainer));
    if (!buffer)
        return NULL;
    buffer->size = size;
    buffer->value = (char *) malloc(sizeof(char) * size);
    strncpy(buffer->value, value, size);
    return buffer;
}

StringContainer *CreateStringContainerWithNull(const char *value, unsigned int size) {
    if (!value || !size)
        return NULL;

    StringContainer *buffer = (StringContainer *) malloc(sizeof(StringContainer));
    if (!buffer)
        return NULL;
    buffer->size = size + 1;
    buffer->value = (char *) malloc(sizeof(char) * (size + 1));
    strncpy(buffer->value, value, size);
    buffer->value[size] = '\0';
    return buffer;
}

void EmplaceStringContainer(StringContainer *dest, const StringContainer *src) {
    if (!dest || !src)
        return;

    if (dest->value)
        free(dest->value);

    dest->value = (char *) malloc(sizeof(char) * src->size);
    dest->size = src->size;
    strncpy(dest->value, src->value, dest->size);
}

void DeleteStringContainer(StringContainer *str) {
    if (!str)
        return;
    if (str->value)
        free(str->value);
    free(str);
}


StringContainer *StringCatPath(const StringContainer *dest, const StringContainer *src) {
    if (!dest || !src)
        return NULL;

    StringContainer *buffer = (StringContainer *) malloc(sizeof(StringContainer));
    if (!buffer)
        return NULL;
    buffer->size = dest->size + src->size;
    buffer->value = (char *) malloc(sizeof(char) * buffer->size);
    strncpy(buffer->value, dest->value, dest->size - 1);
    buffer->value[dest->size - 1] = '.';
    strncpy(&buffer->value[dest->size], src->value, src->size);
    return buffer;
}

StringContainer *StringAdd(const StringContainer *dest, const char *value, unsigned int size) {
    if (!dest || !value)
        return NULL;

    StringContainer *buffer = (StringContainer *) malloc(sizeof(StringContainer));
    if (!buffer)
        return NULL;
    buffer->size = dest->size + size - 1;
    buffer->value = (char *) malloc(sizeof(char) * buffer->size);
    strncpy(buffer->value, dest->value, dest->size - 1);
    strncpy(&buffer->value[dest->size - 1], value, size);
    return buffer;
}