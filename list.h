//
// Created by thomasf on 2020/09/25.
//

#pragma once

typedef struct List {
    struct List *previous;
    struct List *next;
    void *value;
} List;

/// nullptr on failure
List *NextNList(List *list_ptr, unsigned int n);

/// creates new string list if list_ptr is nullptr
List *PushToList(List *list_ptr, void *value);

void EraseList(List *list_ptr, void deleter(void *ptr));