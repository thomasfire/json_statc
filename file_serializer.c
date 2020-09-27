//
// Created by thomasf on 2020/09/25.
//

#include "file_serializer.h"

#include "string_container.h"
#include "json_handlers.h"
#include "file_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

JsonElement *GetRootFromFile(const char *filepath, ReadResult *result) {
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


void FormattedStatisticsOutPut(const JsonStatistics *stats, const char *path) {
    printf("Object: %s\nNulls:%d\nNumerics:%d\nStrings:%d\nBools:%d\nArrays:%d\nObjects:%d\nDepth:%d\n", path,
           stats->n_nulls, stats->n_numeric,
           stats->n_strings, stats->n_bools,
           stats->n_arrays, stats->n_objects, stats->depth);
}

JsonStatistics PrintStatsPrivate(JsonElement *root_ptr, unsigned int level, const StringContainer * path) {
    JsonStatistics stats = {0, 0, 0, 0, 0, 0, level};

    if (!root_ptr)
        return stats;
    JsonType type = root_ptr->type;
    switch (type) {
        case kNull:
        case kNumeric:
        case kString:
        case kBool:
            return stats;
        case kArray:
        case kObject:
            break;
    };
    List *buffer = NULL;

    if (type == kArray)
        buffer = ((JsonArray *) root_ptr->data_ptr)->elements_begin;
    else
        buffer = ((JsonObject *) root_ptr->data_ptr)->key_value_pairs_begin;

    unsigned int index = 0;
    do {
        if (!buffer->value)
            continue;
        JsonElement *element = type == kArray ? (JsonElement *) buffer->value : ((KeyValuePair *) buffer->value)->value;
        if (!element)
            continue;
        JsonType elem_type = element->type;
        switch (elem_type) {
            case kNull:
                stats.n_nulls++;
                break;
            case kNumeric:
                stats.n_numeric++;
                break;
            case kString:
                stats.n_strings++;
                break;
            case kBool:
                stats.n_bools++;
                break;
            case kArray:
                stats.n_arrays++;
                char str[20];
                sprintf(str, ".%d", index);
                StringContainer * buffername= StringAdd(path, str, strnlen(str, 20));
                JsonStatistics child_stat = PrintStatsPrivate(element, level + 1, buffername);
                SumStats(&stats, &child_stat);
                DeleteStringContainer(buffername);
                break;
            case kObject:
                stats.n_objects++;
                StringContainer * buffer_name= StringCatPath(path, ((KeyValuePair *) buffer->value)->key);
                JsonStatistics child_obj_stat = PrintStatsPrivate(element, level + 1, buffer_name);
                SumStats(&stats, &child_obj_stat);
                DeleteStringContainer(buffer_name);
        };
        index++;
    } while ((buffer = NextNList(buffer, 1)));

    FormattedStatisticsOutPut(&stats, path->value);
}

void PrintStatistics(JsonElement *root_ptr) {
    StringContainer * buffer = CreateStringContainer("root", 5);
    PrintStatsPrivate(root_ptr, 0, buffer);
    DeleteStringContainer(buffer);
}

void DeleteJsonElement(JsonElement *root_ptr) {
    if (!root_ptr)
        return;
    DeleteElement(root_ptr);
}
