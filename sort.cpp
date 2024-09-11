//read lines from standard input (cin) or from a file (if a filename is provided as a command-line
    // argument).
//The program should use the insertion sort algorithm.
//After sorting, the program should print the sorted lines to standard output (cout).
//Sort according to standard string comparisons.
//Follow the formatting demonstrated in the example.

#include <iostream>
#include <string>
#include <vector>
using std::cout, std::endl, std::cin, std::vector, std::string;
#include <fstream>
using std::ifstream;

void printVector(const vector<string>& vec) {
    for(const auto & i : vec) {
        cout << i << endl;
    }
}

void insertionSort(vector<string> & vec){
    for(int i = 0; i < vec.size(); i++) {
        int j = i;
        string item = vec[j];
        while ((j > 0) && (vec[j-1] > item)){
            vec[j] = vec[j-1];
            j--;
        }
        vec[j] = item;
    }
}

int main(int argc, char const* argv[]) {
    vector<string> sortables;
    string item;
    if (argc >= 2) { // file
        const string maze_file = argv[1];
        ifstream infile(maze_file);
        while (getline(infile, item)){
            sortables.push_back(item);
        }
        infile.close();
    } else {
        while (getline(cin, item)){
            if (item.empty()){ break; }
            sortables.push_back(item);
        }
    }
    // printVector(sortables); cout << endl; // debugging only
    insertionSort(sortables);
    printVector(sortables);
    return 0;
}

// g++ -Wall -std=c++17 -o sort sort.cpp
// ./sort test_files/test1.dialog.txt
