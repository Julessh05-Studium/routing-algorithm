#include <stdio.h>
#include <_stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logic/algo.h"

#include "objects/dictionary.h"
#include "parsing/parser.h"

#define MAP_LONG "--map"
#define MAP_SHORT "-m"
#define START_LONG "--start"
#define START_SHORT "-s"
#define TARGET_LONG "--target"
#define TARGET_SHORT "-t"
#define DEBUG_LONG "--debug"
#define DEBUG_SHORT "-d"

int main(int argc, char *argv[]) {
    DICTIONARY *dictionary;
    char *start;
    char *target;
    bool map_given = false;
    bool start_given = false;
    bool target_given = false;
    bool debug = false;

    for (int i = 1; i < argc; ++i) {
        //printf(argv[i]);
        if (strcmp(argv[i], MAP_LONG) == 0 || strcmp(argv[i], MAP_SHORT) == 0) {
            map_given = true;
            char *path = argv[i + 1];
            if (path == NULL || strcmp(path, "") == 0) {
                fprintf(stderr, "a valid path has to be passed.");
                return EXIT_FAILURE;
            }
            if (path[0] != '/') {
                char *tmp_path = malloc(sizeof(char) * 200);
                if (getcwd(tmp_path, 200) == NULL) {
                    fprintf(stderr, "failed to get current working directory.\n");
                    return EXIT_FAILURE;
                }
                char *pws = malloc(sizeof(char) * 200);
                strcpy(pws, "/");
                strcat(pws, path);
                strcat(tmp_path, pws);
                free(pws);
            }
            dictionary = parse(path);
            // dict_out(dictionary);
            i++;
        }
        if (strcmp(argv[i], START_LONG) == 0 || strcmp(argv[i], START_SHORT) == 0) {
            start_given = true;
            start = argv[i + 1];
            if (start == NULL) {
                fprintf(stderr, "a valid start name has to be passed.");
                return EXIT_FAILURE;
            }
            i++;
        }
        if (strcmp(argv[i], TARGET_LONG) == 0 || strcmp(argv[i], TARGET_SHORT) == 0) {
            target_given = true;
            target = argv[i + 1];
            if (target == NULL) {
                fprintf(stderr, "a valid target name has to be passed.");
                return EXIT_FAILURE;
            }
            i++;
        }
        if (strcmp(argv[i], TARGET_LONG) == 0 || strcmp(argv[i], TARGET_SHORT) == 0) {
            target = argv[i + 1];
            if (target == NULL) {
                return EXIT_FAILURE;
            }
            i++;
        }
        if (strcmp(argv[i], DEBUG_LONG) == 0 || strcmp(argv[i], DEBUG_SHORT) == 0) {
            debug = true;
        }
    }
    if (!(map_given && start_given && target_given)) {
        fprintf(
            stderr,
            "To run the program, a map, a start and a target have to be passed"
        );
    }

    dijkstra(dictionary, start, target, debug);
    return EXIT_SUCCESS;
}
