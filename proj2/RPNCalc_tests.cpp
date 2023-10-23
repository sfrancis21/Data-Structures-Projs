/*
 *  RPNCalc_tests.cpp
 *  Sara Francis
 *  3/3/22
 *
 *  CS 15 Project 2: CalcYouLater
 *
 *  This file is for testing functions in the RPNCalc class
 */

#include "RPNCalc.h"
#include <iostream>

//void addInt_test(RPNCalc test);
//void addBool_test(RPNCalc test);
//void notCommand_test(RPNCalc test);
//void clear_test(RPNCalc test);
//void dup_test(RPNCalc test);
//void swap_test(RPNCalc test);
//void quit_test(RPNCalc test);
//void simpleOp_test(RPNCalc test);
//void inequalOp_test(RPNCalc test);
//void addString_test(RPNCalc test);

int main() {
    RPNCalc sim;

    //addInt_test(sim);
    //addBool_test(sim);
    //notCommand_test(sim);
    //clear_test(sim);
    //dup_test(sim);
    //swap_test(sim);
    //quit_test(sim);
    //simpleOp_test(sim);
    //inequalOp_test(sim);
    //addString_test(sim);

    return 0;
}

//Tests adding integers and printing them from the stack
//Checks that the number 5 is printed out
// void addInt_test(RPNCalc test) {
//     int num = 5;
//     test.addInt(num);
//     test.calcPrint();
// }

//Tests both the drop function and adding true/false boolens to the stack
//Tests that true and false are added properly and false is then printed
// void addBool_test(RPNCalc test) {
//     test.trueBool();
//     test.falseBool();
//     test.calcPrint();
//     test.drop();
//     test.calcPrint();
// }

//Tests the notCommand function
//Makes sure the boolean that is printed is the opposite of the one added
// void notCommand_test(RPNCalc test) {
//     test.trueBool();
//     test.notCommand();
//     test.calcPrint();
// }

//Test for the clearCommand function and empty print case
//Makes sure that all elements added to the stack are removed and the error
//for trying to print an empty stack is correct
// void clear_test(RPNCalc test) {
//     int num = 1;
//     test.addInt(num);
//     test.calcPrint();
//     int num2 = 2;
//     test.addInt(num2);
//     test.calcPrint();
//     int num3 = 3;
//     test.addInt(num3);
//     test.calcPrint();

//     test.clearCommand();
//     test.calcPrint();

// }

//Test for the dup function
//Tests for a element at trying to duplicate an empty stack
// void dup_test(RPNCalc test) {
//     int num = 1;
//     test.addInt(num);
//     test.dup();
//     test.calcPrint();
//     test.drop();
//     test.calcPrint();

//     //Empties stack and tries to duplicate top element
//     test.drop();
//     test.dup();
// }

//Test for swap function
//Tests that it swaps two elements but also prints error if there
//are not
//two elements to swap
// void swap_test(RPNCalc test) {
//     int num = 1;
//     int num2 = 2;
//     test.addInt(num);
//     test.addInt(num2);

//     test.swap();
//     test.calcPrint();

//     test.drop();
//     test.drop();

//     test.swap();
// }

//Tests the quit function
// void quit_test(RPNCalc test) {
//     test.quit();
// }

//Tests the simpleOp function
//Makes sure it delivers the correct result for each operand
//I changed the string command to test each one
//Tested cases with 0 as an integer and results that would give
//negative numbers or undefined values (ex: 2\0)
//Also tested for cases where the top two datum are not integers
//void simpleOp_test(RPNCalc test) {
    //test.trueBool();
    // int num2 = 0;
    // test.addInt(num2);
    // int num = 3;
    // std::string command = "+";
    // test.addInt(num);
    // test.simpleOp(command);
    // test.calcPrint();
//}

//This is the test for inequalOp command
//Tests different operators for both true and false cases and 
//different datum types (int, rstring, etc)
//I changed the string command to test each one to avoid rewriting
// void inequalOp_test(RPNCalc test) {
//     int num = 5;
//     int num2 = 4;
//     test.addInt(num);
//     test.addInt(num2);
//     std::string command = "==";
//     test.inequalOp(command);
//     test.calcPrint();
// }

//This is the test for the addString Command
//Makes sure regular rStrings and nested rStrings are properly added
//Checks that unbalanced rStrings are not added
// void addString_test(RPNCalc test) {
//     test.run();
// }