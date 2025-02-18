#include <stdio.h>
#include <_stdlib.h>
#include <string.h>

#include "logic/algo.h"

#include "objects/dictionary.h"
#include "parsing/parser.h"

#define MAP_LONG "--map"
#define MAP_SHORT "-m"

int main(int argc, char *argv[]) {
    DICTIONARY *dictionary;

    for (int i = 1; i < argc; ++i) {
        printf(argv[i]);
        if (strcmp(argv[i], MAP_LONG) == 0 || strcmp(argv[i], MAP_SHORT) == 0) {
            char *path = argv[i + 1];
            if (path == NULL) {
                return EXIT_FAILURE;
            }
            dictionary = parse(path);
            // dict_out(dictionary);
            i++;
        }
    }
    DICTIONARY dict = {};
    CITY *cities = malloc(sizeof(CITY) * 3);
    CITY c = {.name = "Stuttgart"};
    cities[0] = c;
    c.name = "Berlin";
    cities[1] = c;
    c.name = "München";
    cities[2] = c;
    dict.keys = cities;

    VALUE *values = malloc(sizeof(VALUE) * 3);
    WAYPOINT *w_s = malloc(sizeof(WAYPOINT));

    c.name = "Stuttgart";
    CITY ds = {.name = "München"};
    WAYPOINT ws = {.city = c, .distance = 100, .destination = ds};
    w_s[0] = ws;
    VALUE vs = {.waypoints = w_s};
    values[0] = vs;

    c.name = "Berlin";
    CITY db = {.name = "München"};
    WAYPOINT wb = {.city = c, .distance = 100, .destination = db};
    w_s[0] = wb;
    VALUE vb = {.waypoints = w_s};
    values[1] = vb;

    c.name = "München";
    CITY dm = {.name = "Berlin"};
    WAYPOINT wm = {.city = c, .distance = 100, .destination = dm};
    w_s[0] = wm;
    VALUE vm = {.waypoints = w_s};
    values[2] = vm;
    dict.values = values;

    dijkstra(&dict, "Stuttgart", "Berlin");

    free(w_s);
    free(cities);
    free(values);
    return EXIT_SUCCESS;
}
