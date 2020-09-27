//
// Created by thomasf on 2020/09/25.
//

#pragma once

typedef struct List {
    struct List *previous;
    struct List *next;
    void *value;
    unsigned int size;
} List;

/// nullptr on failure
List *NextNList(List *list_ptr, unsigned int n);

List *PreviousNList(List *list_ptr, unsigned int n);

/// creates new string list if list_ptr is nullptr
List *PushToList(List *list_ptr, void *value, unsigned int size);

/// returns: nullptr if list_ptr is last element in list or is nullptr,
/// previous element if exists,
/// next element if exists and previous doesn't exist
List *DeleteFromList(List *list_ptr, void deleter(void *ptr) );

void EraseList(List * list_ptr, void deleter(void *ptr) );