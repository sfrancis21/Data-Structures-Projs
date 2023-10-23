/*
 *  MetroSim.h
 *  Sara Francis
 *  2/17
 *
 *  CS 15 Project 1: Metro Sim
 *
 * This is the class declarations for the MetroSim class
 * It is responsible for creating vectors for the stations, station queues, and train queues.
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "PassengerQueue.h"
#include "Passenger.h"
#include <vector>
#include <iostream>

// Put any other necessary includes here


// Put any other structs you need here

class MetroSim
{
public:
    //Constructor
    MetroSim();

    //Reading Stations from File
    void readinStations(std::string filename);

    //Total Print Statement
    void printAll();

    //Turn for Passenger Command
    void passengerCommand(int arrival, int departure);

    //Turn for Train Command
    void trainCommand();

    //End Simulation Command
    void endCommand();

    //Printing Passengers to the output file
    void printOutput(std::string output);

private:
    //Queue to keep track of outputted passengers
    PassengerQueue outputPassengers;
    //Keeps track of Station the train is at
    int stationofTrain; 
    //Number of stations
    int stationSize;
    //Passenger Index Number
    int passengerNum;

    //Vector for each train car that holds a queue of passengers
    std::vector<PassengerQueue> train;

    //Vector for each station that holds a queue of passengers
    std::vector<PassengerQueue> stationQueue;

    //Vector for each station
    std::vector<std::string> stations;

    //Functions for adding and removing from train and station vectors
    void addingPassengerToStation(Passenger person);
    void removingPassengerFromStation(int stationNum);
    void addingPassengerToTrain(Passenger person);
    void removingPassengerFromTrain(int stationNum);
    
    //Initialize Vectors
    void initializeVectors();

     //Printing Station queues
    void printStationQueue(int stationNum, std::ostream &output);

    //Printing train passengers in ascending station order
    void printTrainPassengers(std::ostream &output);

    //Print all the station names
    void printStations();

    //Moves the train
    void movingTrain();
    
};

#endif
