/*
 *  HashSort.cpp
 *  Sara Francis and Sara Svahn
 *  4/11
 *
 *  CS 15 Project 3: Gerp
 *
 *  Implementation of the hash table of lines in files
 *
 */

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <fstream>
#include "HashSort.h"

using namespace std;

/*
 * name:      constructor 
 * purpose:   Initialzes the two hash tables and their member variables 
 * arguments: None
 * returns:   None
 * effects:   Every index in both hash tables set to nullptr 
 */ 
HashSort::HashSort() {
    tableSize = 100;
    numItems = 0;
    permSize = 100; 
    permNumItems = 0; 

    chainTable = new hashNode *[tableSize];
    permTable = new caseNode *[permSize];

    for (int i = 0; i < tableSize; i++) {
        chainTable[i] = nullptr;
        permTable[i] = nullptr;
    }

}

/*
 * name:      destructor 
 * purpose:   Frees any heap allocated space 
 * arguments: None
 * returns:   None
 * effects:   None
 */ 
HashSort::~HashSort() {
    for (int i = 0; i < tableSize; i++) {
        deleteList(chainTable[i]);
    }
    for (int i = 0; i < permSize; i++) {
        deletePermList(permTable[i]);
    }
    delete [] chainTable;
    delete [] permTable;
}


/*
 * name:      deleteList(hashNode *node) 
 * purpose:   Deletes all the nodes in the chained list at an index of the 
              hash table 
 * arguments: Node to delete 
 * returns:   None
 * effects:   Recursively calls itself
 */ 
void HashSort::deleteList(hashNode *node)
{
    if (node == nullptr) {
        return;  
    }
    deleteList(node->next); 
    delete node; 
}

/*
 * name:      deletePermList(caseNode *node) 
 * purpose:   Deletes all the nodes in the chained list at an index of the  
              perm table 
 * arguments: Node to delete 
 * returns:   None
 * effects:   Recursively calls itself 
 */ 
void HashSort::deletePermList(caseNode *node)
{
    if (node == nullptr) {
        return;  
    }
    deletePermList(node->next); 
    delete node; 
}

/*
 * name:      insertWrapper(int index, string word) 
 * purpose:   Call the private insert function with more parameters 
 * arguments: Index of the word in the lineList, word to insert 
 * returns:   None
 * effects:   None 
 */ 
void HashSort::insertWrapper(int index, string word) {
    insert(index, word, chainTable); 
}

/*
 * name:      insert(int index, string word, hashNode **&table) 
 * purpose:   Inserts a word into the hash table with its data 
 * arguments: Index of the word in the line list, the word, and the table to
              insert into 
 * returns:   None
 * effects:   Calls expand if necessary 
 */ 
void HashSort::insert(int index, string word, hashNode **&table) {
    size_t key = std::hash<string>{}(word);
    int hashIndex = key % tableSize;
    if (numItems >= tableSize * 4) {
        expandHash();
    }
    hashing(index, word, hashIndex, table); 
}

/*
 * name:      hashing(int index, string word, int hashIndex, hashNode **&table) 
 * purpose:   Helper function for insert, inserts a word into the hash table
              either as the first node at that index, a new node at that index,
              or a node that already exists in which case the indices set 
              changes 
 * arguments: Index of the word in the lineList, the word, the index to insert
              it in the hash, and the hash table to insert it into 
 * returns:   None
 * effects:   None
 */ 
void HashSort::hashing(int index, string word, int hashIndex, hashNode
**&table) {
    if (table[hashIndex] == nullptr) { // first node at this index 
        hashNode *newHashNode = newNode(word, index);
        table[hashIndex] = newHashNode; 
        numItems++;
    } else {
        int length = listLength(table[hashIndex]); 
        hashNode *curr = table[hashIndex];
        if (length == 1) { // loop below doesn't include this case 
            if (table[hashIndex]->word == word) { // word already in table
                curr->indices.insert(index); // add to set of indices
                return; 
            }
        }
        while (curr != nullptr) {
            if (curr->word == word) { // word already in table 
                curr->indices.insert(index); // add to set of indices 
                return; 
            }
            if (curr->next == nullptr) { // make a new node, chain it 
                hashNode *newHashNode = newNode(word, index);
                curr->next = newHashNode; 
                numItems++;
                return;
            }
            curr = curr->next; 
        }
    }
}

/*
 * name:      insertPermWrapper(string word) 
 * purpose:   Calls the private function with more parameters 
 * arguments: Word to insert
 * returns:   None
 * effects:   None
 */ 
void HashSort::insertPermWrapper(string word) {
    insertPerm(word, permTable);
}

