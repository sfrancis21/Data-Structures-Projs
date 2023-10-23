/*
 *  Passenger.cpp
 *  Sara Francis
 *  2/13
 *
 *  CS 15 Project 1: Metro Sim
 *
 * Function Definitions for the Passenger Class
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * name:      print()
 * purpose:   Print out the passenger info
 * arguments: Output
 * returns:   None
 * effects:   Prints
 */
void Passenger::print(std::ostream &output)
{
        output << "[" << id << ", " << from << "->" << to << "]";
}
