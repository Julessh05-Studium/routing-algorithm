//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef ROUTE_H
#define ROUTE_H

#include "dictionary.h"

/* STRUCT */

/**
 * represents a route with all it's connections
 */
typedef struct Route {
    CITY destination;
    CONNECTION *connections;
    int distance;
    int length;
} ROUTE;

/* FUNCTIONS */

/**
 * Appends a single connection to the given route
 * @param route the route to append something to
 * @param connection the connection to append to the route
 */
void append_to_route(ROUTE *route, CONNECTION connection);

/**
 * Prints the route to the console with all it's connections and distance
 * @param route the route to print out to the console
 * @param start the start point of the route
 */
void print_route(const ROUTE *route, const char *start);

/**
 * Returns the last parameter of the route
 * @param route the route to search for the last parameter in
 * @return the last parameter of the input route
 */
CONNECTION *get_last_eof(const ROUTE *route);

/**
 * Frees the memory of the struct route, and it's allocated memory spots
 * @param route the route to free memory from
 */
void free_route(ROUTE *route);

#endif //ROUTE_H
