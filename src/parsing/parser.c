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

int csv_column;
int char_index;
CITY *start_city;
CITY *dest_city;
FILE *map_file;
DICTIONARY *dictionary;

/**
 * Initializes the global variables for parsing a new csv row.
 */
void init_csv_line() {
  csv_column = 0;
  char_index = 0;
}

/**
 * Resets column counter and character counter for reading next line.
 */
void next_row() {
  csv_column++;
  char_index = 0;
}

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
          .city = *start_city, .destination = *dest_city, .distance = dist});
  return true;
}

/**
 * Frees given parameters and closes file stream.
 */
void free_mem(FILE *file, char *val) {
  free(val);
  fclose(file);
}

/**
 * Allocates memory for start and destination city.
 *
 * @return true if malloc was successful, false otherwise
 */
bool malloc_start_dest_city() {
  start_city = malloc(sizeof(CITY));
  if (start_city == NULL) {
    return false;
  }

  dest_city = malloc(sizeof(CITY));
  if (dest_city == NULL) {
    free(start_city);
    return false;
  }

  return true;
}

/**
 * Sets the name of the given city.
 *
 * @param name name of the city
 * @param city city to set the name
 * @return a bool if the name was set successfully
 */
bool set_city_name(const char *name, CITY *city) {
  city->name = malloc(strlen(name) + 1);
  if (city->name == NULL) {
    return false;
  }
  strncpy(city->name, name, char_index);
  city->name[strlen(name)] = '\0';
  return true;
}

/**
 * Converts given string to integer
 * @param val string to convert
 * @return the converted integer
 */
int get_distance_from_str(const char *val) {
  char tmp[char_index + 1];
  strncpy(tmp, val + '\0', char_index);
  tmp[char_index] = '\0';
  return (int) strtoumax(tmp, nullptr, 10);
}

/**
 * Handles a CSV-column seperator character (here: `,` comma).
 *
 * @param current_word
 * @return
 */
bool handle_csv_column(const char *current_word) {
  switch (csv_column) {
    case 0: {
      set_city_name(current_word, start_city);
      break;
    }
    case 1: {
      set_city_name(current_word, dest_city);
      break;
    }
    default: {
      return false;
    }
  }

  return true;
}

/**
 * Initializes the file reader and dictionary.
 *
 * @param path path to file map file.
 * @return a bool if opening file and allocating memory for dictionary succeeded.
 */
bool init_parser(char path[]) {
  map_file = fopen(path, "r");
  if (map_file == NULL) {
    fclose(map_file);
    return false;
  }

  dictionary = malloc(sizeof(DICTIONARY));
  if (dictionary == NULL) {
    fclose(map_file);
    return false;
  }

  return true;
}

/**
 * Parses the map file given by the specified file path.
 * After allocating needed memory and opening file stream,
 * the file is parsed character by character until EOF is reached.
 *
 * @param path absolute path to the file
 * @return a dictionary with data from the map.
 */
DICTIONARY *parse(char path[]) {
  if (!init_parser(path)) {
    return nullptr;
  }

  char *current_word = malloc(32 * sizeof(char));
  if (current_word == NULL || !malloc_start_dest_city()) {
    fclose(map_file);
    free(dictionary);
    return nullptr;
  }

  int buf_size = BUFFER_SIZE;
  init_csv_line();

  while (true) {
    const int current_char = getc(map_file);

    if (char_index == BUFFER_SIZE - 1) {
      buf_size += BUFFER_SIZE;
      char *tmp = realloc(current_word, buf_size);
      if (tmp == NULL) {
        free_mem(map_file, current_word);
        return nullptr;
      }
      current_word = tmp;
    }

    if (current_char == '\n' || current_char == EOF) {
      add_wp_to_dict(dictionary, start_city, dest_city, get_distance_from_str(current_word));

      if (start_city == NULL || dest_city == NULL || !malloc_start_dest_city()) {
        free_mem(map_file, current_word);
        return nullptr;
      }

      init_csv_line();
      if (current_char == EOF) {
        break;
      }
      continue;
    }

    if (current_char == ',') {
      current_word[char_index] = '\0';

      if (!handle_csv_column(current_word)) {
        free_mem(map_file, current_word);
        return nullptr;
      }

      next_row();
      continue;
    }

    current_word[char_index++] = (char) current_char;
  }

  free_mem(map_file, current_word);
  return dictionary;
}
