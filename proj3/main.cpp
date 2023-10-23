/*
 *  main.cpp
 *  Sara Francis and Sara Svahn
 *  4/11
 *
 *  CS 15 Project 3: Gerp
 *
 *  This file is the client file of the program where the functions of FileSort
 *  are implemented and starts the program
 *  Calls all necessary FileSort functions to search and sort data
 *
 */

#include <iostream>
#include "FileSort.h"
#include "HashSort.h"
#include "FSTreeTraversal.cpp"
#include "stringProcessing.h"
using namespace std;

void parse_command_line(int argc, char *argv[], FileSort &sorting);
void read_in_tree(FileSort &sorting);
void run_query_loop(string outputFile, FileSort &sorting);
void query_user(string command, FileSort &sorting, ostream &outfile);
void search(string command, FileSort &sorting, ostream &outfile);
void searchI(string command, FileSort &sorting, ostream &outfile);

/*
 * name:      main 
 * purpose:   Call the necessary functions to run the program 
 * arguments: argc and *argv[] from the command line 
 * returns:   0 when it's done
 * effects:   None
 */ 
int main(int argc, char *argv[]) {
    FileSort sorting;
    parse_command_line(argc, argv, sorting); 
    return 0;
}

/*
 * name:      parse_command_line(int argc, char *argv[], FileSort &sorting) 
 * purpose:   Parse the command line 
 * arguments: argc and argv[], instance of the FileSort class 
 * returns:   None
 * effects:   None
 */ 
void parse_command_line(int argc, char *argv[], FileSort &sorting) {
    if (argc != 3) {
        cerr << "Usage : ./ gerp inputDirectory outputFile" << endl;
        exit(EXIT_FAILURE);
    }
    string directoryName = argv[1];
    string outputFile = argv[2];
    create_tree(directoryName); 
    read_in_tree(sorting);
    run_query_loop(outputFile, sorting);
}

/*
 * name:      read_in_tree(FileSort &sorting) 
 * purpose:   Read in the files from the tree 
 * arguments: Instance of the FileSort class 
 * returns:   None
 * effects:   Opens and closes the file that contains the paths to be read in 
 */ 
void read_in_tree(FileSort &sorting) {
    ifstream in; 
    in.open("pathList.txt");
    if (not in.is_open()) {
        cerr << "Error: could not open file " << "pathList.txt" << endl;
        exit(EXIT_FAILURE);
    }
    string path; 
    while (getline(in, path)) { // gets and sorts all lines in the file 
        sorting.processFile(path);
    }
    in.close(); 
}

/*
 * name:      run_query_loop(string outputFile, FileSort &sorting) 
 * purpose:   Continously queries commands and runs the appropriate operations 
 * arguments: Output file to print to, instance of the FileSort class 
 * returns:   None
 * effects:   None 
 */ 
void run_query_loop(string outputFile, FileSort &sorting) {
    ofstream outfile;
    outfile.open(outputFile);
    string command = "";
    while (command != "@q" and command != "@quit") {
        cout << "Query? ";
        cin >> command;
        if (command == "@i" or command == "@insensitive") { // insensitive
            cin >> command; 
            searchI(command, sorting, outfile);
        } else if (command == "@f") { // change output file 
            string newOutputFilename; 
            cin >> newOutputFilename;
            outfile.close();
            outfile.open(newOutputFilename);
        } else if (command == "@q" or command == "@quit") { // quit
            outfile.close();
            cout << "Goodbye! Thank you and have a nice day." << endl;
            return; 
        } else if (cin.eof()) { // also quit
            outfile.close();
            cout << "Query? ";
            cout << "Goodbye! Thank you and have a nice day." << endl;
            return; 
        } else { // any string
            search(command, sorting, outfile);
        }
    }
}

/*
 * name:      search(string command, FileSort &sorting, ostream &outfile)
 * purpose:   Perform regular search 
 * arguments: Command (word to search for), instance of FileSort class, output
              file to print to 
 * returns:   None
 * effects:   None 
 */ 
void search(string command, FileSort &sorting, ostream &outfile) {
    string str = stripNonAlphaNum(command); 
    if (str.length() != 0) {
        sorting.searchHash(str, outfile);
    } else {
        outfile << str << " Not Found. Try with @insensitive or @i." <<
        endl;
    }
}

/*
 * name:      searchI(string command, FileSort &sorting, ostream &outfile)
 * purpose:   Perform case insensitive search 
 * arguments: Command (word to search for), instance of FileSort class, output
              file to print to 
 * returns:   None
 * effects:   None 
 */ 
void searchI(string command, FileSort &sorting, ostream &outfile) {
    string str = stripNonAlphaNum(command); 
    if (str.length() != 0) {
        sorting.searchInsensitive(str, outfile);
    } else {
        outfile << str << " Not Found." << endl;
    }
}