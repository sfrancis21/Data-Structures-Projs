/*
 *  unit_tests.h
 *  Sara Francis
 *  2/13
 *
 *  CS 15 Project 1: Metro Sim
 *
 *  This file is for testing all of the functions in project one
 *  This includes the classes passenger and passengerqueue
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include "MetroSim.h"
#include <cassert>
#include <sstream>
#include <iostream>

/********************************************************************\
*                           METRO SIM TESTS                          *
\********************************************************************/

// Passenger Print Test
void passenger_print_test() {
    Passenger p(1, 5, 6);
    std::ostringstream ss;
    p.print(ss);
    assert(ss.str() == "[1, 5->6]");
}

//Adding to passenger enqueue and front test
void enqueue_test() {
    PassengerQueue q;
    Passenger p(3, 5, 7);
    q.enqueue(p);

    Passenger result;
    result = q.front();
    
    std::ostringstream ss;
    result.print(ss);
    assert(ss.str() == "[3, 5->7]");
}

//Passenger Queue Size test
void queueSize_test() {
    //One element
    PassengerQueue q;
    Passenger p(3, 5, 7);
    q.enqueue(p);
    assert(q.size() == 1);

    //Zero Elements
    PassengerQueue w;
    assert(w.size() == 0);
    
    //Many elements
    PassengerQueue z;
    Passenger a(1, 5, 2);
    Passenger b(2, 8, 6);
    Passenger c(3, 11, 7);
    Passenger d(4, 9, 4);
   
    z.enqueue(a);
    z.enqueue(b);
    z.enqueue(c);
    z.enqueue(d);
    assert(z.size() == 4);
}

//Testing printing many passengers 
void bigPrint_test() {
    PassengerQueue q;
    
    Passenger a(1, 5, 2);
    Passenger b(2, 8, 6);
    Passenger c(3, 11, 7);
    Passenger d(4, 9, 4);
   
    q.enqueue(a);
    q.enqueue(b);
    q.enqueue(c);
    q.enqueue(d);

    std::ostringstream ss;
    q.print(ss);
    assert(ss.str() == "[1, 5->2][2, 8->6][3, 11->7][4, 9->4]");
}

//Testing PassengerQueue dequeue
void passengerDequeue_test() {
    //Full list
    PassengerQueue q;
    Passenger a(1, 5, 2);
    Passenger b(2, 8, 6);
   
    q.enqueue(a);
    q.enqueue(b);
    q.dequeue();

    std::ostringstream ss;
    q.print(ss);
    assert(ss.str() == "[2, 8->6]");

}

//Adding Passengers to stationQueue and train (Made functions public)
// void addingPassengers_test() {
//     MetroSim sim;
//     Passenger p(1, 3, 5);
//     Passenger q(2, 5, 5);
//     Passenger z(3, 7, 10);
//     Passenger x(4, 10, 1);

    
//     std::string filename = "stations.txt";
//     sim.readinStations(filename);
    
//     //One person from one station
//     sim.addingPassengerToTrain(p);
//     std::ostringstream ss;
//     sim.printTrainPassengers(ss);
//     assert(ss.str() == "[1, 3->5]");

//     //Two people from the same station
//     sim.addingPassengerToTrain(q);
//     std::ostringstream ww;
//     sim.printTrainPassengers(ww);
//     assert(ww.str() == "[1, 3->5][2, 5->5]");

//     //People in multiple stations
//     sim.addingPassengerToTrain(z);
//     sim.addingPassengerToTrain(x);
//     std::ostringstream yy;
//     sim.printTrainPassengers(yy);
//     assert(yy.str() == "[4, 10->1][1, 3->5][2, 5->5][3, 7->10]");
// }

//Removing Passengers from Train (Made functions public)
// void removingPassengers_test() {
//     MetroSim sim;

//     std::string filename = "stations.txt";
//     sim.readinStations(filename);
//     //Making Passengers
//     Passenger p(1, 3, 5);
//     Passenger q(2, 5, 5);
//     Passenger z(3, 7, 10);
//     Passenger x(4, 10, 1);
//     //Adding Passengers
//     sim.addingPassengerToTrain(p);
//     sim.addingPassengerToTrain(q);
//     sim.addingPassengerToTrain(z);
//     sim.addingPassengerToTrain(x);

//     sim.removingPassengerFromTrain(5);
//     std::ostringstream yy;
//     sim.printTrainPassengers(yy);
//     assert(yy.str() == "[4, 10->1][3, 7->10]");
// }

//Tests Big printing statement
void printAll_test() {
    MetroSim sim;
    std::string filename = "stations.txt";
    sim.readinStations(filename);
    sim.printAll();
}