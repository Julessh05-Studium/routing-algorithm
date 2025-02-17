//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

/* STRUCTS */

/*
 * struct representing a single city
 */
typedef struct City {
    char *name;
    int id;
    bool visited;
} CITY = {.visited = false};

/*
 * struct representing a waypoint, which includes a start city,
 * the destination and the distance between those two
 */
typedef struct Waypoint {
    CITY city;
    CITY destination;
    int distance;
} WAYPOINT = {.distance = 0};

/*
 * A value represents an array of waypoints in a dictionary
 */
typedef struct Value {
    int size;
    WAYPOINT *waypoints;
} VALUE = {.waypoints = {}, .size = 0};

/*
 * The global struct holding all values the algorithm needs
 */
typedef struct Dictionary {
    int size;
    CITY **keys;
    VALUE **values;
} DICTIONARY = {.keys = {}, .values = {}, .size = 0};

/* FUNCTIONS */

// VALUE FUNCTIONS

/*
 * Returns the waypoint with the smallest distance in the array of the passed value.
 * Passing a specific value implicitly means searching for the nearest waypoint to the city which has been the key to the passed value.
 */
WAYPOINT get_nearest(VALUE value, DICTIONARY *dict);

/**
 * Removes a single city, which is specified by the name passed to the function,
 * from the values waypoints
 * @param value Value to remove something from
 * @param city The name of the city removing
 */
bool remove_from_val(VALUE value, const char *city);

/**
 * Removes a single city, which is specified by the name passed to the function,
 * and its asserted values from the dictionary
 * from the dictionary
 * @param dict the dictionary to remove something from
 * @param city The name of the city removing
 */
bool remove_from_dict(DICTIONARY *dict, const char *city);

// DICTIONARY FUNCTIONS

/*
 * Appends a new entry with key and value to the passed dictionary
 */
void add_to_dictionary(DICTIONARY *dict, const CITY key, const VALUE value);

/*
 * Returns the city struct for a specific city name in the given dictionary
 */
CITY *get_key(DICTIONARY *dict, const char *city);

/*
 * Returns the value for a passed city name
 */
VALUE *get(const DICTIONARY *dict, const char *city);

/*
 * Frees the memory of the dictionary
 */
void free_dict_mem(DICTIONARY *dict);


#endif //DICTIONARY_H
