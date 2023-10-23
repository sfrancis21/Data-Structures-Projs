/*
 *  RPNCalc.cpp
 *  Sara Francis
 *  3/3
 *
 *  CS 15 Project 2: CalcYouLater
 *
 * Function Definitions for the RPNCalc Class
 *
 */

#include "RPNCalc.h"
#include "DatumStack.h"
#include "Datum.h"
#include <iostream>
#include <cstdio>
#include <sstream>
#include <fstream>

bool got_int(std::string s, int *resultp);
std::string parseRString(std::istream &input);

/*
 * name:      RPNCalc()
 * purpose:   Default constructor
 * arguments: None
 * returns:   none
 * effects:   Initialize RPNCalc Object
 */
RPNCalc::RPNCalc() {
    errorCount = 0;
    turn = 0;
}

/*
 * name:      ~RPNCalc()
 * purpose:   Deconstructor
 * arguments: None
 * returns:   none
 * effects:   Removes any heap allocated memory that may be initialized
 */
RPNCalc::~RPNCalc() {

}

/*
 * name:      run()
 * purpose:   Takes in commands from cin and calls processCommand()
 * arguments: None
 * returns:   none
 * effects:   Continues until file ends or quit is called
 */
void RPNCalc::run() {
    std::string command;

    while (turn == 0) {
        std::cin >> command;
        if (! std::cin.fail()) {
            processCommand(command);
        } else {
            quit();
        }
    }
}

/*
 * name:      processCommand()
 * purpose:   Calls the correct functions for the command
 * arguments: String holding the command
 * returns:   none
 * effects:   Calls many other functions to perform the commanded action
 */
void RPNCalc::processCommand(std::string command) {
    std::string ifCommand = "";
    int result = 0;
    bool condition = got_int(command, &result);
    if (condition) {
        int num = result;
        addInt(num);
    } else if (command == "print") {
        calcPrint();
    } else if (command == "#t") {
        trueBool();
    } else if (command == "#f") {
        falseBool();
    } else if (command == "drop") {
        drop();
    } else if (command == "not") {
        notCommand();
    } else if (command == "dup") {
        dup();
    } else if (command == "swap") {
        swap();
    } else if (command == "exec") {
        exec(ifCommand);
    } else if (command == "clear") {
        clearCommand();
    } else if (simpleOpCheck(command)) {
        simpleOp(command);
    } else if (inequalCheck(command)) {
        inequalOp(command);
    } else if (command == "if") {
        ifCondition();
    } else if (command == "file") {
        file();
    } else if (command == "{") {
        std::string parsedString = parseRString(std::cin);
        addString(parsedString);
    } else if (command == "quit") {
        quit();
    } else if (fileCheck(command)) {
        command = "{ " + command + " }";
        addString(command);
    } else if (command == "file") {
        file();
    } else {
        std::cerr << command << ": unimplemented\n";
    }

}

/*
 * name:      addInt()
 * purpose:   Adds the integer to the stack
 * arguments: Point to the integer to add
 * returns:   none
 * effects:   stack size increases
 */
void RPNCalc::addInt(int value) {
    Datum num(value);
    calc_stack.push(num);
}

/*
 * name:      addString()
 * purpose:   Adds the rString command to the stack
 * arguments: rString to add to the stack
 * returns:   none
 * effects:   stack size increases
 */
void RPNCalc::addString(std::string command) {
    Datum result(command);
    calc_stack.push(result);
}

/*
 * name:      trueBool()
 * purpose:   Adds a true boolean onto the stack
 * arguments: none
 * returns:   none
 * effects:   stack size increases
 */
void RPNCalc::trueBool() {
    Datum result(true);
    calc_stack.push(result);
}

/*
 * name:      falseBool()
 * purpose:   Adds a false boolean onto the stack
 * arguments: none
 * returns:   none
 * effects:   stack size increases
 */
void RPNCalc::falseBool() {
    Datum result(false);
    calc_stack.push(result);
}

