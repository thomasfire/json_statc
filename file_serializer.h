//
// Created by thomasf on 2020/09/25.
//

#pragma once

#include "json_elements.h"

typedef enum ReadResult {
    kReadOk,
    kReadEmpty,
    kReadFailure,
    kParseFailure
} ReadResult;

JsonElement *GetRootFromFile(const char *filepath, enum ReadResult *result);

void PrintStatistics(JsonElement *root_ptr);

void DeleteJsonElement(JsonElement *root_ptr);