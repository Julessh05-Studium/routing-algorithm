#include <stdio.h>
#include <_stdlib.h>
#include <string.h>

#include "logic/algo.h"

#include "objects/dictionary.h"
#include "parsing/parser.h"

#define MAP_LONG "--map"
#define MAP_SHORT "-m"
#define START_LONG "--start"
#define START_SHORT "-s"
#define TARGET_LONG "--target"
#define TARGET_SHORT "-t"

int main(int argc, char *argv[]) {
    DICTIONARY *dictionary;
    char *start;
    char *target;

    for (int i = 1; i < argc; ++i) {
        //printf(argv[i]);
        if (strcmp(argv[i], MAP_LONG) == 0 || strcmp(argv[i], MAP_SHORT) == 0) {
            char *path = argv[i + 1];
            if (path == NULL) {
                return EXIT_FAILURE;
            }
            dictionary = parse(path);
            // dict_out(dictionary);
            i++;
        }
        if (strcmp(argv[i], START_LONG) == 0 || strcmp(argv[i], START_SHORT) == 0) {
            start = argv[i + 1];
            if (start == NULL) {
                return EXIT_FAILURE;
            }
            i++;
        }
        if (strcmp(argv[i], MAP_LONG) == 0 || strcmp(argv[i], MAP_SHORT) == 0) {
            target = argv[i + 1];
            if (target == NULL) {
                return EXIT_FAILURE;
            }
            i++;
        }
    }

    dijkstra(dictionary, start, target);
    return EXIT_SUCCESS;
}
