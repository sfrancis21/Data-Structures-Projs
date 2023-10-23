/*
 *
 */

#include <iostream>
#include <fstream>
#include <string>


#include "MetroSim.h"

using namespace std;

void parse_command_line(int argc, char *argv[]);
void turnFunc(MetroSim sim, std::string outputFile);
void commandFileFunc(MetroSim sim, std::string outputFile, std::string commandFile);

int main(int argc, char *argv[])
{
        parse_command_line(argc, argv);
        return 0;
}

//Determines what function is used based on the commands
void parse_command_line(int argc, char *argv[]) {
        MetroSim sim;
        string emptyCommand = "";
        if (argc < 3) {
                std::cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]\n";
                exit(1);
        } else if (argc == 3) {
                std::string stationFile = string(argv[1]);
                std::string outputFile = string(argv[2]);
                sim.readinStations(stationFile);
                turnFunc(sim, outputFile);
        } else if (argc == 4) {
                std::string stationFile = string(argv[1]);
                std::string outputFile = string(argv[2]);
                std::string commandFile = string(argv[3]);
                sim.readinStations(stationFile);
                commandFileFunc(sim, outputFile, commandFile);
        }
        return;
}

//Calls MetroSim functions to handle each command from cin
void turnFunc(MetroSim sim, std::string outputFile) {
        int turn = 0;
        while (turn == 0) {
                sim.printAll();
                char inputCommand;
                char input2;
                std::cout << "Command? "; 
                cin >> inputCommand;
                //Passenger Command
                if (inputCommand == 'p') {
                        int arrival;
                        int departure;
                        cin >> arrival >> departure;
                        sim.passengerCommand(arrival, departure);
                } else if (inputCommand == 'm') {
                        cin >> input2;
                        if (input2 == 'm') {
                                sim.trainCommand();
                        } else if (input2== 'f') {
                                sim.endCommand();
                                turn = 1;
                        }
                }
        }
        sim.printOutput(outputFile);
        return;
}

//Calls MetroSim functions to handle commands from a file
void commandFileFunc(MetroSim sim, std::string outputFile, std::string commandFile) {
        int turn = 0;
        std::ifstream infile;
        infile.open(commandFile);

        if (not infile.is_open()) {
                std::cerr << "Error: could not open file " << commandFile;
        }
        //Checks what command is inputted and runs the correct functions
        while (turn == 0) {
                if (infile.eof()) {
                        std::cout << "Thanks for playing MetroSim. Have a nice day!" << std::endl;
                        return;
                }
                sim.printAll();
                std::cout << "Command? "; 
                char letter;
                infile >> letter;
                 if (letter == 'p') {
                        int arrival;
                        int departure;
                        infile >> arrival >> departure;
                        sim.passengerCommand(arrival, departure);
                } else if (letter == 'm') {
                        char input2;
                        infile >> input2;
                        if (input2 == 'm') {
                                sim.trainCommand();
                        } else if (input2== 'f') {
                                sim.endCommand();
                                turn = 1;
                        }
                }
        }
        sim.printOutput(outputFile);
        infile.close();
        return;
}