/*
 * name:      drop()
 * purpose:   Drops the top datum from the stack
 * arguments: none
 * returns:   none
 * effects:   stack size decreases
*/
void RPNCalc::drop() {
    try {
        Datum result(calc_stack.top());
        calc_stack.pop();
    }
    catch (std::runtime_error) {
        std::cerr << "Error: empty_stack\n";
    }
}

/*
 * name:      clearCommand()
 * purpose:   Clears all elements from the stack
 * arguments: none
 * returns:   none
 * effects:   stack size becomes zero
*/
void RPNCalc::clearCommand() {
    calc_stack.clear();
}

/*
 * name:      dup()
 * purpose:   Duplicates the top element on the stack
 * arguments: none
 * returns:   none
 * effects:   stack size increases
*/
void RPNCalc::dup() {
    Datum result(topElem());
    if (errorCount == 0) {
        calc_stack.push(result);
    }
}

/*
 * name:      swap()
 * purpose:   Swaps the top element with the second highest element
 * arguments: none
 * returns:   none
 * effects:   Top element changes
*/
void RPNCalc::swap() {
    try {
        Datum result(topElem());
        calc_stack.pop();
        Datum result2(topElem());
        calc_stack.pop();
        calc_stack.push(result);
        calc_stack.push(result2);
    }
    catch (std::runtime_error) {
        if (errorCount == 0) {
            std::cerr << "Error: empty_stack\n";
        }
    }
}

/*
 * name:      quit()
 * purpose:   Quits the program
 * to the stack
 * arguments: none
 * returns:   none
 * effects:   stack size increases
*/
void RPNCalc::quit() {
    std::cerr << "Thank you for using CalcYouLater.\n";
    turn = 1;
}

/*
 * name:      ifCommand()
 * purpose:   Pops two boolean cases and a test condition from the stack and
 * executes the one that matches the test condition
 * arguments: none
 * returns:   none
 * effects:   stack size decreases
*/
void RPNCalc::ifCondition() {
    try {
        //Gets all three required elements
        Datum falseCase(topElem());
        calc_stack.pop();
        bool case1 = falseCase.isRString();
        Datum trueCase(topElem());
        calc_stack.pop();
        bool case2 = trueCase.isRString();
        Datum testCondition(topElem());
        calc_stack.pop();
        bool conditionCheck = testCondition.isBool();

        //Checks each datum type is correct - if so it performs the function
        if ((case1 == true) and (case2 == true) and (conditionCheck == true)) {
            bool condition = testCondition.getBool();
            if (condition == false) {
                std::string falseString = falseCase.toString();
                exec(falseString);
            } else {
                std::string trueString = trueCase.toString();
                exec(trueString);
            }
        } else {
            if (conditionCheck == false) {
                std::cerr << "Error: expected boolean in if test\n";
            } else {
                std::cerr << "Error: expected rstring in if branch\n";
            }
        }
    }
    catch (std::runtime_error) {
        if (errorCount == 0) {
            std::cerr << "Error: empty_stack\n";
        }
    }
}

/*
 * name:      exec()
 * purpose:   Executes the command in the rString
 * Reads in commands from within the rstring and sends them to processCommands
 * arguments: string ifcommand for an rstring read in from file
 * returns:   none
 * effects:   Commands in rstring executed and stack size changes
*/
void RPNCalc::exec(std::string ifCommand) {
    try {
        //Sets correct string to execute
        std::string command;
        std::string part;
        bool answer;
        if (ifCommand == "") {
            Datum result(topElem());
            command = result.toString();
            calc_stack.pop();
            answer = result.isRString();
        } else {
            command = ifCommand;
            answer = true;
        }

        //Gets each individual command within each rstring
        std::stringstream str(command);
        if (answer == true) {
            while (getline(str, part, ' ')) {
                if ((part != "{") and (part != "}")) {
                    if (part != "") {
                        processCommand(part);
                    }
                }
            }
        } else {
            std::cerr << "Error: cannot execute non rstring\n";
        }
    }
    catch (std::runtime_error) {
        if (errorCount == 0) {
            std::cerr << "Error: empty_stack\n";
        }
    }
}

