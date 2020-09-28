//
// Created by thomasf on 2020/09/25.
//

#include "file_serializer.h"

#include "string_container.h"
#include "json_handlers.h"
#include "file_reader.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

JsonStatistics
PrintStatsPrivate(JsonElement *root_ptr, unsigned int level, const StringContainer *path, unsigned int *max_level,
                  StringContainer *max_level_path);

void
HandleElementsStatistics(JsonType elem_type, JsonStatistics *stats, const StringContainer *prefix, JsonElement *element,
                         unsigned int level, unsigned int *max_level,
                         StringContainer *max_level_path);


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


void FormattedStatisticsOutPut(const JsonStatistics *stats, const char *path, bool is_object) {
    if (is_object)
        printf("Object");
    else
        printf("Array");
    printf(": %s\n\tNulls:%d\n\tNumerics:%d\n\tStrings:%d\n\tBools:%d\n\tArrays:%d\n\tObjects:%d\n\tDepth:%d\n\n",
           path,
           stats->n_nulls, stats->n_numeric,
           stats->n_strings, stats->n_bools,
           stats->n_arrays, stats->n_objects, stats->depth);
}

void
HandleElementsStatistics(JsonType elem_type, JsonStatistics *stats, const StringContainer *prefix, JsonElement *element,
                         unsigned int level, unsigned int *max_level,
                         StringContainer *max_level_path) {
    switch (elem_type) {
        case kNull:
            stats->n_nulls++;
            break;
        case kNumeric:
            stats->n_numeric++;
            break;
        case kString:
            stats->n_strings++;
            break;
        case kBool:
            stats->n_bools++;
            break;
        case kArray: {
            stats->n_arrays++;
            JsonStatistics child_stat = PrintStatsPrivate(element, level, prefix, max_level, max_level_path);
            SumStats(stats, &child_stat);
            break;
        }
        case kObject: {
            stats->n_objects++;
            JsonStatistics child_obj_stat = PrintStatsPrivate(element, level, prefix, max_level,
                                                              max_level_path);
            SumStats(stats, &child_obj_stat);
        }
        default:
            break;
    }
}

JsonStatistics
PrintStatsPrivate(JsonElement *root_ptr, unsigned int level, const StringContainer *path, unsigned int *max_level,
                  StringContainer *max_level_path) {
    JsonStatistics stats = {0, 0, 0, 0, 0, 0, level};

    if (!root_ptr)
        return stats;
    JsonType type = root_ptr->type;

    List *buffer = NULL;

    if (type == kArray)
        buffer = ((JsonArray *) root_ptr->data_ptr)->elements_begin;
    else if (type == kObject)
        buffer = ((JsonObject *) root_ptr->data_ptr)->key_value_pairs_begin;
    else
        return stats;

    unsigned int index = 0;
    do {
        if (!buffer->value)
            continue;
        JsonElement *element =
                type != kObject ? (JsonElement *) buffer->value : ((KeyValuePair *) buffer->value)->value;
        if (!element)
            continue;
        JsonType elem_type = element->type;
        StringContainer *prefix = NULL;
        if (elem_type == kObject || elem_type == kArray) {
            if (type == kObject)
                prefix = StringCatPath(path, ((KeyValuePair *) buffer->value)->key);
            else {
                char str[20] = {0};
                memset(str, 0, 20);
                sprintf(str, "[%d]", index);
                prefix = StringAdd(path, str, strnlen(str, 20) + 1);
            }
        }
        HandleElementsStatistics(elem_type, &stats, prefix, element, level, max_level,
                                 max_level_path);
        if (prefix)
            DeleteStringContainer(prefix);
        index++;
    } while ((buffer = NextNList(buffer, 1)));

    FormattedStatisticsOutPut(&stats, path->value, type == kObject);

    if (level > *max_level) {
        *max_level = level;
        EmplaceStringContainer(max_level_path, path);
    }

    return stats;
}

void PrintStatistics(JsonElement *root_ptr) {
    StringContainer *buffer = CreateStringContainer("$", 2);
    StringContainer *max_path = CreateStringContainer("$", 2);
    unsigned int max_depth = 0;
    PrintStatsPrivate(root_ptr, 0, buffer, &max_depth, max_path);

    printf("Deepest object/array is `%s` with depth = %d.\n", max_path->value, max_depth);

    DeleteStringContainer(max_path);
    DeleteStringContainer(buffer);
}

void DeleteJsonElement(JsonElement *root_ptr) {
    if (!root_ptr)
        return;
    DeleteElement(root_ptr);
}
