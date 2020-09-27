//
// Created by thomasf on 2020/09/27.
//

#include "json_elements.h"

#include <stdlib.h>

JsonElement *CreateElement(JsonType type) {
    JsonElement *element = (JsonElement *) calloc(1, sizeof(JsonElement));
    if (!element)
        return NULL;
    element->type = type;
    return element;
}

void DeleteElement(JsonElement *element) {
    if (!element)
        return;
    if (element->data_ptr) {
        switch (element->type) {
            case kNull:
            case kNumeric:
            case kString:
            case kBool:
                free(element->data_ptr);
                break;
            case kArray:
                DeleteArray((JsonArray *) element->data_ptr);
                break;
            case kObject:
                DeleteObject((JsonObject *) element->data_ptr);
                break;
        }
    }
    free(element);
}

void DeleteVoidElement(void *ptr) {
    DeleteElement((JsonElement *) ptr);
}

KeyValuePair *CreateKeyPair(StringContainer *key, JsonElement *value) {
    KeyValuePair *element = (KeyValuePair *) malloc(sizeof(KeyValuePair));
    if (!element)
        return NULL;
    element->key = key;
    element->value = value;
    return element;
}

void DeleteKeyPair(KeyValuePair *element) {
    if (!element)
        return;
    DeleteStringContainer(element->key);
    DeleteElement(element->value);
    free(element);
}

void DeleteVoidKeyPair(void *ptr) {
    DeleteKeyPair((KeyValuePair *) ptr);
}

JsonArray *CreateArray() {
    JsonArray *array = (JsonArray *) calloc(1, sizeof(JsonArray));
    if (!array)
        return NULL;
    return array;
}

JsonElement *CreateElementFromArray(JsonArray *array) {
    JsonElement *element = CreateElement(kArray);
    if (!element)
        return NULL;
    element->data_ptr = (void *) array;
    element->size = sizeof(JsonArray);
    return element;
}

void PushToArray(JsonArray *array_ptr, JsonElement *element) {
    if (!array_ptr || !element)
        return;
    array_ptr->elements_end = PushToList(array_ptr->elements_end, element, sizeof(JsonElement));
    if (!array_ptr->elements_begin)
        array_ptr->elements_begin = array_ptr->elements_end;
}


void DeleteArray(JsonArray *element) {
    if (!element)
        return;
    EraseList(element->elements_begin, DeleteVoidElement);
    free(element);
}

JsonObject *CreateObject() {
    JsonObject *object = (JsonObject *) calloc(1, sizeof(JsonObject));
    if (!object)
        return NULL;
    return object;
}

JsonElement *CreateElementFromObject(JsonObject *object) {
    JsonElement *element = CreateElement(kObject);
    if (!element)
        return NULL;
    element->data_ptr = (void *) object;
    element->size = sizeof(JsonObject);
    return element;
}

void PushToObject(JsonObject *object_ptr, KeyValuePair *element) {
    if (!object_ptr || !element)
        return;
    object_ptr->key_value_pairs_end = PushToList(object_ptr->key_value_pairs_end, element, sizeof(JsonElement));
    if (!object_ptr->key_value_pairs_begin)
        object_ptr->key_value_pairs_begin = object_ptr->key_value_pairs_end;
}

void DeleteObject(JsonObject *element) {
    if (!element)
        return;
    EraseList(element->key_value_pairs_begin, DeleteVoidKeyPair);
    free(element);
}


void SumStats(JsonStatistics *dest, const JsonStatistics *src) {
    dest->n_arrays += src->n_arrays;
    dest->n_bools += src->n_bools;
    dest->n_nulls += src->n_nulls;
    dest->n_numeric += src->n_numeric;
    dest->n_objects += src->n_objects;
    dest->n_strings += src->n_strings;
    if (src->depth > dest->depth)
        dest->depth = src->depth;
}