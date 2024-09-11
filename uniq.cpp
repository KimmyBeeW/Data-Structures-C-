// reads lines from a text input and outputs unique lines only.
// Read lines from a file if a filename is provided as a command-line argument, otherwise read lines from stdin
// Output unique lines in the order they appear in the input
// Do not output a line more than once

#include <iostream>
#include <string>
using std::cout, std::endl, std::cin , std::cerr, std::string, std::atoi;
#include <fstream>
using std::ifstream, std::ofstream;
#include <set>
using std::set;

int main(int argc, char const* argv[]) {
    string line;
    set<string> inputs;
    if (argc == 1) { //read lines from standard input.
        while(true){
            getline(cin, line);
            if (line.empty()){
                break;
            } else {
                if (inputs.find(line) == inputs.end()){
                    inputs.insert(line);
                    cout << line << endl;
                }
            }
        }
    }
    else if (argc == 2) {
        const string file = argv[1];
        ifstream infile(file);
        if (!infile.is_open()) {
            cerr << "ERROR: can't open " << file << endl;
        }
        while (getline(infile, line)){
            if (inputs.find(line) == inputs.end()){
                inputs.insert(line);
                cout << line << endl;
            }
        }
        infile.close();
    }
    return 0;
}

// g++ -Wall -std=c++17 -o uniq uniq.cpp
