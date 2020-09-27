cmake_minimum_required(VERSION 3.17)
project(json_statc)

set(CMAKE_C_STANDARD 11)

add_executable(json_statc
        main.c
        char_helpers.c
        char_helpers.h
        json_elements.h
        list.c
        list.h
        string_container.c
        string_container.h
        file_serializer.c
        file_serializer.h
        json_handlers.c
        json_handlers.h
        file_reader.c
        file_reader.h
        json_elements.c
)
