cmake_minimum_required(VERSION 3.30)
project(routing_algorithm C)

set(CMAKE_C_STANDARD 23)

add_executable(routing_algorithm src/main.c
        src/objects/dictionary.h
        src/logic/algo.c
        src/logic/algo.h
        src/objects/route.h
        src/objects/dictionary.c
        src/objects/route.c)
