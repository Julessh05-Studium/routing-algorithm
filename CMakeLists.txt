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
add_executable(routing_algorithm src/main.c
        src/objects/dictionary.h
        src/logic/algo.c
        src/logic/algo.h
        src/objects/route.h
        src/objects/dictionary.c
        src/objects/route.c)
