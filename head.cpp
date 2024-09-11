//The head program should read the first n lines of either a file or standard input
//If n isn't provided, print 10 lines
//If no file is provided, read the lines from standard input ( cin )
//There are four possible scenarios for command-line arguments:
    // 1) No arguments: the program should read 10 lines from standard input.
    // 2) 1 argument that is an input file: the program should attempt to read 10 lines from the file.
    // 3) 1 argument that is a number of lines n : the program should read that number of lines from standard input.
        //-NOTE: Empty lines ( "" ) count as valid input. The program should accept them the same way it accepts non-empty lines.
    // 4) 2 arguments: the program should read n lines from the file.
//If the input file does not exist, the program should print an error message and exit
//If more lines are requested than the input file has, the program should just print as many lines as the file has and no extras.
//Follow the formatting demonstrated in the example

#include <iostream>
#include <string>
using std::cout, std::endl, std::cin , std::cerr, std::string, std::atoi;
#include <fstream>
using std::ifstream, std::ofstream;

void standard_input(int n){
    string line;
    for (int i = 0; i < n; i++){
        getline(cin, line);
        cout << line << endl;
    }
}

void file_reader(int n, const string &file){
    ifstream infile(file);
    if (!infile.is_open()) {
        cerr << "ERROR: can't open " << file << endl;
    }
    string line;
    for (int i = 0; i < n; i++){
        if (!getline(infile, line)) {
            break;
        }
        cout << line << endl;
    }
    infile.close();
}

int main(int argc, char const* argv[]) {
    if (argc == 1) { // the program should read 10 lines from standard input.
        standard_input(10);
        return 0;
    }
    else if (argc == 2) {
        if (argv[1][0] == '-') { // is an int: the program should read that number of lines from standard input.
            standard_input(atoi(argv[1] + 1));
            return 0;
        }
        else {  // is a file: the program should attempt to read 10 lines from the file.
            file_reader(10, argv[1]);
            return 0;
        }
    }
    else if (argc == 3){  // the program should read n lines from the file.
        file_reader(atoi(argv[1]+1), argv[2]);
        return 0;
    }
    return 1;
}

// g++ -std=c++17 -o head head.cpp
// ./head -7 test_files/head_both_args.stdout.txt