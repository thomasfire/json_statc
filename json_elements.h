//
// Created by thomasf on 2020/09/25.
//

#pragma once

#include "list.h"
#include "string_container.h"

typedef enum JsonType {
    kNull,
    kNumeric,
    kString,
    kBool,
    kArray,
    kObject
} JsonType;

typedef struct JsonStatistics {
    unsigned int n_nulls;
    unsigned int n_numeric;
    unsigned int n_strings;
    unsigned int n_bools;
    unsigned int n_objects;
    unsigned int n_arrays;
    unsigned int depth;
} JsonStatistics;


typedef struct JsonElement {
    // struct JsonStatistics statistics;
    enum JsonType type;
    void *data_ptr; // not nullptr only for objects and arrays. It is memory optimization
    unsigned int size;
} JsonElement;

typedef struct KeyValuePair {
    StringContainer *key;
    JsonElement *value;
} KeyValuePair;


typedef struct JsonObject {
    List *key_value_pairs_begin;
    List *key_value_pairs_end;
} JsonObject;

typedef struct JsonArray {
    List *elements_begin;
    List *elements_end;
} JsonArray;


void SumStats(JsonStatistics *dest, const JsonStatistics *src);

JsonElement *CreateElement(JsonType type);

void DeleteElement(JsonElement *element);

KeyValuePair *CreateKeyPair(StringContainer *key, JsonElement *value);

void DeleteKeyPair(KeyValuePair *element);

JsonArray *CreateArray();

JsonElement *CreateElementFromArray(JsonArray *type);

void PushToArray(JsonArray *array_ptr, JsonElement *element);

void DeleteArray(JsonArray *element);

JsonObject *CreateObject();

JsonElement *CreateElementFromObject(JsonObject *type);

void PushToObject(JsonObject *array_ptr, KeyValuePair *element);

void DeleteObject(JsonObject *element);

