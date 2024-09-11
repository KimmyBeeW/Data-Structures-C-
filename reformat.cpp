//Write a program that reads in a file containing a list of names, point scores, and a factor.
//The program should reformat and output the data to a new file, where the points are multiplied by the
// given factor for each name.
//
//Accept the input file name and the output file name as command line arguments
//You can assume the input file is formatted correctly
//The input file format:
//Each line contains a first name, last name, points (integer), and factor (double) separated by spaces
//There is no trailing whitespace
//The output file format:
//Each line contains the last name, a comma, the first name, a colon, and the recalculated points (as a double)
//There is no trailing whitespace

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
    if (argc != 3) {
        cerr << "needs an input file and output file" << endl;
        return 1;
    }
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    if (!outfile.is_open()) {
        cerr << argv[2] << " did not open" << endl;
    }
    string line;
    while (getline(infile, line)){
        istringstream line_stream(line); // line_stream = istringstream(line)
        string fixed, first, last; double score, factor;
        line_stream >> first >> last >> score >> factor;
        outfile << last << ", " << first << ": " << score*factor << endl;
    }
    infile.close();
    outfile.close();
}

// g++ -std=c++17 -o reformat reformat.cpp
// ./reformat test_files/reformat_test1.input.txt output_file.txt
