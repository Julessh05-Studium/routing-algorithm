//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef ROUTE_H
#define ROUTE_H

#include "dictionary.h"

/* STRUCT */

typedef struct Route {
    WAYPOINT *waypoints;
    int length;
} ROUTE = {.waypoints = {}, .length = 0};

/* FUNCTIONS */

void append_to_route(ROUTE *route, WAYPOINT waypoint);

int get_distance(const ROUTE *route);

void print_route(const ROUTE *route);

void free_route(ROUTE *route);

#endif //ROUTE_H
