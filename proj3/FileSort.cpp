/*
 *  FileSort.cpp
 *  Sara Francis and Sara Svahn
 *  4/9
 *
 *  CS 15 Project 3: Gerp
 *
 *  Functions for opening and processing a file 
 *
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "FileSort.h"
#include "HashSort.h"
#include "stringProcessing.h"

using namespace std;

/*
 * name:      Constructor
 * purpose:   Initialize instance of FileSort 
 * arguments: None
 * returns:   None
 * effects:   Empty
 */ 
FileSort::FileSort() {

}

/*
 * name:      Destructor
 * purpose:   Free all heap allocated space, but that is done in HashSort
 * arguments: None
 * returns:   None
 * effects:   Empty
 */ 
FileSort::~FileSort() {
    
}

/*
 * name:      processFile(string filename)
 * purpose:   Calls function to open and process file
 * arguments: filename to get information from
 * returns:   nothing
 * effects:   None
 */ 
void FileSort::processFile(string filename) {
    openFile(filename);
}

/*
 * name:      openFile(string filename)
 * purpose:   Reads in each line from the file 
 * arguments: filename to read in data from
 * returns:   nothing
 * effects:   None
 */ 
void FileSort::openFile(string filename) {
    ifstream infile;
    infile.open(filename);

    if (not infile.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line; 

    int lineNum = 1;
    while(getline(infile, line)) {
        if (line.length() != 0) { // call sort line on each line in file 
            sortLine(line, lineNum, filename);
        }
        lineNum++;
    }

    infile.close();
}

/*
 * name:      sortLine(string line, int lineNum, string filename)
 * purpose:   Gets each word from the line and calls hash function to insert
            it into each hash table. It also adds info into the vector 
            and gets the index to be stored with the word in the hash table
 * arguments: Line to get words from, lineNum is the line number and then the
                filename to store
 * returns:   Nothing
 * effects:   Increases size of vector and calls HashSort functions
 */ 
void FileSort::sortLine(string line, int lineNum, string filename) {

    lineInfo item; // create lineInfo struct instance 
    item.line = line;
    item.filePath = filename;
    item.lineNum = lineNum; 
    lineList.push_back(item); 

    int index = lineList.size() - 1; 

    istringstream ss(line);
    string word; 
    while (ss >> word) {
        string strippedWord = stripNonAlphaNum(word); // strip word 
        if (strippedWord != "") { // make sure it's still a word
            hash.insertWrapper(index, strippedWord); // hash into main hash
            hash.insertPermWrapper(strippedWord); // hash into permutations hash
        }
    }
}

/*
 * name:      searchInsensitive(string word, ostream &output)
 * purpose:   Searches for a word while ignoring capitalization
 * arguments: Word to search and the output stream to print to
 * returns:   nothing
 * effects:   Calls HashSort functions and may print to output stream
 */ 
void FileSort::searchInsensitive(string word, ostream &output) {
    set<int> indices;
    indices = hash.insensitiveSearch(word); // call insensitive search
    if (not indices.empty()) {
        printLines(indices, output);
    } else { 
        output << word << " Not Found." << endl;
    }
}

/*
 * name:      searchHash(string word, ostream &output)
 * purpose:   Searches for a word in the directory
 * arguments: Word to search and the output stream to print to
 * returns:   nothing
 * effects:   Calls HashSort functions and may print to output stream
 */ 
void FileSort::searchHash(string word, ostream &output) {
    set<int> indices;
    indices = hash.search(word); // call regular search
    if (not indices.empty()) {
        printLines(indices, output);
    } else {
        output << word << " Not Found. Try with @insensitive or @i." << endl;
    }
}

/*
 * name:      printLines(set<int> indices, ostream &output)
 * purpose:   Print path, line number, and line that contains searched for word
 * arguments: Set of indices to get information from and the output stream
 * returns:   nothing
 * effects:   Prints information to output file
 */ 
void FileSort::printLines(set<int> indices, ostream &output) {
    for (auto it = indices.begin(); it != indices.end(); it++) {
        output << lineList.at(*it).filePath << ":" << lineList.at(*it).lineNum
        << ": " << lineList.at(*it).line << endl; 
    }
}
