//
// Created by thomasf on 2020/09/25.
//

#include "file_serializer.h"

#include "string_container.h"
#include "json_handlers.h"
#include "file_reader.h"

#include <stdio.h>

JsonElement *ProcessStrToJson(const StringContainer *json_str) {
    JsonElement *root = NULL;
    unsigned int index = 0;

    HandleSpaces(json_str, &index);
    root = HandleElement(json_str, &index);
    HandleSpaces(json_str, &index);
    if (index != json_str->size - 1) {
        DeleteJsonElement(root);
        return NULL;
    }

    return root;
}

JsonElement *GetRootFromFile(const char *filepath, enum ReadResult *result) {
    StringContainer *filedata = ReadFile(filepath);
    if (filedata == NULL) {
        *result = kReadFailure;
        return NULL;
    } else if (filedata->size == 1) {
        *result = kReadEmpty;
        DeleteStringContainer(filedata);
        return NULL;
    }

    JsonElement *result_json = ProcessStrToJson(filedata);

    if (!result_json)
        *result = kParseFailure;

    DeleteStringContainer(filedata);

    return result_json;
}


void PrintStatsPrivate(JsonElement *root_ptr, unsigned int level) {

}

void PrintStatistics(JsonElement *root_ptr) {
    PrintStatsPrivate(root_ptr, 0);
}

void DeleteJsonElement(JsonElement *root_ptr) {
    if (!root_ptr)
        return;
    DeleteElement(root_ptr);
}
