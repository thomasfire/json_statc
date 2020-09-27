//
// Created by thomasf on 2020/09/25.
//

#pragma once

#include <stdbool.h>


bool IsWhitespace(char symbol);

bool IsNumeric(char symbol);

bool IsNullBegin(char symbol);

bool IsBoolBegin(char symbol);

bool IsCorrectEscape(char symbol1, char symbol2);

