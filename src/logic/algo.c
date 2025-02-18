//
// Created by Julian Schumacher on 05.02.25.
//

#include "algo.h"

#include <stdio.h>
#include <stdlib.h>
#include "../objects/route.h"

/**
 * Returns a pointer to the route with the smallest distance in an array passed as a pointer.
 * @param routes pointer to the array start of routes to get the element from
 * @param size the size of the array to read from
 * @return pointer to the route with the shortest distance
 */
ROUTE *get_route_min_dist(ROUTE *routes, const int size) {
    int min = -1;
    ROUTE *r = nullptr;
    for (int i = 0; i < size; i++) {
        if (min < 0 || routes[i].length > 0 && routes[i].length < min) {
            min = routes[i].length;
            r = &routes[i];
        }
    }
    return r;
}

/**
 * Returns the route for the specified city name
 * @param routes the array, or a pointer to the array start, of routes to search in
 * @param size the size of the array to prevent segmentation faults
 * @param name the city name to be searched for
 * @return a pointer to the city with the specified name
 */
ROUTE *get_route_for_city(ROUTE *routes, const int size, const char *name) {
    ROUTE *r = nullptr;
    for (int i = 0; i < size; i++) {
        if (routes[i].destination.name == name) {
            r = &routes[i];
        }
    }
    return r;
}

void dijkstra(
    const DICTIONARY *dict,
    const char *start,
    const char *target
) {
    const int DICT_SIZE = dict->size;
    // Copy cities to array
    CITY *all_cities = malloc(sizeof(CITY) * DICT_SIZE);
    int all_cities_size = 0;
    for (; all_cities_size < DICT_SIZE; all_cities_size++) {
        all_cities[all_cities_size] = *dict->keys[all_cities_size];
    }

    // Create routes array for all routes
    ROUTE *routes = malloc(sizeof(ROUTE) * all_cities_size);

    for (int i = 0; i < all_cities_size; i++) {
        // create route to every city
        ROUTE *route = malloc(sizeof(ROUTE));
        route->destination = all_cities[i];
        // set length to 0 if start and -1 if undefined
        if (all_cities[i].name == start) {
            route->length = 0;
        } else {
            route->length = -1;
        }
        // TODO: malloc
        routes[i] = *route;
    }

    const WAYPOINT *start_neighbors = get(dict, start)->waypoints;
    for (int i = 0; i < get(dict, start)->size; i++) {
        // Calculate distance to every neighbor of start
        ROUTE *r = get_route_for_city(routes, DICT_SIZE, start_neighbors[i].destination.name);
        r->length = start_neighbors[i].distance;

        // Restructure array and remove start city
        const CITY *tmp = all_cities;
        CITY *tmp_p = realloc(all_cities, sizeof(CITY) * --all_cities_size);
        all_cities = tmp_p;
        int k = 0;
        for (int j = 1; j < all_cities_size; j++) {
            if (all_cities[j].name == start) {
                j--;
            } else {
                all_cities[j] = tmp[k];
            }
            k++;
        }
    }

    // For every city that is not yet calculated fully
    while (all_cities != nullptr) {
        // Get waypoint with the smallest distance to
        const ROUTE *sr = get_route_min_dist(routes, DICT_SIZE);
        const CITY sr_dest = sr->destination;
        const VALUE *v = get(dict, sr_dest.name);
        const WAYPOINT *neighbors = v->waypoints;
        for (int i = 0; i < v->size; i++) {
            const int tmp_l = neighbors[i].distance + sr->length;
            ROUTE *cr = get_route_for_city(routes, DICT_SIZE, sr_dest.name);
            // Set new length, if either is not set, or is greater
            if (cr->length < 0 || cr->length > tmp_l) {
                cr->length = tmp_l;
            }
        }

        // Restructure array and remove current city
        const CITY *tmp = all_cities;
        CITY *tmp_p = realloc(all_cities, sizeof(CITY) * --all_cities_size);
        all_cities = tmp_p;
        int k = 0;
        for (int j = 1; j < all_cities_size; j++) {
            if (all_cities[j].name == sr_dest.name) {
                j--;
            } else {
                all_cities[j] = tmp[k];
            }
            k++;
        }
    }

    // Print route to target
    const ROUTE *target_route = get_route_for_city(routes, DICT_SIZE, target);
    printf("Target %s reached:", target);
    print_route(target_route);

    // Free mem
    for (int i = 0; i < DICT_SIZE; i++) {
        free_route(&routes[i]);
    }
    free(routes);
    free(all_cities);
}