/*
 * name:      fileCheck()
 * purpose:   Checks if the input was the name of a file and if so adds it
 * arguments: string command
 * returns:   bool
 * effects:   Leads to rstring being added
*/
bool RPNCalc::fileCheck(std::string command) {
    bool answer = false;
    int stringLength = command.length();
    int count = 0;
    if (command[stringLength - 1] == 'c') {
        count++;
    } 
    if (command[stringLength - 2] == 'l') {
        count++;
    }
    if (command[stringLength - 3] == 'y') {
        count++;
    }
    if (command[stringLength - 4] == 'c') {
        count++;
    }
    if (count == 4) {
        answer = true;
    }
    return answer;
}

/*
 * name:      file()
 * purpose:   Reads in a file name from the top rString and then executes the
 * the commands in that file by calling readFile
 * arguments: none
 * returns:   none
 * effects:   Commands in a file executed
*/
void RPNCalc::file() {
    try {
        //Gets name of File and sends it to be read
        Datum result(topElem());
        std::string command = result.toString();
        std::string part;
        std::stringstream str(command);
        calc_stack.pop();
        bool answer = result.isRString();
        if (answer == true) {
            while (getline(str, part, ' ')) {
                if ((part != "{") and (part != "}")) {
                    readFile(part);
                }
            }
        } else {
            std::cerr << "Error: file operand not rstring\n";
        }
    }
    catch (std::runtime_error) {
        if (errorCount == 0) {
            std::cerr << "Error: empty_stack\n";
        }
    }
}

/*
 * name:      readFile()
 * purpose:   Reads in commands from file and sends them to processCommands
 * arguments: File name
 * returns:   none
 * effects:   Commands in a file executed
*/
void RPNCalc::readFile(std::string fileName) {
    std::ifstream infile;
    infile.open(fileName);
    if (not infile.is_open()) {
        std::cerr << "Unable to read " << fileName << "\n";
    }
    //Reads every line and either sends individual command or adds rstring
    std::string command;
    while(getline(infile, command)) {
        if (command != "") {
            if (command == "{") {
                std::string longCommand = parseRString(infile);
                addString(longCommand);
            } else {
                if (command[0] == '{') {
                    addString(command);
                } else {
                    processCommand(command);
                }
            }
        }
    }
    if (infile.eof()) {
        return;
    }
}

/*
 * name:      simpleOp()
 * purpose:   Takes the top two datum and performs the given
 * operation and pushed the result onto the stack
 * arguments: string command
 * returns:   none
 * effects:   Removes two datum and adds a new one (size decrease)
*/
void RPNCalc::simpleOp(std::string command) {
    try {
        Datum result(topElem());
        calc_stack.pop();
        Datum result2(topElem());
        calc_stack.pop();
        int num1 = result.getInt();
        int num2 = result2.getInt();
        try {
            int answer = calcResult(command, num1, num2);
            Datum choice(answer);
            calc_stack.push(choice);
        }
        catch (std::range_error) {
            std::cerr << "Error: division by 0.\n";
            return;
        }
    }
    catch (std::runtime_error) {
        if (errorCount == 0) {
            std::cerr << "Error: datum_not_int\n";
        }
        return;
    }
}


/*
 * name:      inequalOp()
 * purpose:   Takes the top two datum and performs the given
 * operation and pushed the result onto the stack
 * arguments: string command
 * returns:   none
 * effects:   Removes two datum and adds a new one (size decrease)
*/
void RPNCalc::inequalOp(std::string command) {
    try {
        Datum result(topElem());
        calc_stack.pop();
        Datum result2(topElem());
        calc_stack.pop();
        int num1 = result.getInt();
        int num2 = result2.getInt();

        bool answer = inequalResult(command, num1, num2);
        Datum choice(answer);
        calc_stack.push(choice);
    }
    catch (std::runtime_error) {
        if (errorCount == 0) {
            std::cerr << "Error: datum_not_int\n";
        }
        return;
    }
   
}

