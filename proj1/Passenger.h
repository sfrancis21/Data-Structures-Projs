/*
 *  Passenger.h
 *  Sara Francis
 *  2/13
 *
 *  CS 15 Project 1: Metro Sim
 *
 * This is the class declarations for the Passenger class
 * It is responsible for creating passengers and the functions used to print them out
 *
 */

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        // TODO: implement the print function in Passenger.cpp
        void print(std::ostream &output);

};

#endif
