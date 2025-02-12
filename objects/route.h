//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef ROUTE_H
#define ROUTE_H

#include "dictionary.h"

/* STRUCT */

/*
 * represents a route with all it's waypoints
 */
typedef struct Route {
    WAYPOINT *waypoints;
    int length;
} ROUTE = {.waypoints = {}, .length = 0};

/* FUNCTIONS */

/*
 * Appends a single waypoint to the given route
 */
void append_to_route(ROUTE *route, WAYPOINT waypoint);

/*
 * Returns the complete distance in the route
 */
int get_distance(const ROUTE *route);

/*
 * Prints the route to the console with all it's waypoints and distance
 */
void print_route(const ROUTE *route);

/*
 * Frees the memory of the struct route, and it's allocated memory spots
 */
void free_route(ROUTE *route);

#endif //ROUTE_H
