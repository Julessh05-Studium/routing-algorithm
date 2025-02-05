//
// Created by Julian Schumacher on 05.02.25.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdlib.h>

typedef struct City {
    char *name;
    int id;
} CITY;

typedef struct Waypoint {
    CITY city;
    CITY destination;
    int distance;
} WAYPOINT;

typedef struct Value {
    int size;
    WAYPOINT *waypoints;

    WAYPOINT get_nearest() const {
        int smallest_distance = -1;
        WAYPOINT res = {};
        for (int i = 0; i < size; ++i) {
            if (smallest_distance == -1) {
                smallest_distance = waypoints[i].distance;
            }
            if (waypoints[i].distance < smallest_distance) {
                smallest_distance = waypoints[i].distance;
                res = waypoints[i];
            }
        }
        return res;
    }
} VALUE;

typedef struct Dictionary {
    int size;
    CITY keys[];
    VALUE values[];

    int get_size() const {
        return size;
    }

    void add(const CITY key, const VALUE value) {
        realloc(keys, sizeof(CITY) * (size + 1));
        keys[size] = key;
        realloc(values, sizeof(struct Value) * (size + 1));
        values[size] = value;
        size++;
    }

    VALUE *get(const char *city) {
        for (int i = 0; i < size; ++i) {
            if (city == keys[i].name) {
                return &values[i];
            }
        }
        return NULL;
    }

    void free_mem() {
        free(keys);
        free(values);
        size = 0;
    }
} GLOBAL_DICTIONARY = {.keys = {}, .values = {}, .size = 0};

#endif //DICTIONARY_H
