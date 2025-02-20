//
// Created by Julian Schumacher on 20.02.25.
//

#include "fuel_consumption.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double calculate_fuel_consumption(const int distance) {
    const double fe = query_fuel_efficiency();
    const double fq = fe * distance / 100;
    printf("You need %.2fl of fuel for this trip\n", fq);
    return fq;
}

double query_fuel_efficiency() {
    printf("Enter the fuel efficiency of your car to get the fuel consumption for this route, or press n to exit: ");
    char *fuel_consumption = malloc(sizeof(char) * 10);
    scanf("%s", fuel_consumption);
    if (strcmp(fuel_consumption, "n") == 0) {
        exit(0);
    }
    double fe = 0;
    fe = strtof(fuel_consumption, nullptr);
    free(fuel_consumption);
    return fe;
}

double calculate_liter_price(const double liter) {
    const double p = query_liter_price();
    const double cp = p * liter;
    printf("The fuel for this trip will cost %.2f€\n", cp);
    return cp;
}

double query_liter_price() {
    printf("Enter the price per liter, or press n to exit: ");
    char *liter_price = malloc(sizeof(char) * 10);
    scanf("%s", liter_price);
    if (strcmp(liter_price, "n") == 0) {
        exit(0);
    }
    double price = 0;
    price = strtof(liter_price, nullptr);
    free(liter_price);
    return price;
}
