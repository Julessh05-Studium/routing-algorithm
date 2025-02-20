#include <stdio.h>
#include <_stdlib.h>
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

/**
 * Checks whether the identifier marks the path of the map and returns the parsed dictionary if successful
 * @param identifier the identifier which should be checked for the map
 * @param value the path of the map
 * @return the parsed dictionary
 */
DICTIONARY* check_map(const char* identifier, const char* value) {
  if (strcmp(identifier, MAP_LONG) == 0 || strcmp(identifier, MAP_SHORT) == 0) {
    char* path = value;
    if (path == NULL || strcmp(path, "") == 0) {
      fprintf(stderr, "a valid path has to be passed.");
      exit(1);
    }
    if (path[0] != '/') {
      char* tmp_path = malloc(sizeof(char) * 200);
      if (getcwd(tmp_path, 200) == NULL) {
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
char* check_start(const char* identifier, const char* value) {
  if (strcmp(identifier, START_LONG) == 0 || strcmp(identifier, START_SHORT) ==
      0) {
    const char* start = value;
    if (start == NULL) {
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
char* check_target(const char* identifier, const char* value) {
  if (strcmp(identifier, TARGET_LONG) == 0 || strcmp(identifier, TARGET_SHORT)
      == 0) {
    const char* target = value;
    if (target == NULL) {
      fprintf(stderr, "a valid target name has to be passed.");
      exit(1);
    }
    return target;
  }
  return nullptr;
}

int main(int argc, char* argv[]) {
  // Declare variables
  DICTIONARY* dictionary;
  char* start;
  char* target;
  bool map_given = false;
  bool start_given = false;
  bool target_given = false;
  bool debug = false;

  for (int i = 1; i < argc; ++i) {
    if (!map_given) {
      dictionary = check_map(argv[i], argv[i + 1]);
      if (dictionary != nullptr) {
        map_given = true;
        i++;
      }
    }

    if (!start_given) {
      start = check_start(argv[i], argv[i + 1]);
      if (start != nullptr) {
        start_given = true;
        i++;
      }
    }

    if (!target_given) {
      target = check_target(argv[i], argv[i + 1]);
      if (target != nullptr) {
        target_given = true;
        i++;
      }
    }

    if (strcmp(argv[i], DEBUG_LONG) == 0 || strcmp(argv[i], DEBUG_SHORT) == 0) {
      debug = true;
    }
  }

  if (!(map_given && start_given && target_given)) {
    fprintf(
        stderr,
        "To run the program, a valid map, start and target have to be passed"
        );
  }

  const int distance = dijkstra(dictionary, start, target, debug);
  const double liter = calculate_fuel_consumption(distance);
  calculate_liter_price(liter);
  return EXIT_SUCCESS;
}