/*
 * name:      inequalResult()
 * purpose:   Calculates the answer of the given operator applied
 * to two ints
 * arguments: command, first integer, second integer
 * returns:   bool result
 * effects:   stack size increases
*/
bool RPNCalc::inequalResult(std::string command, int num1, int num2)
{
    bool answer = false;
    if (command == ">") {
            answer = num2 > num1;
        } else if (command == "<") {
            answer = num2 < num1;
        } else if (command == "<=") {
            answer = num2 <= num1;
        } else if (command == ">=") {
            answer = num2 >= num1;
        } else if (command == "==") {
            answer = num2 == num1;
        }
    
    return answer;
}

/*
 * name:      calcResult()
 * purpose:   Calculates the answer of the given operator applied
 * to two ints
 * arguments: command, first integer, second integer
 * returns:   integer result
 * effects:   stack size increases
*/
int RPNCalc::calcResult(std::string command, int num1, int num2) {
    int answer = 0;
    if (command == "+") {
            answer = num2 + num1;
        } else if (command == "-") {
            answer = num2 - num1;
        } else if (command == "*") {
            answer = num2 * num1;
        } else if (command == "mod") {
            if (num1 == 0) {
                throw std::range_error("Undefined operation");
            }
            answer = num2 % num1;
        } else if (command == "/") {
            if (num1 == 0) {
                throw std::range_error("Undefined operation");
            }
            answer = num2 / num1;
        }
    
    return answer;
}

/*
 * name:      simpleOpCheck()
 * purpose:   Checks if a simple operator was inputted in the input
 * line
 * to the stack
 * arguments: string command
 * returns:   bool
 * effects:   none
*/
bool RPNCalc::simpleOpCheck(std::string command) {
    bool answer;
    if (command == "+") {
            answer = true;
        } else if (command == "-") {
            answer = true;
        } else if (command == "*") {
            answer = true;
        } else if (command == "mod") {
            answer = true;
        } else if (command == "/") {
            answer = true;
        } else {
            answer = false;
        }
    return answer;
}

/*
 * name:      inequalCheck()
 * purpose:   Checks if a inequality operator was inputted in the
 * input line
 * arguments: string command
 * returns:   bool
 * effects:   none
*/
bool RPNCalc::inequalCheck(std::string command) {
    bool answer;
    if (command == ">") {
            answer = true;
        } else if (command == "<") {
            answer = true;
        } else if (command == "<=") {
            answer = true;
        } else if (command == ">=") {
            answer = true;
        } else if (command == "==") {
            answer = true;
        } else {
            answer = false;
        }
    return answer;
}

/*
 * name:      notCommand()
 * purpose:   Pops the top boolean and adds a boolean of the opposite value
 * to the stack
 * arguments: none
 * returns:   none
 * effects:   stack size increases
*/
void RPNCalc::notCommand() {
    try {
        Datum result(calc_stack.top());
        calc_stack.pop();
        bool answer = result.isBool();
        if (answer == true) {
            if (result.toString() == "#t") {
                Datum opposite(false);
                calc_stack.push(opposite);
            } else if (result.toString() == "#f") {
                Datum opposite2(true);
                calc_stack.push(opposite2);
            }
        } else {
            std::cerr << "Error: datum_not_bool\n";
        }
    }
    catch (std::runtime_error) {
        std::cerr << "Error: empty_stack\n";
    }
}

/*
 * name:      topElem()
 * purpose:   Gets top element in stack and checks for thrown 
 * exceptions
 * arguments: None
 * returns:   Datum
 * effects:   None
*/
Datum RPNCalc::topElem() {
    Datum lastReturn(2);
    errorCount = 0;
    try {
        Datum result(calc_stack.top());
        return result;
    }
    catch (std::runtime_error) {
        std::cerr << "Error: empty_stack\n";
        errorCount = 1;
    }
    return lastReturn;
}

/*
 * name:      calcPrint()
 * purpose:   Prints the top datum from the stack
 * arguments: None
 * returns:   none
 * effects:   None
*/
void RPNCalc::calcPrint() {
    Datum result(topElem());
    if (errorCount == 0) {
        std::cout << result.toString() << std::endl;
    }
}