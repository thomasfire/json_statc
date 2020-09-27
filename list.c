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

List *PreviousNList(List *list_ptr, unsigned int n) {
    List *buff_ptr = list_ptr;
    for (unsigned int i = 0; i < n; i++) {
        if (!buff_ptr)
            return NULL;
        buff_ptr = buff_ptr->previous;
    }
    return buff_ptr;
}

List *PushToList(List *list_ptr, void *value, unsigned int size) {
    List *buffer = (List *) calloc(1, sizeof(List));
    if (!buffer)
        return NULL;

    buffer->value = value;
    buffer->size = size;
    if (list_ptr)
        list_ptr->next = buffer;
    buffer->previous = list_ptr;
    return buffer;
}


List *DeleteFromList(List *list_ptr, void deleter(void *ptr)) {
    if (!list_ptr)
        return NULL;
    List *prev = list_ptr->previous;
    List *next = list_ptr->next;
    if (prev)
        prev->next = next;
    if (next)
        next->previous = prev;
    deleter(list_ptr);

    if (prev)
        return prev;
    if (next)
        return next;
    return NULL;
}

void EraseAllPrevList(List *list_ptr, void deleter(void *ptr)) {
    if (!list_ptr)
        return;
    if (list_ptr->previous)
        EraseAllPrevList(list_ptr->previous, deleter);
    deleter(list_ptr->value);
    free(list_ptr);
}

void EraseAllNextList(List *list_ptr, void deleter(void *ptr)) {
    if (!list_ptr)
        return;
    if (list_ptr->next)
        EraseAllNextList(list_ptr->next, deleter);
    deleter(list_ptr->value);
    free(list_ptr);
}

void EraseList(List *list_ptr, void deleter(void *ptr)) {
    if (!list_ptr)
        return;
    EraseAllPrevList(list_ptr->previous, deleter);
    EraseAllNextList(list_ptr->next, deleter);
    deleter(list_ptr->value);
    free(list_ptr);
}