/*
 *  RPNCalc.h
 *  Sara Francis
 *  3/3/22
 *
 *  CS 15 Project 2: CalcYouLater
 *
 * This is the class declarations for the RPNCalc class
 * It is responsible for taking in commands and performing different tasks
 * with elements in the DatumStack (operators on ints, boolean operatio
 * etc)
 * 
 */

#ifndef RPN_CALC_H
#define RPN_CALC_H

#include "DatumStack.h"
#include "Datum.h"

class RPNCalc {

public:

    RPNCalc();
    ~RPNCalc();

    //Gets command and calls function
    void run();

private:

    //Stack for all Datum
    DatumStack calc_stack;

    //Keeps track of main run loop
    int turn;

    //Keep track of empty stack error
    int errorCount;
    
    //Print Command
    void calcPrint();
    
    //Private helper function for run and exec
    void processCommand(std::string command);

    //False Boolean Command
    void falseBool();

    //Not Command
    void notCommand();

    //Clear Command
    void clearCommand();

    //Dup Command
    void dup();

    //Drop Command
    void drop();

    //Swap Command
    void swap();

    //Quit Command
    void quit();

    //Simple Operator Check
    bool simpleOpCheck(std::string command);

    //Get top element
    Datum topElem();

    //Inequality operator check
    bool inequalCheck(std::string command);

    //Gets result from inequality operator 
    bool inequalResult(std::string command, int num1, int num2);

    //Get integer for Datum and catch error if its not an int
    void checkInt(Datum num);

    //Integer Command
    void addInt(int value);

    //Simple Operator Command
    void simpleOp(std::string command);

    //Calculate the answer of the operator applied to two ints
    int calcResult(std::string command, int num1, int num2);

    //Inequality Operator Command
    void inequalOp(std::string command);

    //True Boolean Command
    void trueBool();

    //rString Command
    void addString(std::string command);

    //exec Command
    void exec(std::string ifCommand);

    //file Command
    void file();

    //Reads in commands from file
    void readFile(std::string fileName);

    //file check
    bool fileCheck(std::string command);

    //if Command
    void ifCondition();
}; 

#endif


