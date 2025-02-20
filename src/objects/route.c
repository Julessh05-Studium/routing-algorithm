//
// Created by Julian Schumacher on 08.02.25.
//

#include "route.h"

#include <stdio.h>
#include <stdlib.h>

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

void print_route(const ROUTE* route, const char* start) {
  printf("%s -> ", start);
  for (int i = 0; i < route->length; i++) {
    printf("%s", route->connections[i].destination.name);
    if (i != route->length - 1) {
      printf(" -> ");
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
