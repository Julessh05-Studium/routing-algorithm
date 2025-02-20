//
// Created by gregorgottschewski on 05.02.25.
//

#include "parser.h"
#include "parser_error_handler.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

int csv_column;
int char_column_index;
CITY *start_city;
CITY *dest_city;
FILE *map_file;
DICTIONARY *dictionary;

/**
 * Initializes the global variables for parsing a new csv row.
 */
void init_csv_line() {
  csv_column = 0;
  char_column_index = 0;
}

/**
 * Resets column counter and character counter for reading next line.
 */
void next_column() {
  csv_column++;
  char_column_index = 0;
}

/**
 * Adds the given start and destination with the given distance to the given
 * dictionary.
 *
 * @param dictionary global connections dictionary
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

    val->connections = malloc(sizeof(CONNECTION));
    if (val->connections == NULL) {
      return false;
    }
    add_to_dictionary(dictionary, start_city, val);
  }

  add(val,
      (CONNECTION){
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
    print_error_general("Name of city is NULL");
    return false;
  }
  strncpy(city->name, name, char_column_index);
  city->name[strlen(name)] = '\0';
  return true;
}

/**
 * Converts given string to integer
 * @param val string to convert
 * @return the converted integer
 */
int get_distance_from_str(const char *val) {
  char tmp[char_column_index + 1];
  strncpy(tmp, val + '\0', char_column_index);
  tmp[char_column_index] = '\0';
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
      print_error_syntax("Map has more than three columns");
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
    print_error_general("Map file could not be opened");
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
 * Resizes the buffer size of specified string.
 *
 * @param buf_size size of the current buffer.
 * @param current_word string to resize.
 * @return true if reallocation succeeded, false otherwise.
 */
bool resize_buffer(int *buf_size, char **current_word) {
  if (current_word == nullptr || *current_word == nullptr || buf_size == nullptr) {
    return false;
  }

  *buf_size += BUFFER_SIZE;
  char *tmp = realloc(*current_word, *buf_size);
  if (tmp == NULL) {
    return false;
  }
  *current_word = tmp;
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

    if (char_column_index + 1 > buf_size) {
      if (!resize_buffer(&buf_size, &current_word)) {
        free_mem(map_file, current_word);
        return nullptr;
      }
    }

    if (current_char == '\n' || current_char == EOF) {
      line_number++;
      const int dist_str = get_distance_from_str(current_word);
      if (dist_str == 0) {
        print_error_general("Distance has to be 1 or greater");
        return nullptr;
      }

      add_wp_to_dict(dictionary, start_city, dest_city, dist_str);

      if (start_city == NULL || dest_city == NULL || !malloc_start_dest_city()) {
        free_mem(map_file, current_word);
        return nullptr;
      }

      init_csv_line();
      if (current_char == EOF) {
        break;
      }
      reset_char_index();
      continue;
    }

    if (current_char == ',') {
      if (char_column_index == 0) {
        print_error_syntax("City name is NULL");
        return nullptr;
      }

      current_word[char_column_index] = '\0';

      if (!handle_csv_column(current_word)) {
        free_mem(map_file, current_word);
        return nullptr;
      }

      next_column();
      continue;
    }

    current_word[char_column_index++] = (char) current_char;
    increment_char_index();
  }

  free_mem(map_file, current_word);
  return dictionary;
}
