//
// Created by Julian Schumacher on 08.02.25.
//

#include "dictionary.h"

#include <stdlib.h>
#include <string.h>

/* VALUE FUNCTIONS */

bool connection_in_values(const VALUE *val, const CONNECTION *connection) {
  if (val == nullptr || connection == nullptr) {
    return true;
  }

  for (int i = 0; i < val->size; ++i) {
    const CONNECTION *tmp = &val->connections[i];
    if (strcmp(tmp->destination.name, connection->destination.name) == 0) {
      return true;
    }
  }

  return false;
}

CONNECTION get_nearest(const VALUE value, const DICTIONARY* dict) {
  int smallest_distance = -1;
  CONNECTION result = {};
  for (int i = 0; i < value.size; ++i) {
    const CONNECTION current_connection = value.connections[i];
    if (smallest_distance == -1) {
      smallest_distance = current_connection.distance;
    }
    if (current_connection.distance < smallest_distance && get_key(
            dict, current_connection.city.name)->visited) {
      smallest_distance = current_connection.distance;
      result = current_connection;
    }
  }
  return result;
}

bool add(VALUE* value, const CONNECTION connection) {
  CONNECTION* tmp =
      realloc(value->connections, sizeof(CONNECTION) * (value->size + 1));
  if (tmp == nullptr) {
    return false;
  }
  value->connections = tmp;
  value->connections[value->size] = connection;
  value->size += 1;
  return true;
}

bool remove_from_val(VALUE value, const char* city) {
  bool removed = false;
  CONNECTION* new_connections = malloc(sizeof(CONNECTION) * value.size - 1);
  int j = 0;
  for (int i = 0; i < value.size - 1; ++i) {
    if (value.connections[j].city.name != city) {
      new_connections[i] = value.connections[j];
    } else {
      i--;
      removed = true;
    }
    j++;
  }
  free(value.connections);
  value.connections = new_connections;
  value.size--;
  return removed;
}

bool remove_from_dict(DICTIONARY* dict, const char* city) {
  bool removed = false;
  CITY* new_cities = malloc(sizeof(CITY) * dict->size - 1);
  VALUE** new_values = malloc(sizeof(VALUE) * dict->size - 1);
  int j = 0;
  for (int i = 0; i < dict->size - 1; ++i) {
    if (dict->keys[j].name != city) {
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

bool add_to_dictionary(DICTIONARY* dict, const CITY* key, VALUE* value) {
  const int size = dict->size;

  CITY* tmp_city = realloc(dict->keys, sizeof(*dict->keys) * (size + 1));
  if (tmp_city == nullptr) {
    return false;
  }
  dict->keys = tmp_city;

  VALUE** tmp_values = realloc(dict->values, sizeof(VALUE**) * (size + 1));
  if (tmp_values == nullptr) {
    free(tmp_city);
    return false;
  }
  dict->values = tmp_values;

  dict->keys[size] = *key;
  dict->values[size] = value;
  dict->size++;
  return true;
}

CITY* get_key(const DICTIONARY* dict, const char* city) {
  for (int i = 0; i < dict->size; ++i) {
    if (strcmp(city, dict->keys[i].name)) {
      return &dict->keys[i];
    }
  }
  return nullptr;
}

VALUE* get_value(const DICTIONARY* dict, const char* city) {
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

void free_dict_mem(DICTIONARY* dict) {
  free(dict->keys);
  free(dict->values);
  dict->size = 0;
}
