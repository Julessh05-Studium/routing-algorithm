//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef ROUTE_H
#define ROUTE_H

#include "dictionary.h"

/* STRUCT */

/**
 * represents a route with all it's waypoints
 */
typedef struct Route {
    CITY destination;
    WAYPOINT *waypoints;
    int length;
} ROUTE = {.waypoints = {}, .length = 0};

/* FUNCTIONS */

/**
 * Appends a single waypoint to the given route
 * @param route the route to append something to
 * @param waypoint the waypoint to append to the route
 */
void append_to_route(ROUTE *route, WAYPOINT waypoint);

/**
 * Returns the complete distance in the route
 * @param route the route to calculate the distance for
 * @return the distance as int
 */
int get_distance(const ROUTE *route);

/**
 * Prints the route to the console with all it's waypoints and distance
 * @param route the route to print out to the console
 */
void print_route(const ROUTE *route);

/**
 * Returns the last parameter of the route
 * @param route the route to search for the last parameter in
 * @return the last parameter of the input route
 */
WAYPOINT *get_last_eof(const ROUTE *route);

/**
 * Frees the memory of the struct route, and it's allocated memory spots
 * @param route the route to free memory from
 */
void free_route(ROUTE *route);

#endif //ROUTE_H
