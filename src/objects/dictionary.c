//
// Created by Julian Schumacher on 08.02.25.
//

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

bool add(VALUE *value, const WAYPOINT waypoint) {
    WAYPOINT *tmp =
            realloc(value->waypoints, sizeof(WAYPOINT) * (value->size + 1));
    if (tmp == NULL) {
        return false;
    }
    value->waypoints = tmp;
    value->waypoints[value->size] = waypoint;
    value->size += 1;
    return true;
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

bool add_to_dictionary(DICTIONARY *dict, CITY *key, VALUE *value) {
    const int size = dict->size;

    CITY *tmp_city = realloc(dict->keys, sizeof(*dict->keys) * (size + 1));
    if (tmp_city == NULL) {
        return false;
    }
    dict->keys = tmp_city;

    VALUE **tmp_values = realloc(dict->values, sizeof(VALUE **) * (size + 1));
    if (tmp_values == NULL) {
        free(tmp_city);
        return false;
    }
    dict->values = tmp_values;

    dict->keys[size] = *key;
    dict->values[size] = value;
    dict->size++;
    return true;
}

CITY *get_key(const DICTIONARY *dict, const char *city) {
    for (int i = 0; i < dict->size; ++i) {
        if (city == dict->keys[i]->name) {
            return dict->keys[i];
        }
    }
    return nullptr;
}

VALUE *get_value(const DICTIONARY *dict, const char *city) {
    if (dict == nullptr || city == nullptr) {
        return nullptr;
    }
    for (int i = 0; i < dict->size; ++i) {
        if (strcmp(city, dict->keys[i].name) == 0) {
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
