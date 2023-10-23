/*
 *  HashSort.h
 *  Sara Francis and Sara Svahn
 *  4/11
 *
 *  CS 15 Project 3: Gerp
 *
 *  Class declarations for the HashSort Class
 *  Responsible for sorting info into hash table and searching
 *
 */
 
#ifndef HashSort_H
#define HashSort_H

#include <vector>
#include <set>
//#include <fstream>

using namespace std; 

class HashSort {

public: 
    HashSort();
    ~HashSort();
    
    //Testing Print function
    //void print();

    //Called from FileSort for inserting into chain and perm hash
    void insertWrapper(int index, string word);
    void insertPermWrapper(string word);

    //Called from FileSort to search for case sens and insens
    set<int> search(string word);
    set<int> insensitiveSearch(string word);

private: 

    //Node for chainTable
    struct hashNode {
        string word;
        set<int> indices;
        hashNode* next;
    };

    //Node for permTable
    struct caseNode {
        string word; 
        set<string> permutations; 
        caseNode* next; 
    };
    
    //Declaring our hash tables
    hashNode **chainTable;
    caseNode **permTable;

    //Variables for items and table size of both hashes
    int permSize;
    int permNumItems;

    int tableSize;
    int numItems;

    //New Node functions
    hashNode* newNode(string word, int index);
    caseNode* newCaseNode(string word, string lower);

    //Length of chain at index for both tables
    int listLength(hashNode *curr);
    int permListLength(caseNode *curr);

    //Print functions for testing
    //void printHashNode(caseNode *curr); 

    //Deletes chain of nodes at that index
    void deleteList(hashNode *node);
    void deletePermList(caseNode *node);

    //Expand functions for hash tables
    void expandPermHash();
    void expandHash();

    //Insert functions for hash tables with public wrapper functions
    void insertPerm(string word);
    void insert(int index, string word, hashNode **&table);
    void hashing(int index, string word, int hashIndex, hashNode **&table);
    void insertPerm(string word, caseNode **&table);
    void hashingPerm(string word, string lower, int permIndex, 
    caseNode **&table);

}; 

#endif 