//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

/* STRUCTS */

typedef struct City {
    char *name;
    int id;
    bool visited;
} CITY = {.visited = false};

typedef struct Waypoint {
    CITY city;
    CITY destination;
    int distance;
} WAYPOINT = {.distance = 0};

typedef struct Value {
    int size;
    WAYPOINT *waypoints;
} VALUE = {.waypoints = {}, .size = 0};

typedef struct Dictionary {
    int size;
    CITY keys[];
    VALUE values[];
} DICTIONARY = {.keys = {}, .values = {}, .size = 0};

/* FUNCTIONS */

// VALUE FUNCTIONS

WAYPOINT get_nearest(VALUE value, DICTIONARY *dict);

// DICTIONARY FUNCTIONS

void add_to_dictionary(DICTIONARY *dict, const CITY key, const VALUE value);

CITY *get_key(DICTIONARY *dict, const char *city);

VALUE *get(DICTIONARY *dict, const char *city);

void free_dict_mem(DICTIONARY *dict);


#endif //DICTIONARY_H
