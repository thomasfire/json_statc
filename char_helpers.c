//
// Created by thomasf on 2020/09/25.
//

#include "char_helpers.h"

#include <ctype.h>


bool IsWhitespace(char symbol) {
    return isspace(symbol);
}

bool IsNumeric(char symbol) {
    return isdigit(symbol) || symbol == '.';
}

bool IsNullBegin(char symbol) {
    return symbol == 'n';
}

bool IsBoolBegin(char symbol) {
    return symbol == 't' || symbol == 'f';
}

bool IsCorrectEscape(char symbol1, char symbol2) {
    if (symbol1 != '\\')
        return false;
    switch (symbol2) {
        case '\\':
        case 'n':
        case 'b':
        case 'f':
        case 'r':
        case 't':
        case '"':
            return true;
        default:
            return false;
    }
}