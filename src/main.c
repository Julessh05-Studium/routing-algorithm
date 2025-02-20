#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logic/algo.h"

#include "objects/dictionary.h"
#include "parsing/parser.h"

#include "reallife_application/fuel_consumption.h"

#define MAP_LONG "--map"
#define MAP_SHORT "-m"

#define START_LONG "--start"
#define START_SHORT "-s"

#define TARGET_LONG "--target"
#define TARGET_SHORT "-t"

#define DEBUG_LONG "--debug"
#define DEBUG_SHORT "-d"

#define WAYPOINT_LONG "--waypoint"
#define WAYPOINT_SHORT "-wp"

#define REALLIFE_ACTIVE "--real"

/**
 * Checks whether the identifier marks the path of the map and returns the parsed dictionary if successful
 * @param identifier the identifier which should be checked for the map
 * @param value the path of the map
 * @return the parsed dictionary
 */
DICTIONARY* check_map(const char* identifier, const char* value) {
  if (strcmp(identifier, MAP_LONG) == 0 || strcmp(identifier, MAP_SHORT) == 0) {
    const char* path = value;
    if (path == nullptr || strcmp(path, "") == 0) {
      fprintf(stderr, "a valid path has to be passed.");
      exit(1);
    }
    if (path[0] != '/') {
      char* tmp_path = malloc(sizeof(char) * 200);
      if (getcwd(tmp_path, 200) == nullptr) {
        fprintf(stderr, "failed to get current working directory.\n");
        exit(1);
      }
      char* pws = malloc(sizeof(char) * 200);
      strcpy(pws, "/");
      strcat(pws, path);
      strcat(tmp_path, pws);
      free(pws);
    }
    return parse(path);
  }
  return nullptr;
}

/**
 * Checks for the start city marker and returns the city marker if found
 * @param identifier the identifier to be checked for the start identifier
 * @param value the start city
 * @return the start city passed to this program
 */
const char* check_start(const char* identifier, const char* value) {
  if (strcmp(identifier, START_LONG) == 0 || strcmp(identifier, START_SHORT) ==
      0) {
    const char* start = value;
    if (start == nullptr) {
      fprintf(stderr, "a valid start name has to be passed.");
      exit(1);
    }
    return start;
  }
  return nullptr;
}

/**
 * Checks for the target city marker and returns the city marker if found
 * @param identifier the identifier to be checked for the target identifier
 * @param value the target city
 * @return the target city passed to this program
 */
const char* check_target(const char* identifier, const char* value) {
  if (strcmp(identifier, TARGET_LONG) == 0 || strcmp(identifier, TARGET_SHORT)
      == 0) {
    const char* target = value;
    if (target == nullptr) {
      fprintf(stderr, "a valid target name has to be passed.");
      exit(1);
    }
    return target;
  }
  return nullptr;
}

const char* check_waypoint(const char* identifier, const char* value) {
  if (strcmp(identifier, WAYPOINT_LONG) == 0 || strcmp(
          identifier, WAYPOINT_SHORT) == 0) {
    if (value == nullptr) {
      fprintf(
          stderr,
          "a valid waypoint name has to be passed, if waypoints should be used.");
      exit(1);
    }
    return value;
  }
  return nullptr;
}

int main(const int argc, char* argv[]) {
  // Declare variables
  const DICTIONARY* dictionary = nullptr;
  const char* start = nullptr;
  const char* target = nullptr;
  bool map_given = false;
  bool start_given = false;
  bool target_given = false;
  bool debug = false;
  char** waypoints = nullptr;
  int waypoints_size = 0;
  unsigned long* waypoints_length = nullptr;
  bool reallife = false;

  for (int i = 1; i < argc; ++i) {
    // Check for map
    if (!map_given) {
      dictionary = check_map(argv[i], argv[i + 1]);
      if (dictionary != nullptr) {
        map_given = true;
        i++;
      }
    }

    // Check for start city
    if (!start_given) {
      start = check_start(argv[i], argv[i + 1]);
      if (start != nullptr) {
        start_given = true;
        i++;
      }
    }

    // Check for target city
    if (!target_given) {
      target = check_target(argv[i], argv[i + 1]);
      if (target != nullptr) {
        target_given = true;
        i++;
      }
    }

    // Check for debug
    if (strcmp(argv[i], DEBUG_LONG) == 0 || strcmp(argv[i], DEBUG_SHORT) ==
        0) {
      debug = true;
    }

    // Check for reallife application with fuel and price
    if (strcmp(argv[i], REALLIFE_ACTIVE) == 0) {
      reallife = true;
    }

    // TODO-js: extract method
    const char* waypoint_to_check = check_waypoint(argv[i], argv[i + 1]);
    if (waypoint_to_check != nullptr) {
      waypoints_size++;
      char** tmp_waypoints_pointer;
      if (waypoints != nullptr) {
        tmp_waypoints_pointer = realloc(waypoints,
                                        sizeof(char*) * waypoints_size);
      } else {
        tmp_waypoints_pointer = malloc(sizeof(char*));
      }
      waypoints = tmp_waypoints_pointer;
      //free(tmp_waypoints_pointer);

      unsigned long* tmp_waypoints_length_pointer;
      if (waypoints_length != nullptr) {
        tmp_waypoints_length_pointer = realloc(waypoints_length,
                                               sizeof(unsigned long) *
                                               waypoints_size);
      } else {
        tmp_waypoints_length_pointer = malloc(sizeof(unsigned long));
      }
      waypoints_length = tmp_waypoints_length_pointer;
      //free(tmp_waypoints_length_pointer);

      waypoints[waypoints_size - 1] =
          malloc(sizeof(char) * strlen(argv[i + 1]));
      waypoints[waypoints_size - 1] = argv[i + 1];
      waypoints_length[waypoints_size - 1] = strlen(argv[i + 1]);
    }
  }

  // Error handling if one or more required information are not provided
  if (!(map_given && start_given && target_given)) {
    fprintf(
        stderr,
        "To run the program, a valid map, start and target have to be passed"
        );
    return EXIT_FAILURE;
  }

  // average data
  double fuel_efficiency = 7.7;
  double price_per_liter = 1.85;
  if (reallife) {
    // Query specific user data
    fuel_efficiency = query_fuel_efficiency();
    price_per_liter = query_liter_price();
  }

  // calculate different routes
  int distance = 0;
  if (waypoints != nullptr) {
    distance = dijkstra(dictionary, start, waypoints[0], debug);
    if (!reallife) {
      printf("Estimated price and fuel consumption based on average data:\n");
    }
    double liter =
        calculate_fuel_consumption(distance, fuel_efficiency);
    calculate_liter_price(liter, price_per_liter);
    for (int i = 0; i < waypoints_size; ++i) {
      distance = dijkstra(dictionary, waypoints[i], waypoints[i + 1], debug);
      liter = calculate_fuel_consumption(distance, fuel_efficiency);
      calculate_liter_price(liter, price_per_liter);
    }
  } else {
    distance = dijkstra(dictionary, start, target, debug);
    if (!reallife) {
      printf("Estimated price and fuel consumption based on average data:\n");
    }
    const double liter =
        calculate_fuel_consumption(distance, fuel_efficiency);
    calculate_liter_price(liter, price_per_liter);
  }

  // Free memory
  free(waypoints);
  free(waypoints_length);
  return EXIT_SUCCESS;
}
