// :)
// The Collatz conjecture states that for any positive integer:
//  if the number is even, divide it by 2
//  if the numbers is odd, multiply it by 3 and add 1
//  and that by following these steps, all sequences will eventually reach 1.
//Write program that prints the Collatz sequence from the starting value (which is provided as a commandline argument).
// Stop when you reach 1.

#include <iostream>
using std::cout, std::endl, std::cerr;
#include <cstdlib>
using std::abs;

int main(int argc, char* argv[]){
    if (argc < 2){
        cerr << "collatz requires 1 argument: an int" << endl;
        return 1;
    }
    int num = abs(atoi(argv[1]));
    cout << num << endl;
    while (num != 1){
        if (num % 2 == 0){
            num /= 2;
            cout << num << endl;
        }
        if ((num % 2 == 1) && (num != 1)){
            num *= 3; num += 1;
            cout << num << endl;
        }
    }
    return 0;
}

// g++ -std=c++17 -o collatz collatz.cpp
// ./collatz 9