/*
 * name:      insertPerm(string word, caseNode **&table) 
 * purpose:   Insert a word into the permutations hash with its data
 * arguments: Word to insert, hash table to insert into
 * returns:   None
 * effects:   Calls expand if necessary 
 */ 
void HashSort::insertPerm(string word, caseNode **&table) {
    string lower = "";
    for (size_t i = 0; i < word.length(); i++) {
        lower += tolower(word[i]);
    }
    size_t key = std::hash<string>{}(lower); 
    int permIndex = key % permSize; 
    if (permNumItems == permSize * 2) {
        expandPermHash(); 
    }
    hashingPerm(word, lower, permIndex, table);
}

/*
 * name:      hashingPerm(string word, string lower, int permIndex, caseNode
              **&table) 
 * purpose:   Helper function for insertPerm, inserts a word into the hash of 
              permutations either as the first node in that index, a new node at
              that index, or a node that already exists in which case the 
              permutations set changes 
 * arguments: Word to insert, lowercase version of the word, index of the 
              permutations hash to insert it at, hash table to insert into 
 * returns:   None
 * effects:   None
 */ 
void HashSort::hashingPerm(string word, string lower, int permIndex, 
caseNode **&table) {
    if (table[permIndex] == nullptr) { // first node at this index 
        caseNode *newcNode = newCaseNode(word, lower);
        table[permIndex] = newcNode;
        permNumItems++;
    } else {
        int length = permListLength(table[permIndex]);
        caseNode *curr = table[permIndex];
        if (length == 1) { // below loop doesn't account for this case 
            if (table[permIndex]->word == lower) { // word already in hash 
                curr->permutations.insert(word); // add to set of permutations
                return; 
            }
        }
        while (curr != nullptr) {
            if (curr->word == lower) { // word already in hash 
                curr->permutations.insert(word); // add to set of permutations
                return; 
            } 
            if (curr->next == nullptr) { // make a new node, chain it
                caseNode *newcNode = newCaseNode(word, lower);
                curr->next = newcNode; 
                permNumItems++;
                return;
            }
            curr = curr->next; 
        }
    }
}

/*
 * name:      newCaseNode(string word, string lower) 
 * purpose:   Creates a new caseNode
 * arguments: Word and its lowercase version
 * returns:   Pointer to the new caseNode
 * effects:   None 
 */ 
HashSort::caseNode* HashSort::newCaseNode(string word, string lower) {
    caseNode* np = new caseNode();
    np->word = lower; 
    np->permutations.insert(word);
    np->next = nullptr; 
    return np;
}

/*
 * name:      newNode(string word, int index) 
 * purpose:   Creates a new hashNode
 * arguments: Word and its index in the lineList vector 
 * returns:   Pointer to the new hashNode
 * effects:   None
 */ 
HashSort::hashNode* HashSort::newNode(string word, int index) {
    hashNode* np = new hashNode();
    np->indices.insert(index); 
    np->next = nullptr; 
    np->word = word; 
    return np;
}

/*
 * name:      permListLength(caseNode *curr) 
 * purpose:   Finds the length of the chained list at an index of the 
              permutations hash 
 * arguments: Pointer to the current caseNode
 * returns:   The length as an integer 
 * effects:   Recursively calls itself 
 */ 
int HashSort::permListLength(caseNode *curr)
{
    if (curr == nullptr) { // base case 
        return 0;
    } else { // recursive case 
        return 1 + permListLength(curr->next);
    }
}

/*
 * name:      listLength(hashNode *curr) 
 * purpose:   Finds the length of the chained list at an index of the main hash
 * arguments: Pointer to the current hashNode
 * returns:   The length as an integer
 * effects:   Recursively calls itself 
 */ 
int HashSort::listLength(hashNode *curr)
{
    if (curr == nullptr) {
        return 0;
    } else {
        return 1 + listLength(curr->next);
    }
}

/*
 * name:      print() 
 * purpose:   Prints the hash
 * arguments: None
 * returns:   None
 * effects:   Calls helper function, commented out because only used for testing
 */ 
// void HashSort::print()
// {
//     cout << "hash table size is " << tableSize << endl;
//     for (int i = 0; i < permSize; i++) {
//         caseNode *curr = permTable[i];
//         cout << i << ": " << endl;
//         while (curr != nullptr) {
//             printHashNode(curr);
//             curr = curr->next;
//             if (curr != nullptr) {
//                 cout << endl;
//             }
//         }
//         cout << endl << endl;
//     }
//     cout << "finished printing" << endl;
// }

/*
 * name:      printHashNode(caseNode *curr) 
 * purpose:   Prints a node of the hash 
 * arguments: The node to print (either caseNode or hashNode we switched back
              and forth)
 * returns:   None
 * effects:   Commented out because only used for testing purposes 
 */ 
