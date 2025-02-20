//
// Created by Julian Schumacher on 20.02.25.
//

#ifndef FUEL_CONSUMPTION_H
#define FUEL_CONSUMPTION_H

/**
 * calculates the fuel consumption for the trip. This method queries the user for the fuel efficiency of their car
 * @param distance The distance the user wants to travel with this trip
 * @return
 */
double calculate_fuel_consumption(int distance);

/**
 * queries the user for the current price per liter in euro and calculates the price for the trip
 * @param liter the amount of liter needed for the trip
 * @return price for liter passed
 */
double calculate_liter_price(double liter);

#endif //FUEL_CONSUMPTION_H
