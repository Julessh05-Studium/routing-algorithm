cmake_minimum_required(VERSION 3.30)
project(routing_algorithm C)

set(CMAKE_C_STANDARD 23)

add_executable(routing_algorithm
        src/main.c
        src/objects/dictionary.h
        src/objects/dictionary.c
        src/logic/algo.h
        src/logic/algo.c
        src/objects/route.h
        src/objects/route.c
        src/parsing/parser.h
        src/parsing/parser.c
        src/parsing/parser_error_handler.h
        src/parsing/parser_error_handler.c
        src/reallife_application/fuel_consumption.c
        src/reallife_application/fuel_consumption.h
)
