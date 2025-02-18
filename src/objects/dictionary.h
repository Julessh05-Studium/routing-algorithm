//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H


/* STRUCTS */

/**
 * struct representing a single city
 */
typedef struct {
    char *name;
    int id;
    bool visited;
} CITY;

/**
 * struct representing a waypoint, which includes a start city,
 * the destination and the distance between those two
 */
typedef struct {
    CITY city;
    CITY destination;
    int distance;
} WAYPOINT;

/**
 * A value represents an array of waypoints in a dictionary
 */
typedef struct {
    int size;
    WAYPOINT *waypoints;
} VALUE;

/**
 * The global struct holding all values the algorithm needs
 */
typedef struct {
    int size;
    CITY *keys;
    VALUE **values;
} DICTIONARY;

/* FUNCTIONS */

// VALUE FUNCTIONS

/**
 * Returns the waypoint with the smallest distance in the array of the passed value.
 * Passing a specific value implicitly means searching for the nearest waypoint to the city which has been the key to the passed value.
 */
WAYPOINT get_nearest(const VALUE value, const DICTIONARY *dict);

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

/**
 * Adds a waypoint to the Value waypoints array.
 * This function reallocates memory, which can lead to memory loss.
 * Please check the return value and free memory if reallocation fails.
 *
 * @param value value with waypoints array to add waypoint to
 * @param waypoint waypoint to add.
 * @return true if action succeeded, false otherwise.
 */
bool add(VALUE *value, const WAYPOINT waypoint);

// DICTIONARY FUNCTIONS

/**
 * Appends a new entry with key and value to the passed dictionary
 */
bool add_to_dictionary(DICTIONARY *dict, const CITY *key, VALUE *value);

/**
 * Returns the city struct for a specific city name in the given dictionary
 */
CITY *get_key(const DICTIONARY *dict, const char *city);

/**
 * Returns the value for a passed city name
 */
VALUE *get_value(const DICTIONARY *dict, const char *city);

/**
 * Frees the memory of the dictionary
 */
void free_dict_mem(DICTIONARY *dict);


#endif //DICTIONARY_H
