//
// Created by Julian Schumacher on 08.02.25.
//

#include "dictionary.h"

#include <stdlib.h>

/* VALUE FUNCTIONS */


WAYPOINT get_nearest(const VALUE value, DICTIONARY *dict) {
    int smallest_distance = -1;
    WAYPOINT res = {};
    for (int i = 0; i < value.size; ++i) {
        const WAYPOINT current_waypoint = value.waypoints[i];
        if (smallest_distance == -1) {
            smallest_distance = current_waypoint.distance;
        }
        if (current_waypoint.distance < smallest_distance && get_key(dict, current_waypoint.city.name)->visited) {
            smallest_distance = current_waypoint.distance;
            res = current_waypoint;
        }
    }
    return res;
}

bool remove_from_val(VALUE value, const char *city) {
    bool removed = false;
    WAYPOINT *new_waypoints = malloc(sizeof(WAYPOINT) * value.size - 1);
    int j = 0;
    for (int i = 0; i < value.size - 1; ++i) {
        if (value.waypoints[j].city.name != city) {
            new_waypoints[i] = value.waypoints[j];
        } else {
            i--;
            removed = true;
        }
        j++;
    }
    free(value.waypoints);
    value.waypoints = new_waypoints;
    value.size--;
    return removed;
}

bool remove_from_dict(DICTIONARY *dict, const char *city) {
    bool removed = false;
    CITY **new_cities = malloc(sizeof(CITY) * dict->size - 1);
    VALUE **new_values = malloc(sizeof(VALUE) * dict->size - 1);
    int j = 0;
    for (int i = 0; i < dict->size - 1; ++i) {
        if (dict->keys[j]->name != city) {
            new_cities[i] = dict->keys[j];
            new_values[i] = dict->values[j];
        } else {
            i--;
            removed = true;
        }
        j++;
    }
    free_dict_mem(dict);
    dict->size = j;
    dict->keys = new_cities;
    dict->values = new_values;
    return removed;
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

CITY *get_key(const DICTIONARY *dict, const char *city) {
    for (int i = 0; i < dict->size; ++i) {
        if (city == dict->keys[i]->name) {
            return dict->keys[i];
        }
    }
    return nullptr;
}

VALUE *get(const DICTIONARY *dict, const char *city) {
    for (int i = 0; i < dict->size; ++i) {
        if (city == dict->keys[i]->name) {
            return dict->values[i];
        }
    }
    return nullptr;
}

void free_dict_mem(DICTIONARY *dict) {
    free(dict->keys);
    free(dict->values);
    dict->size = 0;
}
