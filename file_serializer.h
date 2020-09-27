//
// Created by thomasf on 2020/09/25.
//

#pragma once

#include "json_elements.h"

typedef enum {
    kReadOk,
    kReadEmpty,
    kReadFailure,
    kParseFailure
} ReadResult;

JsonElement *GetRootFromFile(const char *filepath, ReadResult *result);

void PrintStatistics(JsonElement *root_ptr);

void DeleteJsonElement(JsonElement *root_ptr);