//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

/* STRUCTS */

/**
 * struct representing a single city
 */
typedef struct City {
    char *name;
    int id;
    bool visited;
} CITY = {.visited = false};

/**
 * struct representing a waypoint, which includes a start city,
 * the destination and the distance between those two
 */
typedef struct Waypoint {
    CITY city;
    CITY destination;
    int distance;
} WAYPOINT = {.distance = 0};

/**
 * A value represents an array of waypoints in a dictionary
 */
typedef struct Value {
    int size;
    WAYPOINT *waypoints;
} VALUE = {.waypoints = {}, .size = 0};

/**
 * The global struct holding all values the algorithm needs
 */
typedef struct Dictionary {
    int size;
    CITY keys[];
    VALUE values[];
} DICTIONARY = {.keys = {}, .values = {}, .size = 0};

/* FUNCTIONS */

// VALUE FUNCTIONS

/**
 * Returns the waypoint with the smallest distance in the array of the passed value.
 * Passing a specific value implicitly means searching for the nearest waypoint to the city which has been the key to the passed value.
 */
WAYPOINT get_nearest(VALUE value, DICTIONARY *dict);

/**
 * Adds a waypoint to the Value waypoints array.
 * This function reallocates memory, which can lead to memory loss.
 * Please check the return value and free memory if reallocation fails.
 *
 * @param waypoint waypoint to add.
 * @return true if action succeeded, false otherwise.
 */
bool add(const WAYPOINT waypoint);

// DICTIONARY FUNCTIONS

/**
 * Appends a new entry with key and value to the passed dictionary
 */
void add_to_dictionary(DICTIONARY *dict, const CITY key, const VALUE value);

/**
 * Returns the city struct for a specific city name in the given dictionary
 */
CITY *get_key(DICTIONARY *dict, const char *city);

/**
 * Returns the value for a passed city name
 */
VALUE *get(DICTIONARY *dict, const char *city);

/**
 * Frees the memory of the dictionary
 */
void free_dict_mem(DICTIONARY *dict);


#endif //DICTIONARY_H
