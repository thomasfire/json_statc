//
// Created by thomasf on 2020/09/27.
//

#pragma once

#include "string_container.h"
#include "json_elements.h"

JsonElement *HandleElement(const StringContainer *string, unsigned int *begin);

JsonElement *HandleObject(const StringContainer *string, unsigned int *begin);

JsonElement *HandleArray(const StringContainer *string, unsigned int *begin);

JsonElement *HandleString(const StringContainer *string, unsigned int *begin);

JsonElement *HandleNumeric(const StringContainer *string, unsigned int *begin);

JsonElement *HandleBool(const StringContainer *string, unsigned int *begin);

JsonElement *HandleNull(const StringContainer *string, unsigned int *begin);

void HandleSpaces(const StringContainer *string, unsigned int *begin);