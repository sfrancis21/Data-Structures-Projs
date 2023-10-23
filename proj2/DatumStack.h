/*
 *  DatumStack.h
 *  Sara Francis
 *  2/26
 *
 *  CS 15 Project 2: CalcYouLater
 *
 * This is the class declarations for the DatumStack class
 * It is responsible for creating a stack of datum objects and the functions
 * used to add, remove, and inspect elements from the stack
 * 
 */

#ifndef DATUM_STACK_H
#define DATUM_STACK_H

#include "Datum.h"
#include <list>

class DatumStack {

public:

    //Constructors
    DatumStack();
    DatumStack(Datum arr[], int size);

    //Adding or Removing or Getting Datum
    void pop();
    void push(Datum object);
    Datum top();

    //Clear, Empty Check, and Size check
    void clear();
    bool isEmpty();
    int size();



private:
    //Throws Exceptions
    void runtimeError();

    //Number of elements in the stack
    int stackSize;

    std::list<Datum> stack;

    //Printing for Tests
    std::string print();


}; 

#endif
