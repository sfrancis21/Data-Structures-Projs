/*
 *  FileSort.h
 *  Sara Francis and Sara Svahn
 *  4/9
 *
 *  CS 15 Project 3: Gerp
 *
 *  Class declarations for the FileProcessor class
 *  Responsible for processing all files from the tree
 *
 */
#include "HashSort.h"
#ifndef FileSort_H
#define FileSort_H

class FileSort {

public: 
    FileSort();
    ~FileSort();

    //Process tree functions called from main.cpp
    void processFile(std::string filename); 

    //Search functions called from main.cpp
    void searchHash(string word, ostream &output);
    void searchInsensitive(string word, ostream &output);

private: 

    //Functions to open file and sort the lines
    void openFile(std::string filename); 
    void sortLine(std::string line, int lineNum, std::string filename);

    //Prints out search results to file
    void printLines(set<int> indices, ostream &output);

    //Struct for vector of data
    struct lineInfo {
        string filePath;
        string line; 
        int lineNum; 
    };

    vector<lineInfo> lineList; 

    HashSort hash; 

}; 

#endif 