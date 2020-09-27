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

void DeleteStringContainer(StringContainer *str) {
    if (!str)
        return;
    if (str->value)
        free(str->value);
    free(str);
}