// void HashSort::printHashNode(caseNode *curr)
// {
//     cout << "word:  " << curr->word << "----";
//     cout << " set of perms: "; 
//     for (auto iterator = curr->permutations.begin(); 
//     iterator != curr->permutations.end(); iterator++) {
//         cout << *iterator << " ";
//     }
// }

/*
 * name:      search(string word) 
 * purpose:   Searches for a word in the hash table 
 * arguments: Word to search for
 * returns:   A set of indices that the word is at in the lineList vector 
 * effects:   None 
 */ 
set<int> HashSort::search(string word) {
    size_t key = std::hash<string>{}(word);
    int hashIndex = key % tableSize;
    hashNode *curr = chainTable[hashIndex];
    while (curr != nullptr) {
        if (curr->word == word) { // found word 
            return curr->indices; 
        }
        curr = curr->next; 
    }
    set<int> emptySet; 
    return emptySet; // word not found, return an empty set 
}

/*
 * name:      insensitiveSearch(string word) 
 * purpose:   Searches for a word in the hash without caring about upper or 
              lower case 
 * arguments: Word to search for 
 * returns:   A set of indices that the word is at in the lineList vector 
 * effects:   None 
 */ 
set<int> HashSort::insensitiveSearch(string word) {
    set<int> allIndices;
    string lower = "";
    for (size_t i = 0; i < word.length(); i++) { // make word lowercase 
        lower += tolower(word[i]);
    }
    size_t permKey = std::hash<string>{}(lower);
    int permIndex = permKey % permSize; 
    caseNode *curr = permTable[permIndex];
    while (curr != nullptr) {
        if (curr->word == lower) { // lowercase word found in permutations hash
            for (auto iterator = curr->permutations.begin(); 
            iterator != curr->permutations.end(); iterator++) {
                string perm = *iterator; 
                set<int> returnedSet = search(perm); // search in main hash 
                for (auto it = returnedSet.begin(); it != returnedSet.end(); 
                it++) { // append returned set to overall set of indices
                    int index = *it;
                    allIndices.insert(index); 
                }
            } 
        }
        curr = curr->next; 
    }
    return allIndices; 
}

/*
 * name:      expandHash  
 * purpose:   Expands the hash table 
 * arguments: None
 * returns:   None
 * effects:   Allocates and frees memory space accordingly
 */ 
void HashSort::expandHash() {    
    int oldSize = tableSize; // keep track of old size for loop 
    tableSize *= 2; // resize table 
    hashNode **newHash = new hashNode *[tableSize]; // create new hash with    
                                                    // more space allocated 
    for (int i = 0; i < tableSize; i++) {
        newHash[i] = nullptr; // initialize every index of new hash to nullptr 
    }
    for (int i = 0; i < oldSize; i++) {
        if (chainTable[i] != nullptr) { // as long as that index isn't empty 
            hashNode *curr = chainTable[i]; 
            while (curr != nullptr) { // loop thru index and rehash every node
                string newWord = curr->word;
                for (auto iterator = curr->indices.begin(); 
                iterator != curr->indices.end(); iterator++) {
                    int index = *iterator;
                    insert(index, newWord, newHash);
                }        
                curr = curr->next;
            }
        }
    }
    for (int i = 0; i < oldSize; i++) { // free allocated memory on the heap 
        deleteList(chainTable[i]);
    }
    delete [] chainTable;
    chainTable = newHash;
}

/*
 * name:      expandPermHash() 
 * purpose:   Expands the permutation hash 
 * arguments: None
 * returns:   None
 * effects:   Allocates and deletes memory space accordingly 
 */ 
void HashSort::expandPermHash() {
    int oldSize = permSize; // save old size for loop
    permSize *= 2; // resize table 
    caseNode **newPerm = new caseNode *[permSize]; // allocate new hash 
    for (int i = 0; i < permSize; i++) {
        newPerm[i] = nullptr; // initialize each index to nullptr 
    }
    for (int i = 0; i < oldSize; i++) {
        if (permTable[i] != nullptr) {
            caseNode *curr = permTable[i]; 
            while (curr != nullptr) { // loop thru index and rehash each node
                for (auto iterator = curr->permutations.begin(); 
                iterator != curr->permutations.end(); iterator++) {
                    string perm = *iterator;
                    insertPerm(perm, newPerm);
                }        
                curr = curr->next;
            }
        }
    }
    for (int i = 0; i < oldSize; i++) { // free allocated heap memory 
        deletePermList(permTable[i]); 
    }
    delete [] permTable; 
    permTable = newPerm; 
}