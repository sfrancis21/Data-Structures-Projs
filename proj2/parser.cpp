/*
 *  parser.cpp
 *  Sara Francis
 *  2/27
 *
 *  CS 15 Project 2: CalcYouLater
 *
 * This is the file used to parse the Rstrings sent in through the command 
 * line to return the input as one single string
 * 
 */

#include <iostream>

/* name:     parseRString()
 * purpose:   Parses rstring and turns it into a std::string
 * arguments: istream input (most likely std::cin)
 * returns:   the string version of the input
 * effects:   none
 */
std::string parseRString(std::istream &input) {
    std::string symbol;
    std::string new_string;

    while (symbol != "}") {
        input >> symbol;
        
        if (symbol == "{") {
            new_string = new_string + " " + parseRString(input);
 
        } else {
            new_string = new_string + " " + symbol;
        }
    }

    new_string = "{" + new_string;
    return new_string;
}


