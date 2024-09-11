// :)
#include <iostream>
using std::cout, std::cerr, std::cin, std::endl;
#include <string>
using std::string, std::getline;
#include <unordered_map>
using std::unordered_map;
#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;
#include <sstream>
using std::istringstream;

void print_map(const unordered_map<string, vector<string>>& the_map){
    for (const auto &pair : the_map) {
        cout << pair.first << ": ";  // Print the key
        const vector<string>& values = pair.second;
        for (size_t i = 0; i < values.size(); ++i) {
            cout << values[i];
            if (i != values.size() - 1) {  cout << ", "; }
        }
        cout << endl;
    }
}

unordered_map<string, vector<string>> train(istringstream &in, unordered_map<string, vector<string>>& the_map){
    string prev, curr;
    vector<string> list;
    while (in >> curr) {
        if (the_map.find(prev) != the_map.end()){ // key already exists
            the_map[prev].push_back(curr); // edit the list to add the next word
        }else { // key doesn't exist yet
            list.push_back(curr); // inserts a list consisting only of one word
            the_map.insert({prev, list});
            list.clear();  // empty the list
        }
        prev = curr;
    }
    return the_map;
}

int main(int argc, char const* argv[]){
    unordered_map<string, vector<string>> the_map;
    if (argc == 2) {
        // open the text file input:
        const string txt_file = argv[1];
        ifstream infile(txt_file);
        if (!infile.is_open()) {
            cerr << "ERROR: can't open " << txt_file << endl;
            return 1;
        }

        // train the model:
        string line;
        while (getline(infile, line)){
            istringstream in(line);
            the_map = train(in, the_map);
        }
        infile.close();
    }
    print_map(the_map);
    return 0;
}

// g++ -Wall -std=c++17 -o txt_gen basic_text_generation.cpp
// ./txt_gen test_files/1Nephi.txt