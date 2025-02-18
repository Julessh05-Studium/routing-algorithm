//
// Created by gregorgottschewski on 05.02.25.
//

#include "parser.h"

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

int dist;

void init_csv_line() { dist = 0; }

/**
 * Adds the given start and destination with the given distance to the given
 * dictionary.
 *
 * @param dictionary global waypoints dictionary
 * @param start_city start city
 * @param dest_city destination city
 * @param dist distance between start and destination city
 */
bool add_wp_to_dict(DICTIONARY *dictionary, CITY *start_city,
                    const CITY *dest_city, const int dist) {
  if (start_city == NULL || dest_city == NULL) {
    return false;
  }

  VALUE *val = get_value(dictionary, start_city->name);
  if (val == NULL) {
    val = malloc(sizeof(VALUE));
    if (val == NULL) {
      return false;
    }

    val->waypoints = malloc(sizeof(WAYPOINT));
    if (val->waypoints == NULL) {
      return false;
    }
    add_to_dictionary(dictionary, start_city, val);
  }

  add(val,
      (WAYPOINT){
        .city = *start_city, .destination = *dest_city, .distance = dist
      });
  return true;
}

/**
 * Frees given parameters and closes file stream.
 */
void free_mem(FILE *file, char *val) {
  free(val);
  fclose(file);
}

DICTIONARY *parse(char path[]) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    fclose(file);
    return NULL;
  }

  DICTIONARY *dictionary = malloc(sizeof(DICTIONARY));
  if (dictionary == NULL) {
    fclose(file);
    return NULL;
  }

  int c;
  char *val = malloc(32 * sizeof(char));
  if (val == NULL) {
    fclose(file);
    free(dictionary);
    return NULL;
  }

  int buf_size = BUFFER_SIZE;
  int csv_column = 0;
  init_csv_line();
  int i = 0;

  CITY *start_city = malloc(sizeof(CITY));
  CITY *dest_city = malloc(sizeof(CITY));

  while ((c = getc(file)) != EOF) {
    if (i == BUFFER_SIZE - 1) {
      buf_size += BUFFER_SIZE;
      char *tmp = realloc(val, buf_size);
      if (tmp == NULL) {
        free_mem(file, val);
        return NULL;
      }
      val = tmp;
    }

    if (c == '\n') {
      val[i] = '\0';

      char tmp[i + 1];
      strncpy(tmp, val, i);
      tmp[i] = '\0';
      dist = atoi(tmp);

      add_wp_to_dict(dictionary, start_city, dest_city, dist);
      start_city = malloc(sizeof(CITY));
      dest_city = malloc(sizeof(CITY));

      if (start_city == NULL || dest_city == NULL) {
        free_mem(file, val);
        return NULL;
      }

      init_csv_line();
      csv_column = 0;
      i = 0;
      continue;
    }

    if (c == ',') {
      val[i] = '\0';
      switch (csv_column) {
        case 0: {
          start_city->name = malloc(strlen(val) + 1);
          strncpy(start_city->name, val, i);
          start_city->name[strlen(val)] = '\0';
          break;
        }
        case 1:
          dest_city->name = malloc(strlen(val) + 1);
          strncpy(dest_city->name, val, i);
          dest_city->name[strlen(val)] = '\0';
          break;
        default:
          free_mem(file, val);
          return NULL;
      }

      i = 0;
      csv_column++;
      continue;
    }

    val[i++] = c;
  }

  free_mem(file, val);
  return dictionary;
}
