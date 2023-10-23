/*
 *  MetroSim.cpp
 *  Sara Francis
 *  2/17
 *
 *  CS 15 Project 1: Metro Sim
 *
 * Function Definitions for the MetroSim Class
 *
 */

#include "MetroSim.h"
#include "PassengerQueue.h"
#include "Passenger.h"
#include <vector>
#include <iostream>
#include <fstream>

/*
 * name:      MetroSim()
 * purpose:   Initialize variables
 * arguments: none
 * returns:   None
 * effects:   sets variables
 */
MetroSim::MetroSim() {
    stationofTrain = 0;
    stationSize = 0;
    passengerNum = 1;
 }

/*
 * name:      initializeVectors()
 * purpose:   Initialize Passenger Queues for train and stationQueue vectors
 * arguments: none
 * returns:   None
 * effects:   initializes queues
 */
void MetroSim::initializeVectors() {
    for (int i = 0; i < stationSize; i++) {
        PassengerQueue temp;
        train.push_back(temp);
        stationQueue.push_back(temp);
    }
}

/*
 * name:      movingTrain()
 * purpose:   Move the train
 * arguments: none
 * returns:   None
 * effects:   none
 */
void MetroSim::movingTrain(){
    if (stationofTrain == stationSize - 1) {
        stationofTrain = 0;
    } else {
        stationofTrain++;
    }
}

/*
 * name:      passengerCommand()
 * purpose:   Calls all functions for the passenger command
 * arguments: Arrival and departure int for passenger
 * returns:   None
 * effects:   none
 */
void MetroSim::passengerCommand(int arrival, int departure) {
    Passenger p(passengerNum, arrival, departure);
    addingPassengerToStation(p);
    passengerNum++;
}

/*
 * name:      trainCommand()
 * purpose:   Calls all functions needed for when the train moves
 * arguments: output
 * returns:   None
 * effects:   none
 */
void MetroSim::trainCommand() {
    removingPassengerFromStation(stationofTrain);
    movingTrain();
    removingPassengerFromTrain(stationofTrain);
}

/*
 * name:      endCommand()
 * purpose:   Ends the simulation
 * arguments: none
 * returns:   None
 * effects:   none
 */
void MetroSim::endCommand() {
    std::cout << "Thanks for playing MetroSim. Have a nice day!" << std::endl;
}

/*
 * name:      readinStations()
 * purpose:   Read in stations from file and add them to the stations vector.
 * arguments: File name
 * returns:   None
 * effects:   Sets stations vector and station Num
 */
void MetroSim::readinStations(std::string filename) {
    std::ifstream infile;
    infile.open(filename);

    if (not infile.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string stationName;
    while(getline(infile, stationName)) {
        stations.push_back(stationName);
    }
    infile.close();
    stationSize = stations.size();
    initializeVectors();
}

/*
 * name:      addingPassengerToStation()
 * purpose:   Adds a passenger to the station queue
 * arguments: Person to add and station number to add it at
 * returns:   None
 * effects:   Adds passenger to stationQueue
 */
void MetroSim::addingPassengerToStation(Passenger person) {
    int stationNum = person.from;
    stationQueue[stationNum].enqueue(person);
}

/*
 * name:      removingPassengerFromStation()
 * purpose:   Removes a passengers from the station queue
 * arguments: Person to  and station number to add it at
 * returns:   None
 * effects:   Removes passengers to stationQueue
 */
void MetroSim::removingPassengerFromStation(int stationNum) {
    int queueSize;
    Passenger chosen;
    queueSize = stationQueue[stationNum].size();
    for (int i = 0; i < queueSize; i++) {
        chosen = stationQueue[stationNum].front();
        stationQueue[stationNum].dequeue();
        addingPassengerToTrain(chosen);
    }
}

/*
 * name:      addingPassengerToTrain()
 * purpose:   Adds passengers to the train queue
 * arguments: station number to add it at
 * returns:   None
 * effects:   Adds passenger to train
 */
void MetroSim::addingPassengerToTrain(Passenger person) {
    int stationNum = person.to;
    train[stationNum].enqueue(person);
}

/*
 * name:      removingPassengerFromTrain()
 * purpose:   Removes passengers from the train queue
 * arguments: station number to add it at
 * returns:   None
 * effects:   removes passengers from train
 */
void MetroSim::removingPassengerFromTrain(int stationNum) {
    int trainSize = train[stationNum].size();
    Passenger chosen;
    for (int i = 0; i < trainSize; i++) {
        chosen = train[stationNum].front();
        train[stationNum].dequeue();
        outputPassengers.enqueue(chosen);
    }
}

/*
 * name:      printStationQueue()
 * purpose:   Prints passengers waiting at a specific station
 * arguments: station number to print from and output
 * returns:   None
 * effects:   none
 */
void MetroSim::printStationQueue(int stationNum, std::ostream &output) {
    stationQueue[stationNum].print(output);
}

/*
 * name:      printTrainPassengers()
 * purpose:   Prints passengers waiting at a specific station
 * arguments: output
 * returns:   None
 * effects:   none
 */
void MetroSim::printTrainPassengers(std::ostream &output) {
    for (int i = 0; i < stationSize; i++) {
        train[i].print(output);
    }
}

/*
 * name:      printStations()
 * purpose:   Prints stations with TRAIN
 * arguments: output
 * returns:   None
 * effects:   none
 */
void MetroSim::printStations() {
    for (int i = 0; i < stationSize; i++) {
        std::string message = stations.at(i);
        if (i == stationofTrain) {
            std::cout << "TRAIN: [" << i << "] " << message << " {";
            printStationQueue(i, std::cout);
            std::cout << "}\n";
        }
        else {
            std::cout << "       [" << i << "] " << message << " {";
            printStationQueue(i, std::cout);
            std::cout << "}\n";
        }
    }
}

/*
 * name:      printOutput()
 * purpose:   Prints exiting passenger to output file
 * arguments: output and passenger to print
 * returns:   None
 * effects:   None
 */
void MetroSim::printOutput(std::string outputFile) {
    int length = outputPassengers.size();
    std::ofstream outfile;
    outfile.open(outputFile);

    if (not outfile.is_open()) {
        std::cerr << "Error: could not open file " << outputFile << std::endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < length; i++) {
        Passenger p = outputPassengers.front();
        int departure = p.to;
        int passengerID = p.id;
        std::string stationName = stations.at(departure);
        outfile << "Passenger " << passengerID << " left train at station "
        << stationName << std::endl;
        outputPassengers.dequeue();
    }

    outfile.close();
}

/*
 * name:      printAll()
 * purpose:   Prints entire sim page
 * arguments: output
 * returns:   None
 * effects:   print all
 */
void MetroSim::printAll() {
    //Printing train passengers
    std::cout << "Passengers on the train: {";
    printTrainPassengers(std::cout);
    std::cout << "}\n";

    //Stations
    printStations();
}