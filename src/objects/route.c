//
// Created by Julian Schumacher on 08.02.25.
//

#include "route.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_to_route(ROUTE* route, const CONNECTION connection) {
  CONNECTION* tmp_route;
  if (route->connections == nullptr) {
    tmp_route = malloc(sizeof(CONNECTION) * (route->length + 1));
  } else {
    tmp_route = realloc(route->connections,
                        sizeof(CONNECTION) * (route->length + 1));
  }
  route->connections = tmp_route;
  route->connections[route->length] = connection;
  route->length++;
}

void print_route(const ROUTE* route, const char* start,
                 char** complete_route, const bool debug) {
  printf("%s -> ", start);
  for (int i = 0; i < route->length; i++) {
    const char* connection = route->connections[i].destination.name;
    printf("%s", connection);
    if (!debug) {
      char* tmp_complete_route = realloc(*complete_route,
                                         sizeof(char) * (
                                           strlen(*complete_route) + strlen(
                                               connection) + 4
                                         )
          );
      *complete_route = tmp_complete_route;
      strcat(*complete_route, connection);
    }
    if (i != route->length - 1) {
      printf(" -> ");
      if (!debug) {
        strcat(*complete_route, " -> ");
      }
    } else {
      printf("\n");
    }
  }
  printf("Total distance: %dkm\n", route->distance);
}

CONNECTION* get_last_eof(const ROUTE* route) {
  return &route->connections[route->length - 1];
}


void free_route(ROUTE* route) {
  free(route->connections);
  route->length = 0;
}
