//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef ALGO_H
#define ALGO_H

#include <stdbool.h>

#include "../objects/dictionary.h"

/**
 * The base pathfinding algorithm
 * dict is a dictionary of all connections,
 * start is the name of the city, the user wants to start in,
 * target is the algorithm's destination
 *
 * @param dict the dictionary with all cities
 * @param start the start city
 * @param target the destination city
 * @param debug whether to enable debug mode
 * @param complete_route the complete route string for routes with waypoints
 * @return distance calculated
 */
int dijkstra(
    const DICTIONARY* dict,
    const char* start,
    const char* target,
    bool debug,
    char** complete_route
    );

#endif //ALGO_H
