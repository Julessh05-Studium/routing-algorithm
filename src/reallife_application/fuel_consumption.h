//
// Created by Julian Schumacher on 20.02.25.
//

#ifndef FUEL_CONSUMPTION_H
#define FUEL_CONSUMPTION_H

/**
 * Queries the user for the fuel efficiency of their car
 * @return the fuel efficiency as l/km
 */
double query_fuel_efficiency();

/**
 * calculates the fuel consumption for the trip. This method queries the user for the fuel efficiency of their car
 * @param distance The distance the user wants to travel with this trip
 * @param fuel_efficiency
 * @return
 */
double calculate_fuel_consumption(int distance, double fuel_efficiency);

/**
 * Queries the user for the price per liter in euro
 * @return the price per liter in euro
 */
double query_liter_price();

/**
 * queries the user for the current price per liter in euro and calculates the price for the trip
 * @param liter the amount of liter needed for the trip
 * @param price_per_liter
 * @return price for liter passed
 */
double calculate_liter_price(double liter, double price_per_liter);

#endif //FUEL_CONSUMPTION_H
