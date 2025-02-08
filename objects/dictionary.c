//
// Created by Julian Schumacher on 08.02.25.
//

#include "dictionary.h"

#include <stdlib.h>

/* VALUE FUNCTIONS */

WAYPOINT get_nearest(VALUE value, DICTIONARY *dict) {
    int smallest_distance = -1;
    WAYPOINT res = {};
    for (int i = 0; i < value.size; ++i) {
        WAYPOINT current_waypoint = value.waypoints[i];
        if (smallest_distance == -1) {
            smallest_distance = current_waypoint.distance;
        }
        if (current_waypoint.distance < smallest_distance && dict->get_key(current_waypoint.city.name)->visited) {
            smallest_distance = current_waypoint.distance;
            res = current_waypoint;
        }
    }
    return res;
}

/* DICTIONARY FUNCTIONS */

void add_to_dictionary(DICTIONARY *dict, const CITY key, const VALUE value) {
    const int size = dict->size;
    realloc(dict->keys, sizeof(CITY) * (size + 1));
    dict->keys[size] = key;
    realloc(dict->values, sizeof(struct Value) * (size + 1));
    dict->values[size] = value;
    dict->size++;
}

CITY *get_key(DICTIONARY *dict, const char *city) {
    for (int i = 0; i < dict->size; ++i) {
        if (city == dict->keys[i].name) {
            return &dict->keys[i];
        }
    }
    return nullptr;
}

VALUE *get(DICTIONARY *dict, const char *city) {
    for (int i = 0; i < dict->size; ++i) {
        if (city == dict->keys[i].name) {
            return &dict->values[i];
        }
    }
    return nullptr;
}

void free_dict_mem(DICTIONARY *dict) {
    free(dict->keys);
    free(dict->values);
    dict->size = 0;
    free(dict);
}
