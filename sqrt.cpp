#include <cstdlib>  // atof
using std::abs;
#include <iostream>
using std::cout, std::endl, std::cerr;

const double EPSILON = 0.0001;

//Write a program that estimates the square root of the input value using binary search.

//The input value is passed as a commandline argument
//The program prints each intermediate value in the binary search
//Use the formatting: guess# (guess#squared) << Include the square of the value in parentheses
//The program stops when the difference between the square of the value and the input is less than 0.0001
//The initial lower bound should be 0
//The initial upper bound should be the input value
//If the user inputs a negative number, print the error shown in the examples and exit with a non-zero exit code
//The program should support double inputs (not int )

int main(int argc, char* argv[]){
    if (argc < 2){
        cerr << "sqrt requires 1 argument: a positive int, double, or float number" << endl;
        return 2;
    }
    double input = atof(argv[1]);
    if (input < 0){
        cerr << "Input must be greater than 0" << endl;
        return 1;
    }
    double lower = 0, upper = atof(argv[1]), value = (input / 2), square = value*value;
    cout << value << " (" << square << ")" << endl;
    while (abs(input - square) > EPSILON){
        if (square > input){
            upper = value;
        }
        if (square < input){
            lower = value;
        }
        value = ((lower + upper) / 2); square = value*value;
        cout << value << " (" << square << ")" << endl;
    }
    return 0;
}

// g++ -std=c++17 -o sqrt sqrt.cpp
// ./sqrt 9

// :)
