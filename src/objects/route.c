//
// Created by Julian Schumacher on 08.02.25.
//

#include "route.h"

#include <stdio.h>
#include <stdlib.h>

void append_to_route(ROUTE *route, const WAYPOINT waypoint) {
    WAYPOINT *tmp_r;
    if (route->waypoints == nullptr) {
        tmp_r = malloc(sizeof(WAYPOINT) * (route->length + 1));
    } else {
        tmp_r = realloc(route->waypoints, sizeof(WAYPOINT) * (route->length + 1));
    }
    route->waypoints = tmp_r;
    route->waypoints[route->length] = waypoint;
    route->length++;
}

void print_route(const ROUTE *route, const char *start) {
    printf("%s -> ", start);
    for (int i = 0; i < route->length; i++) {
        printf("%s", route->waypoints[i].destination.name);
        if (i != route->length - 1) {
            printf(" -> ");
        } else {
            printf("\n");
        }
    }
    printf("Total distance: %dkm\n", route->distance);
}

WAYPOINT *get_last_eof(const ROUTE *route) {
    return &route->waypoints[route->length - 1];
}


void free_route(ROUTE *route) {
    free(route->waypoints);
    route->length = 0;
}
