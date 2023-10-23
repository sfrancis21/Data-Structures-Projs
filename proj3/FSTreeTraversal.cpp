/*
 *  FSTreeTraversal.cpp
 *  Sara Francis and Sara Svahn
 *  4/7
 *
 *  CS 15 Project 3: Gerp
 *
 *  Functions for traversing FSTrees
 *
 */
#include <iostream>
#include <fstream>
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

//string parse_command_line(int argc, char *argv[]);
void create_tree(string directoryName);
void tree_traversal_helper(DirNode *node, string pathName, ostream &out);

/*
 * name:      create_tree()
 * purpose:   Creates tree from directory name
 * arguments: Directory name to act as the root
 * returns:   none
 * effects:   Creates tree
 */
void create_tree(string directoryName) {
    FSTree tree(directoryName); 
    ofstream out;
    out.open("pathList.txt");
    tree_traversal_helper(tree.getRoot(), tree.getRoot()->getName(), out);
    out.close();
}

/*
 * name:      tree_traversal_helper()
 * purpose:   Traverses tree and prints out all files with pathways
 * arguments: Node to act as root and pathName to keep track of location
 * returns:   none
 * effects:   Prints out all files with their pathways 
 */
void tree_traversal_helper(DirNode *node, string pathName, ostream &out) {
    if (node == nullptr) {
        return;
    } else if (node->numSubDirs() == 0) { // base case
        int numFiles = node->numFiles();
        for (int n = 0; n < numFiles; n++) {
            out << pathName << "/" << node->getFile(n) << endl;
        }
        return;
    } else {
        int numFiles = node->numFiles();
        int numSubs = node->numSubDirs();
        // loop thru print out files
        for (int n = 0; n < numFiles; n++) {
            out << pathName << "/" << node->getFile(n) << endl;
        }
        // loop thru recurse into subdirectories
        for (int n = 0; n < numSubs; n++) {
            tree_traversal_helper(node->getSubDir(n), 
            pathName + "/" + node->getSubDir(n)->getName(), out);
        }
    }
}