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
 */
int dijkstra(
    const DICTIONARY* dict,
    const char* start,
    const char* target,
    bool debug
    );

#endif //ALGO_H
