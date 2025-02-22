//
// Created by Julian Schumacher on 05.02.25.
//

#include "algo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../objects/route.h"

/**
 * Searches for the specified city in the provided array and performs a lookup on the visited parameter.
 * @param city the city to return the visited parameter for
 * @param cities the city array which contains the cities and information about the visitations
 * @param city_size the size of the array to search in
 * @return the boolean if the city has been visited or not
 */
bool city_visited(const char* city, const CITY* cities, const int city_size) {
  for (int i = 0; i < city_size; i++) {
    if (strcmp(city, cities[i].name) == 0) {
      return cities[i].visited;
    }
  }
  return false;
}

/**
 * Checks for all cities passed in the cities array, if they already have been visited
 * @param cities The array of cities to check the visited parameter for
 * @param city_size the size of the passed array
 * @return whether all cities have been visited
 */
bool all_cities_visited(const CITY* cities, const int city_size) {
  for (int i = 0; i < city_size; i++) {
    if (!city_visited(cities[i].name, cities, city_size)) {
      return false;
    }
  }
  return true;
}

/**
 * Returns a pointer to the route with the smallest distance in an array passed as a pointer.
 * @param routes pointer to the array start of routes to get the element from
 * @param size the size of the array to read from
 * @param applicable_cities the array which contains all the cities applicable for this run of the algorithm
 * @param cities_size the size of the cities array
 * @return pointer to the route with the shortest distance
 */
ROUTE* get_route_min_dist(ROUTE* routes, const int size,
                          const CITY* applicable_cities,
                          const int cities_size) {
  int min_distance = -1;
  ROUTE* route = nullptr;
  for (int i = 0; i < size; i++) {
    if (min_distance < 0 && !city_visited(routes[i].destination.name,
                                          applicable_cities,
                                          cities_size) ||
        routes[i].distance > 0 && routes[i].distance < min_distance &&
        !city_visited(routes[i].destination.name, applicable_cities,
                      cities_size)) {
      min_distance = routes[i].distance;
      route = &routes[i];
    }
  }
  return route;
}

/**
 * Returns the route for the specified city name
 * @param routes the array, or a pointer to the array start, of routes to search in
 * @param size the size of the array to prevent segmentation faults
 * @param name the city name to be searched for
 * @return a pointer to the city with the specified name
 */
ROUTE* get_route_for_city(ROUTE* routes, const int size, const char* name) {
  for (int i = 0; i < size; i++) {
    if (strcmp(routes[i].destination.name, name) == 0) {
      return &routes[i];
    }
  }
  return nullptr;
}

int dijkstra(
    const DICTIONARY* dict,
    const char* start,
    const char* target,
    const bool debug
    ) {
  // constant var for dictionary size
  const int DICT_SIZE = dict->size;
  // Copy cities to working array
  CITY* all_cities = malloc(sizeof(CITY) * DICT_SIZE);
  for (int i = 0; i < DICT_SIZE; i++) {
    all_cities[i] = dict->keys[i];
  }

  // Create routes array for all routes
  ROUTE* routes = malloc(sizeof(ROUTE) * DICT_SIZE);

  // Create a single route for every city
  // TODO-js: extract function
  for (int i = 0; i < DICT_SIZE; i++) {
    ROUTE* route = malloc(sizeof(ROUTE));
    route->destination = all_cities[i];
    route->connections = malloc(sizeof(CONNECTION));
    // set length to 0 if start and -1 if undefined
    if (strcmp(all_cities[i].name, start) == 0) {
      route->distance = 0;
    } else {
      route->distance = -1;
    }
    // Add route to routes
    routes[i] = *route;
  }

  // For every city that is not yet calculated fully
  while (!all_cities_visited(all_cities, DICT_SIZE)) {
    // Get connection with the smallest distance to
    const ROUTE* shortest_route = get_route_min_dist(
        routes, DICT_SIZE, all_cities,
        DICT_SIZE);
    const CITY sr_destination = shortest_route->destination;
    const VALUE* value = get_value(dict, sr_destination.name);
    const CONNECTION* neighbors = value->connections;
    for (int i = 0; i < value->size; i++) {
      const int tmp_length = neighbors[i].distance + shortest_route->distance;
      ROUTE* current_route = get_route_for_city(routes, DICT_SIZE,
                                                neighbors[i].destination.name);
      // Set new length, if either is not set, or is greater
      if (current_route->distance < 0 || current_route->distance > tmp_length) {
        ROUTE* route = malloc(sizeof(ROUTE));
        for (int j = 0; j < shortest_route->length; j++) {
          append_to_route(route, shortest_route->connections[j]);
        }
        append_to_route(route, neighbors[i]);
        current_route->connections = route->connections;
        current_route->distance = tmp_length;
        current_route->length = route->length;
        if (debug) {
          print_route(current_route, start);
        }
      }
    }

    // Restructure array and mark current city as visited
    for (int j = 0; j < DICT_SIZE; j++) {
      if (strcmp(all_cities[j].name, sr_destination.name) == 0) {
        all_cities[j].visited = true;
      }
    }
  }

  // Print route to target
  const ROUTE* target_route = get_route_for_city(routes, DICT_SIZE, target);
  printf("Target %s reached:\n", target);
  print_route(target_route, start);
  const int distance = target_route->distance;

  // Free mem
  for (int i = 0; i < DICT_SIZE; i++) {
    free_route(&routes[i]);
  }
  free(routes);
  free(all_cities);
  return distance;
}
