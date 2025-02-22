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

#define TARGET_LONG "--destination"
#define TARGET_SHORT "-dest"

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
    if (value == nullptr || strcmp(value, "") == 0) {
      fprintf(stderr, "a valid start name has to be passed.");
      exit(1);
    }
    return value;
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
    if (value == nullptr || strcmp(value, "") == 0) {
      fprintf(stderr, "a valid target name has to be passed.");
      exit(1);
    }
    return value;
  }
  return nullptr;
}

/**
 * Checks for the waypoint marker and returns the waypoint if found
 * @param identifier the identifier to check for the waypoint marker
 * @param value the waypoint passed, if it is a waypoint
 * @return the waypoint if found
 */
const char* check_waypoint(const char* identifier, const char* value) {
  if (strcmp(identifier, WAYPOINT_LONG) == 0 || strcmp(
          identifier, WAYPOINT_SHORT) == 0) {
    if (value == nullptr || strcmp(value, "") == 0) {
      fprintf(
          stderr,
          "a valid waypoint name has to be passed, if waypoints should be used.");
      exit(1);
    }
    return value;
  }
  return nullptr;
}

/**
 * Creates the waypoint array at the location specified by waypoints based on all waypoints as arguments
 * @param identifier the identifier to check for the waypoint marker
 * @param value the value of the waypoint
 * @param waypoints the array containing all the waypoints
 * @param waypoints_size the size of the waypoints array
 */
const char** create_waypoint_arr(
    const char* identifier,
    const char* value,
    char** waypoints,
    int* waypoints_size
    ) {
  const char* waypoint_to_check = check_waypoint(identifier, value);
  if (waypoint_to_check != nullptr) {
    *waypoints_size = *waypoints_size + 1;
    char** tmp_waypoints_pointer = realloc(waypoints,
                                           sizeof(char*) * *waypoints_size);
    if (tmp_waypoints_pointer == nullptr) {
      *waypoints_size = *waypoints_size - 1;
      return waypoints;
    }
    waypoints = tmp_waypoints_pointer;
    // - 2 because -1 would be the last element, and -2 is the second last element, which works, because the last element is reserved for destination
    waypoints[*waypoints_size - 2] = waypoint_to_check;
    return waypoints;
  }
  return waypoints;
}

/**
 * Calculates the distances and prints the routes to the std out.
 *
 * @param waypoints the waypoints to visit on the way
 * @param waypoints_size the size of the waypoints array
 * @param dictionary the dictionary of cities
 * @param reallife whether to apply reallife application or not
 * @param debug whether to enable debug mode or not
 */
void calculate_distances(
    const char** waypoints,
    const int waypoints_size,
    const DICTIONARY* dictionary,
    const bool reallife,
    const bool debug
    ) {
  /*
   * average data for fuel efficiency and price per liter
   *
   * fuel efficiency sources:
   * source: https://de.statista.com/statistik/daten/studie/484054/umfrage/durchschnittsverbrauch-pkw-in-privaten-haushalten-in-deutschland/
   * source: https://hvv-schulprojekte.de/unterrichtsmaterialien/kraftstoffverbrauch/#:~:text=Spezifischer%20Kraftstoffverbrauch%20der%20Pkw%20in%20Deutschland&text=Die%20Angaben%20für%20jeden%20Autotyp,100%20km%20für%20Benzin%2DPkw.
   *
   * price per liter source:
   * https://de.statista.com/statistik/daten/studie/1690/umfrage/preis-fuer-einen-liter-superbenzin-monatsdurchschnittswerte/
  */
  double fuel_efficiency = 7.7;
  double price_per_liter = 1.85;
  if (reallife) {
    // Query specific user data
    fuel_efficiency = query_fuel_efficiency();
    price_per_liter = query_liter_price();
  }

  // calculate different routes
  int distance = 0;

  for (int i = 0; i < waypoints_size - 1; i++) {
    distance = dijkstra(dictionary, waypoints[i], waypoints[i + 1], debug);
    if (!reallife) {
      printf(
          "Estimated price and fuel consumption based on average data (7.7l/km - 1.85€/l):\n"
          );
    }
    const double liter =
        calculate_fuel_consumption(distance, fuel_efficiency);
    calculate_liter_price(liter, price_per_liter);
  }
}


int main(const int argc, char* argv[]) {
#if __STDC_VERSION__ < 20200
  fprintf(stderr, "C23 support required\n");
  return EXIT_FAILURE;
#endif
  // Declare variables
  const DICTIONARY* dictionary = nullptr;
  const char* start = nullptr;
  const char* target = nullptr;
  bool map_given = false;
  bool start_given = false;
  bool target_given = false;
  bool debug = false;
  char** waypoints = malloc(sizeof(char*) * 2);;
  int waypoints_size = 2;
  bool reallife = false;

  for (int i = 1; i < argc; ++i) {
    // Check for the map
    if (!map_given) {
      dictionary = check_map(argv[i], argv[i + 1]);
      if (dictionary != nullptr) {
        map_given = true;
        i++;
        continue;
      }
    }

    // Check for start city
    if (!start_given) {
      start = check_start(argv[i], argv[i + 1]);
      if (start != nullptr) {
        start_given = true;
        i++;
        // Add start to waypoints array
        waypoints[0] = start;
        continue;
      }
    }

    // Check for target city
    if (!target_given) {
      target = check_target(argv[i], argv[i + 1]);
      if (target != nullptr) {
        target_given = true;
        i++;
        continue;
      }
    }

    // Check for debug
    if (strcmp(argv[i], DEBUG_LONG) == 0 || strcmp(argv[i], DEBUG_SHORT) ==
        0) {
      debug = true;
      continue;
    }

    // Check for reallife application with fuel and price
    if (strcmp(argv[i], REALLIFE_ACTIVE) == 0) {
      reallife = true;
      continue;
    }

    // Create the waypoint array
    waypoints = create_waypoint_arr(argv[i], argv[i + 1], waypoints,
                                    &waypoints_size);
  }
  waypoints[waypoints_size - 1] = target;

  // Error handling if one or more required information are not provided
  if (!(map_given && start_given && target_given)) {
    fprintf(
        stderr,
        "To run the program, a valid map, start and target have to be passed\n"
        );
    for (int i = 0; i < waypoints_size; ++i) {
      free(waypoints[i]);
    }
    free(waypoints);
    return EXIT_FAILURE;
  }

  // calculate distances
  calculate_distances(waypoints, waypoints_size, dictionary, reallife, debug);
  // Free memory
  free(waypoints);
  return EXIT_SUCCESS;
}
