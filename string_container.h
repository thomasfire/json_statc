//
// Created by thomasf on 2020/09/25.
//

#pragma once

typedef struct StringContainer {
    char *value;
    unsigned int size;
} StringContainer;


StringContainer *CreateStringContainer(const char *value, unsigned int size);

void DeleteStringContainer(StringContainer *str);
