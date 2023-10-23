/*
 *  DatumStack.cpp
 *  Sara Francis
 *  2/27
 *
 *  CS 15 Project 2: CalcYouLater
 *
 * Function Definitions for the DatumStack Class
 *
 */

#include "Datum.h"
#include "DatumStack.h"
#include <list>
#include <sstream>

/*
 * name:      DatumStack()
 * purpose:   Default constructor
 * arguments: None
 * returns:   none
 * effects:   Initialize variables
 */
DatumStack::DatumStack() {
    stackSize = 0;
}

/*
 * name:      DatumStack()
 * purpose:   Initiliaze stack of an array of Datum
 * arguments: Array of Datum and its size
 * returns:   none
 * effects:   Initialize stack
 */
DatumStack::DatumStack(Datum arr[], int size) {
    for (int i = 0; i < size; i++) {
        Datum elem = arr[i];
        push(elem);
    }
    stackSize = size;
}

/*
 * name:      pop()
 * purpose:   Remove top element from the stack
 * arguments: None
 * returns:   none
 * effects:   Remove an element
 */
void DatumStack::pop() {
    runtimeError();
    stack.pop_front();
    stackSize--;
}

/*
 * name:      push()
 * purpose:   Adds element to the front of the stack
 * arguments: Datum object to add
 * returns:   none
 * effects:   Increases size
 */
void DatumStack::push(Datum object) {
    stack.push_front(object);
    stackSize++;
}

 /* name:     top()
 * purpose:   Gets element at the top of the stack
 * arguments: None
 * returns:   Datum at the top of the first 
 * effects:   None
 */
Datum DatumStack::top() {
    runtimeError();
    Datum result(stack.front());
    return result;
}

 /* name:     clear()
 * purpose:   Removes all element in the stack
 * arguments: None
 * returns:   nothing
 * effects:   size is zero
 */
void DatumStack::clear() {
    int length = stackSize;
    for (int i = 0; i < length; i++) {
        pop();
    }
}

 /* name:     isEmpty()
 * purpose:   Checks if the stack is empty
 * arguments: None
 * returns:   true if empty false if its not
 * effects:   none
 */
bool DatumStack::isEmpty() {
    if (stackSize == 0) {
        return true;
    } else {
        return false;
    }
}

/* name:     size()
 * purpose:   checks the size of the stack
 * arguments: None
 * returns:   the size of the stack
 * effects:   none
 */
int DatumStack::size() {
    return stackSize;
}

/* name:      runtimeError()
 * purpose:   checks if the stack is empty and throws an error
 * arguments: None
 * returns:   Error
 * effects:   Throws an exception
 */
void DatumStack::runtimeError() {
    if (isEmpty()) {
        throw std::runtime_error("empty_stack");
    }
}

/* name:      print()
 * purpose:   prints all elements of the stack
 * arguments: None
 * returns:   Elements to cout
 * effects:   None
 */
std::string DatumStack::print() {
    std::stringstream ss;
    ss << "{ ";
    std::list<Datum>::iterator iterator;
    for (iterator = stack.begin(); iterator != stack.end(); iterator++) {
        std::string printThis = iterator->toString();
        ss << printThis;
        ss << " ";
    }
    ss << "}";
    return ss.str();
}