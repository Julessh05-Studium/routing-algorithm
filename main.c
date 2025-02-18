#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "objects/dictionary.h"
#include "out.h"
#include "parser.h"

#define MAP_LONG "--map"
#define MAP_SHORT "-m"

int main(const int argc, char *argv[]) {
  DICTIONARY *dictionary;

  for (int i = 1; i < argc; ++i) {
    printf(argv[i]);
    if (strcmp(argv[i], MAP_LONG) == 0 || strcmp(argv[i], MAP_SHORT) == 0) {
      char *path = argv[i + 1];
      if (path == NULL) {
        return EXIT_FAILURE;
      }
      dictionary = parse(path);
      dict_out(dictionary);
      i++;
    }
  }

  return EXIT_SUCCESS;
}
