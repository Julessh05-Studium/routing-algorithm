//
// Created by Julian Schumacher on 20.02.25.
//

#include "fuel_consumption.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double query_fuel_efficiency() {
  printf(
      "Enter the fuel efficiency of your car (l/km) to get the fuel consumption for this route, or press n to exit: ");
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


double calculate_fuel_consumption(const int distance,
                                  const double fuel_efficiency) {
  const double fuel_consumption = fuel_efficiency * distance / 100;
  printf("You need %.2fl of fuel for this trip\n", fuel_consumption);
  return fuel_consumption;
}


double query_liter_price() {
  printf("Enter the price per liter (€/l), or press n to exit: ");
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


double calculate_liter_price(const double liter, const double price_per_liter) {
  const double complete_price = price_per_liter * liter;
  printf("The fuel for this trip will cost %.2f€\n", complete_price);
  return complete_price;
}
