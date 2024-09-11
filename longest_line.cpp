//  :-)

#include <iostream>
using std::cout, std::cerr, std::endl, std::cin;
#include <fstream>
using std::ifstream, std::ofstream;
#include <string>
using std::string, std::getline;
#include <sstream>
using std::istringstream;

int main(int argc, char **argv) {
    // for each line in input, sum numbers on the line and write to output
    if (argc != 2) {
        cerr << "needs an input file" << endl;
        return 1;
    }
    ifstream infile(argv[1]);
    string line, longest, token; int total = 0, longest_total = 0;
    while (getline(infile, line)){
        istringstream line_stream(line); // line_stream = istringstream(line)
        while (line_stream >> token) {
            total += 1;
        }
        if (total > longest_total){
            longest = line;
            longest_total = total;
        }
        total = 0;
    }
    cout << longest << endl;
    infile.close();
    return 0;
}

// g++ -std=c++17 -o longest longest_line.cpp
// ./longest test_files/longest_line_test1.input.txt