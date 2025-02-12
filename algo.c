//
// Created by Julian Schumacher on 05.02.25.
//

#include "algo.h"
#include <stdio.h>

// TODO-js: take other routes into account, which are shorter in total, but longer in simple steps
void dijkstra(
    DICTIONARY *dict,
    const char *start,
    const char *target
) {
    ROUTE route = {};
    printf("Starting from %s\n", start);
    WAYPOINT w = get_nearest(*get(dict, start), dict);
    CITY current = w.destination;
    current.visited = true;
    append_to_route(&route, w);
    bool reached = false;
    do {
        if (current.name == target) {
            reached = true;
            break;
        }
        w = get_nearest(*get(dict, target), dict);
        current = w.destination;
        current.visited = true;
        append_to_route(&route, w);
    } while (!reached);
    printf("Target %s reached:\n", target);
    print_route(&route);
}
