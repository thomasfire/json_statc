//
// Created by thomasf on 2020/09/27.
//

#include "json_handlers.h"

#include "char_helpers.h"

#include <string.h>

void HandleSpaces(const StringContainer *string, unsigned int *begin) {
    while (*begin < string->size && IsWhitespace(string->value[*begin]))
        (*begin)++;
}

JsonElement *HandleElement(const StringContainer *string, unsigned int *begin) {
    char current_symbol = string->value[*begin];
    if (current_symbol == '{')
        return HandleObject(string, begin);
    else if (current_symbol == '[')
        return HandleArray(string, begin);
    else if (current_symbol == '"')
        return HandleString(string, begin);
    else if (IsBoolBegin(current_symbol))
        return HandleBool(string, begin);
    else if (IsNullBegin(current_symbol))
        return HandleNull(string, begin);
    else if (IsNumeric(current_symbol))
        return HandleNumeric(string, begin);
    return NULL;
}

KeyValuePair *HandleKeyPair(const StringContainer *string, unsigned int *begin) {
    if (*begin < string->size && string->value[*begin] != '"')
        return NULL;

    (*begin)++;
    unsigned int str_begin = *begin;
    StringContainer *key = NULL;
    while (*begin < string->size) {
        if (string->value[*begin] == '\\') {
            if (*begin + 1 < string->size && IsCorrectEscape(string->value[*begin], string->value[*begin + 1]))
                *begin += 2;
            else
                return NULL;
        }
        if (string->value[*begin] == '"') {
            key = CreateStringContainer(&string->value[str_begin], *begin - str_begin);
            (*begin)++;
            break;
        }
        if (string->value[*begin] == '\0')
            return NULL;
        (*begin)++;
    }

    HandleSpaces(string, begin);

    if (*begin < string->size && string->value[*begin] != ':') {
        DeleteStringContainer(key);
        return NULL;
    }
    (*begin)++;
    HandleSpaces(string, begin);

    JsonElement *element = HandleElement(string, begin);

    if (!element) {
        DeleteStringContainer(key);
        return NULL;
    }
    return CreateKeyPair(key, element);
}

JsonElement *HandleObject(const StringContainer *string, unsigned int *begin) {
    (*begin)++;
    HandleSpaces(string, begin);
    if (*begin < string->size && string->value[*begin] == ',')
        return NULL;
    JsonObject *object = CreateObject();
    bool open_comma = false;
    while (*begin < string->size) {
        HandleSpaces(string, begin);
        char current_symbol = string->value[*begin];
        if (current_symbol == '}' && !open_comma) {
            (*begin)++;
            return CreateElementFromObject(object);
        } else if (open_comma && (current_symbol == '}' || current_symbol == '\0'))
            break;

        KeyValuePair *element = HandleKeyPair(string, begin);
        open_comma = false;
        if (!element)
            break;
        PushToObject(object, element);
        HandleSpaces(string, begin);
        if (string->value[*begin] == ',') {
            open_comma = true;
            (*begin)++;
        }
    }
    DeleteObject(object);
    return NULL;
}

JsonElement *HandleArray(const StringContainer *string, unsigned int *begin) {
    (*begin)++;
    HandleSpaces(string, begin);
    if (*begin < string->size && string->value[*begin] == ',')
        return NULL;
    JsonArray *array = CreateArray();
    bool open_comma = false;
    while (*begin < string->size) {
        HandleSpaces(string, begin);
        char current_symbol = string->value[*begin];
        if (current_symbol == ']' && !open_comma) {
            (*begin)++;
            return CreateElementFromArray(array);
        } else if (open_comma && (current_symbol == ']' || current_symbol == '\0'))
            break;

        JsonElement *element = HandleElement(string, begin);
        if (!element)
            break;
        open_comma = false;
        PushToArray(array, element);
        HandleSpaces(string, begin);
        if (string->value[*begin] == ',') {
            open_comma = true;
            (*begin)++;
        }
    }
    DeleteArray(array);
    return NULL;
}

JsonElement *HandleString(const StringContainer *string, unsigned int *begin) {
    (*begin)++;
    while (*begin < string->size) {
        if (string->value[*begin] == '\\') {
            if (*begin + 1 < string->size && IsCorrectEscape(string->value[*begin], string->value[*begin + 1]))
                *begin += 2;
            else
                return NULL;
        }
        if (string->value[*begin] == '"') {
            (*begin)++;
            return CreateElement(kString);
        }
        (*begin)++;
    }
    return NULL;
}

JsonElement *HandleNumeric(const StringContainer *string, unsigned int *begin) {
    short dots = 0;
    while (*begin < string->size && IsNumeric(string->value[*begin])) {
        if (string->value[*begin] == '.')
            dots++;
        (*begin)++;
    }
    if (dots <= 1)
        return CreateElement(kNumeric);
    return NULL;
}

JsonElement *HandleBool(const StringContainer *string, unsigned int *begin) {
    char first_letter = string->value[*begin];
    if (first_letter == 't') {
        if ((*begin) + 4 >= string->size)
            return NULL;
        if (strncmp((string->value + *begin), "true", 4) == 0) {
            (*begin) += 4;
            return CreateElement(kBool);
        }
        return NULL;
    } else if (first_letter == 'f') {
        if ((*begin) + 5 >= string->size)
            return NULL;
        if (strncmp((string->value + *begin), "false", 5) == 0) {
            (*begin) += 5;
            return CreateElement(kBool);
        }
        return NULL;
    } else
        return NULL;
}

JsonElement *HandleNull(const StringContainer *string, unsigned int *begin) {
    if ((*begin) + 4 >= string->size)
        return NULL;
    if (strncmp((string->value + *begin), "null", 4) == 0) {
        (*begin) += 4;
        return CreateElement(kNull);
    }
    return NULL;
}
