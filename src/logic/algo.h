//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef ALGO_H
#define ALGO_H

#include "../objects/dictionary.h"

/**
 * The base pathfinding algorithm
 * dict is a dictionary of all waypoints,
 * start is the name of the city, the user wants to start in,
 * target is the algorithm's destination
 */
void dijkstra(
    const DICTIONARY *dict,
    const char *start,
    const char *target,
    bool debug
);

/* OPTIONAL */
// void a_star();

#endif //ALGO_H
