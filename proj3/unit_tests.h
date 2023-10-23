/*
 *  unit_tests.h
 *  Sara Francis and Sarah Svahn
 *  4/9
 *
 *  CS 15 Project 3: Gerp
 *
 *  This file is for testing all of the functions in project three
 */


#include "FileSort.h"
#include "HashSort.h"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

/********************************************************************\
*                       FileSortTests                          *
\********************************************************************/

// This file was used with different versions of testFile.txt to test that 
void read_file_lines_test() {
    FileSort fp; 
    fp.processFile("testFile.txt");
}

//
// void test_file_path() {
//     FileSort fp;
//     string filename = "proj3-test-dirs/smallGutenberg/www.gutenberg.lib.md"
//      "us/etext96/vpasm10.txt"
//     fp.processFile(filename); 
// }