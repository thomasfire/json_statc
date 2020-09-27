//
// Created by thomasf on 2020/09/25.
//

#include "file_serializer.h"

#include <stdio.h>

/*!
 Написать утилиту на языке C без использования внешних библиотек,
 которая на вход будет получать путь до файла с данными в формате JSON и анализировать их.
 В результате утилита должна вывести метрику: количество используемых типов данных для каждого вложенного объекта,
 включая корневой; уровень каждого вложенного объекта относительно корневого.
 Дополнительно утилита должна распечатать ключ самого глубокого объекта относительно корневого.
 В случае невалидности JSON утилита выводит ошибку.
*/

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: $ json_statc path/to/file\n");
        return 0;
    }

    const char *filename = argv[1];
    ReadResult result;
    JsonElement *root = GetRootFromFile(filename, &result);
    if (!root) {
        switch (result) {
            case kReadOk:
                printf("Hmm, here is bug in the code\n");
                break;
            case kReadEmpty:
                printf("The file is empty\n");
                break;
            case kReadFailure:
                printf("Couldn't read the file.\n");
                break;
            case kParseFailure:
                printf("Invalid JSON.\n");
                break;
            default:
                printf("We do not know what has happened\n");
        }
        return 0;
    }
    PrintStatistics(root);
    DeleteJsonElement(root);

    return 0;
}