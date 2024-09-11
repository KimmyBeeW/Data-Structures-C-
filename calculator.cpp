//  :)

// You can assume the user always provides valid inputs
// e.g. the test will not enter lizard when the program expects a number
// You won't be asked to divide or mod by zero
// Support add, subtract, multiply, divide, and mod (modulus) operations
// Each of these operations takes a left operand and right operand
// If the user enters an invalid operation (one that is not add , subtract , etc.), your program should print {operation} isn't a valid operation and prompt the user to enter another operation (see example).
// The program should exit when given an empty operation

#include <iostream>
using std::cout, std::cerr, std::endl, std::cin;
#include <string>
using std::string, std::getline;
#include <vector>
using std::vector;
#include <algorithm>
using std::find;

int main(){
    string operation, _left_op, _right_op; int left_op, right_op;
    while (operation != "\n") {
        cout << "operation: ";
        getline(cin, operation);
        // if (operation == "exit" or operation == " "){ break; }
        if (operation.empty()){ break; }

        vector<string> operations = {"add", "subtract", "multiply", "divide", "mod"}; //operations = ["add", "subtract", "multiply", "divide", "mod"]
        if (find(operations.begin(), operations.end(), operation) == operations.end()){ //if operation not in operations:
            cout << operation << " isn't a valid operation" << endl;  //print(f"{operation} isn't a valid operation")
        }

        else {
            cout << "left operand: ";
            getline(cin, _left_op);
            left_op = stoi(_left_op);
            cout << "right operand: ";
            getline(cin, _right_op);
            right_op = stoi(_right_op);
            if (operation == "add"){
                cout << left_op + right_op << endl;
            }
            else if (operation == "subtract"){
                cout << left_op - right_op << endl;
            }
            else if (operation == "multiply"){
                cout << left_op * right_op << endl;
            }
            else if (operation == "divide"){
                // if (right_op == 0) { cerr << "Can't divide by zero" << endl; }
                cout << left_op / right_op << endl;
            }
            else if (operation == "mod"){
                // if (right_op == 0) { cerr << "Can't divide by zero" << endl; }
                cout << left_op % right_op << endl;
            }
        }
    }
    return 0;
}

// g++ -std=c++17 -o calc calculator.cpp
// ./calc