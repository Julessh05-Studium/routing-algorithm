//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef ALGO_H
#define ALGO_H

#include "objects/dictionary.h"
#include "objects/route.h"

void dijkstra(
    DICTIONARY *dict,
    const char *start,
    const char *target,
    ROUTE *route
);

/* OPTIONAL */
// void a_star();

#endif //ALGO_H
