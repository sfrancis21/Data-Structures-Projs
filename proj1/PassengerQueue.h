/*
 *  PassengerQueue.h
 *  Sara Francis
 *  2/13
 *
 *  CS 15 Project 1: Metro Sim
 *
 * This is the class declarations for the PassengerQueue class
 * It is responsible for creating a list of passengers and the functions *used to  * edit/insert/remove passengers from the list
 *
 */

#ifndef PASSENGER_QUEUE_H
#define PASSENGER_QUEUE_H

#include "Passenger.h"
#include <list>
#include <iostream>

class PassengerQueue {

public:

    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size();
    void print(std::ostream &output);

private:
    
    std::list<Passenger> queue;

}; 

#endif