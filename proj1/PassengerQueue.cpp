/*
 *  PassengerQueue.cpp
 *  Sara Francis
 *  2/13
 *
 *  CS 15 Project 1: Metro Sim
 *
 * Function Definitions for the PassengerQueue Class
 *
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include <list>
#include <iostream>

/*
 * name:      front()
 * purpose:   Finds the passenger at the front of the list
 * arguments: None
 * returns:   Passenger
 * effects:   None
 */
 Passenger PassengerQueue::front() {
    Passenger result;
    result = queue.front();
    return result;
 }

/*
 * name:      dequeue()
 * purpose:   Removes element at front of the queue
 * arguments: None
 * returns:   None
 * effects:   Size decreases by one
 */
void PassengerQueue::dequeue() {
    queue.pop_front();
}

/*
 * name:      enqueue()
 * purpose:   Inserts a new passenger at the back of the list
 * arguments: Passenger
 * returns:   None
 * effects:   Size increases by one
 */
void PassengerQueue::enqueue(const Passenger &passenger) {
    queue.push_back(passenger);
}

/*
 * name:      size()
 * purpose:   returns the size of the queue
 * arguments: none
 * returns:   None
 * effects:   none
 */
int PassengerQueue::size() {
    return queue.size();
}

/*
 * name:      print()
 * purpose:   prints the queue
 * arguments: output
 * returns:   None
 * effects:   none
 */
void PassengerQueue::print(std::ostream &output) {
    std::list<Passenger>::iterator iterator;
    for (iterator = queue.begin(); iterator != queue.end(); iterator++) {
        int id = iterator->id;
        int arrival = iterator->from;
        int departure = iterator->to;
        Passenger person(id, arrival, departure);
        person.print(output);
    }
}
