//
// Created by thomasf on 2020/09/25.
//

#include "list.h"

#include <stdlib.h>

List *NextNList(List *list_ptr, unsigned int n) {
    List *buff_ptr = list_ptr;
    for (unsigned int i = 0; i < n; i++) {
        if (!buff_ptr)
            return NULL;
        buff_ptr = buff_ptr->next;
    }
    return buff_ptr;
}

List *PushToList(List *list_ptr, void *value) {
    List *buffer = (List *) calloc(1, sizeof(List));
    if (!buffer)
        return NULL;

    buffer->value = value;
    if (list_ptr)
        list_ptr->next = buffer;
    buffer->previous = list_ptr;
    return buffer;
}

void EraseAllPrevList(List *list_ptr, void deleter(void *)) {
    if (!list_ptr)
        return;
    if (list_ptr->previous)
        EraseAllPrevList(list_ptr->previous, deleter);
    deleter(list_ptr->value);
    free(list_ptr);
}

void EraseAllNextList(List *list_ptr, void deleter(void *)) {
    if (!list_ptr)
        return;
    if (list_ptr->next)
        EraseAllNextList(list_ptr->next, deleter);
    deleter(list_ptr->value);
    free(list_ptr);
}

void EraseList(List *list_ptr, void deleter(void *)) {
    if (!list_ptr)
        return;
    EraseAllPrevList(list_ptr->previous, deleter);
    EraseAllNextList(list_ptr->next, deleter);
    deleter(list_ptr->value);
    free(list_ptr);
}