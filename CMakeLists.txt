cmake_minimum_required(VERSION 3.30)
project(routing_algorithm C)

set(CMAKE_C_STANDARD 23)

add_executable(routing_algorithm main.c
        objects/dictionary.h
        algo.c
        algo.h
        objects/route.h
        objects/dictionary.c
        objects/route.c
        parser.c
        out.h
        out.c
)
