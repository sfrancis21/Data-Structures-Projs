/*
 *  unit_tests.h
 *  Sara Francis
 *  2/26
 *
 *  CS 15 Project 2: CalcYouLater
 *
 *  This file is for testing all of the functions in Datum Stack and parsing
 * from project 2
 */

#include "Datum.h"
#include "DatumStack.h"
#include <cassert>
#include <sstream>
#include <iostream>

/********************************************************************\
*                        CALCYOULATER TESTS                          *
\********************************************************************/


/*For all stack tests the print function was made public*/

//Creating a Stack
void create_stack_test() {
    Datum one(1);
    Datum two("hello");
    Datum three(false);
    Datum four("hi");
    Datum arr[4] = {one, two, three, four};
    int size = 4;
    DatumStack stack(arr, size);
    assert(stack.print() == "{ hi #f hello 1 }");
}

//Check is identifies empty stacks
void isEmpty_test() {
    //Empty
    DatumStack stack;
    assert(stack.isEmpty() == true);

    //Filled
    DatumStack stack2;
    Datum one(3);
    stack2.push(one);
    assert(stack2.isEmpty() == false);
}

//Adding to a stack that is empty and filled
void addStack_test() {
    //Empty Stack
    DatumStack stack2;
    Datum one2(1);
    stack2.push(one2);
    assert(stack2.print() == "{ 1 }");

    //Filled Stack
    Datum one(1);
    Datum two("hello");
    Datum three(false);
    Datum four("hi");
    Datum arr[3] = {one, two, three};
    int size = 3;
    DatumStack stack(arr, size);
    stack.push(four);
    assert(stack.print() == "{ hi #f hello 1 }");
}

//Removing from a empty stack
void removeStackElemEmpty_test() {
    DatumStack stack;

    // var to track whether range_error is thrown
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        stack.pop();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

//Removing from one elem stack and filled stack
void removingElem_test() {
    //One Elem Stack
    DatumStack stack2;
    Datum one2(1);
    stack2.push(one2);
    stack2.pop();
    assert(stack2.print() == "{ }");

    //Filled Stack
    Datum one(1);
    Datum two("hello");
    Datum three(false);
    Datum arr[3] = {one, two, three};
    int size = 3;
    DatumStack stack(arr, size);
    stack.pop();
    assert(stack.print() == "{ hello 1 }");
}

//Checks it throws error for getting top elem in empty stack
void noFront_test() {
    DatumStack stack;

    // var to track whether range_error is thrown
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        stack.top();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

//Gets front for filled stack
void getFront_test() {
    //One Elem Stack
    DatumStack stack2;
    Datum one2(1);
    stack2.push(one2);
    Datum test(stack2.top());
    assert(test.toString() == "1");

    //Filled Stack
    Datum one(1);
    Datum two("hello");
    Datum three(false);
    Datum arr[3] = {one, two, three};
    int size = 3;
    DatumStack stack(arr, size);
    Datum test2(stack.top());
    assert(test2.toString() == "#f");
}

//Tests that the stack is cleared properly
void clearStack_test() {
    Datum one(1);
    Datum two("hello");
    Datum three(false);
    Datum arr[3] = {one, two, three};
    int size = 3;
    DatumStack stack(arr, size);
    stack.clear();
    assert(stack.print() == "{ }");
}

//Gets size properly for empty/filled stack
void getSize_test() {
    //Empty Stack
    DatumStack stack2;
    assert(stack2.size() == 0);

    //Filled Stack
    Datum one(1);
    Datum two("hello");
    Datum three(false);
    Datum arr[3] = {one, two, three};
    int size = 3;
    DatumStack stack(arr, size);
    assert(stack.size() == 3);
}