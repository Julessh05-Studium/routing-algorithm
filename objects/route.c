//
// Created by Julian Schumacher on 08.02.25.
//

#include "route.h"
#include <stdlib.h>

void append_to_route(ROUTE *route, const WAYPOINT waypoint) {
    realloc(route->waypoints, sizeof(WAYPOINT) * (route->length + 1));
    route->waypoints[route->length] = waypoint;
    route->length++;
}

int get_distance(const ROUTE *route) {
    int res = 0;
    for (int i = 0; i < route->length; i++) {
        res += route->waypoints[i].distance;
    }
    return res;
}

void print_route(const ROUTE *route) {
    for (int i = 0; i < route->length; i++) {
        printf("%s ", route->waypoints[i].destination.name);
        if (i != route->length - 1) {
            printf("-> \n");
        } else {
            printf("\n");
        }
    }
    printf("Total distance: %dkm\n", get_distance(route));
}

void free_route(ROUTE *route) {
    free(route->waypoints);
    route->length = 0;
    free(route);
}
