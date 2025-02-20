//
// Created by Julian Schumacher on 20.02.25.
//

#include "fuel_consumption.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Queries the user for the fuel efficiency of their car
 * @return the fuel efficiency as l/km
 */
double query_fuel_efficiency() {
  printf(
      "Enter the fuel efficiency of your car to get the fuel consumption for this route, or press n to exit: ");
  char* fuel_consumption = malloc(sizeof(char) * 10);
  scanf("%s", fuel_consumption);
  if (strcmp(fuel_consumption, "n") == 0) {
    exit(0);
  }
  double fuel_efficiency = 0;
  fuel_efficiency = strtof(fuel_consumption, nullptr);
  free(fuel_consumption);
  return fuel_efficiency;
}


double calculate_fuel_consumption(const int distance) {
  const double fuel_efficiency = query_fuel_efficiency();
  const double fuel_consumption = fuel_efficiency * distance / 100;
  printf("You need %.2fl of fuel for this trip\n", fuel_consumption);
  return fuel_consumption;
}

/**
 * Queries the user for the price per liter in euro
 * @return the price per liter in euro
 */
double query_liter_price() {
  printf("Enter the price per liter, or press n to exit: ");
  char* liter_price = malloc(sizeof(char) * 10);
  scanf("%s", liter_price);
  if (strcmp(liter_price, "n") == 0) {
    exit(0);
  }
  double price = 0;
  price = strtof(liter_price, nullptr);
  free(liter_price);
  return price;
}


double calculate_liter_price(const double liter) {
  const double price_per_liter = query_liter_price();
  const double complete_price = price_per_liter * liter;
  printf("The fuel for this trip will cost %.2f€\n", complete_price);
  return complete_price;
}
