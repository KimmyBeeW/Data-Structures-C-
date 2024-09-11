// takes in three integer command line arguments: start, end, and divisor.
// The program should output all the integers between start and end, inclusive,
// that are divisible by divisor.
#include <iostream>
using std::cout, std::endl, std::cerr;

int main(int argc, char* argv[]){
    if (argc < 4){
        cerr << "numbers_divisible_by requires 3 arguments: start, end, and divisor" << endl;
        return 1;
    }
    int start = atoi(argv[1]), end = atoi(argv[2]), divisor = atoi(argv[3]);
    if (start < end){  //the program should iterate in increasing order
        for (; start < (end+1); start++){
            if (start % divisor == 0){
                cout << start << endl;
            }
        }
        return 0;
    }
    if (start >= end){  //the program should iterate in decreasing order
        for (; start > (end-1); start--){
            if (start % divisor == 0){
                cout << start << endl;
            }
        }
        return 0;
    }
}

// g++ -std=c++17 -o numbers_divisible_by numbers_divisible_by.cpp
// ./numbers_divisible_by 1 10 2