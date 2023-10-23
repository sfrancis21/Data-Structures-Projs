/*
 *  stringProcessing.cpp
 *  Sara Francis and Sara Svahn
 *  4/7
 *
 *  CS 15 Project 3: Gerp
 *
 *  Functions and helpers for stripping leading/trailing non alphanumeric chars
 *
 */
#include <iostream>
#include "stringProcessing.h"

using namespace std;


/*
 * name:      stripNonAlphaNum(string str)
 * purpose:   Strip the leading and trailing non-alphanumeric characters from a
              string 
 * arguments: Original string
 * returns:   Stripped string
 * effects:   None
 */
string stripNonAlphaNum(string str) {
    int leading = strip_helper(str);
    if (leading == -10) {
        return "";
    }
    string reverse = reverse_string(str);
    int trailing = strip_helper(reverse);
    string result = ""; 
    int length = str.length();
    for (int i = leading; i < length - trailing; i++) {
        result += str[i]; 
    }
    return result; 
}

/*
 * name:      strip_helper(string str)
 * purpose:   Finds the number of leading non-alphanumeric characters in a 
              string
 * arguments: String with potential leading non-alphanumeric chars 
 * returns:   Integer of the number of leading 
 * effects:   None
 */
int strip_helper(string str) {
    bool found = false; 
    int i = 0; 
    int length = str.length();
    while (not found) {
        if (str[i] >= 48 and str[i] <= 57) {
            found = true; 
        } else if (str[i] >= 65 and str[i] <= 90) {
            found = true; 
        } else if (str[i] >= 97 and str[i] <= 122) {
            found = true;
        } else if (i >= length) {
            //found = true; 
            return -10;
        }
        i++;
    }
    return i - 1; 
}

/*
 * name:      reverse_string(string str)
 * purpose:   Reverses a string
 * arguments: Original String
 * returns:   Reversed String
 * effects:   None
 */
string reverse_string(string str) {
    string reverse = ""; 
    for (int i = str.length() - 1; i >= 0; i--) {
        reverse += str[i];
    }
    return reverse; 
}

// We tested with non alphanumeric on both sides, one side, and neither side
// We also checked with them in the middle 
// 
// int main() {
//     string word = "comp-15"; 
//     cout << "testing on " << word << endl; 
//     cout << stripNonAlphaNum(word) << endl;
//     return 0; 
// }