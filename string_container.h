//
// Created by thomasf on 2020/09/25.
//

#pragma once

typedef struct {
    char *value;
    unsigned int size;
} StringContainer;


StringContainer *CreateStringContainer(const char *value, unsigned int size);

StringContainer *CreateStringContainerWithNull(const char *value, unsigned int size);

/// Replaces the contents of dest with contents of src
void EmplaceStringContainer(StringContainer *dest, const StringContainer *src);

void DeleteStringContainer(StringContainer *str);

StringContainer *StringCatPath(const StringContainer *dest, const StringContainer *src);

StringContainer *StringAdd(const StringContainer *dest, const char *value, unsigned int size);
