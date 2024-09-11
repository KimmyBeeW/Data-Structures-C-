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
#include <ostream>
using std::ofstream, std::ostream;
#include <random>
using std::random_device;
#include <istream>
using std::istream;

void print_map(const unordered_map<string, vector<string> >& the_map){
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

unordered_map<string, vector<string> > train(istream &in, unordered_map<string, vector<string> >& txt_model){
    string prev, curr;
    while (in >> curr) {
        txt_model[prev].push_back(curr); // edit the list to add the next word
        prev = curr;
    }
    return txt_model;
}

void generate_text(unordered_map<string, vector<string> > &txt_model, string first, int num_words, ostream &out){
    for (int i = 0; i < num_words; i++){  // - Repeat until the specified number of words have been printed
        vector<string>& values = txt_model[first]; // - Select the bucket of words that followed the previous word
        int length = static_cast<int>(values.size()); // convert unsigned long to int so that uniform_int_dist doesn't throw errors

        random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, length - 1);
        int randomIndex = dist(gen);
        string word = values[randomIndex];  // - Randomly select a word from that bucket

        out << word << " "; // - Print the word to the provided stream followed by a space
        first = word; // - Set the previous word to the current word
    }
    out << endl;
}

int main(int argc, char const* argv[]){
    unordered_map<string, vector<string> > txt_model;
    if (argc == 3) {
        int num_words = atoi(argv[2]);
        if (num_words <= 0) { cerr << "Error: Number of words must be positive." << endl; return 1; }

        // open the text file input:
        const string txt_file = argv[1];
        ifstream infile(txt_file);
        if (!infile.is_open()) { cerr << "ERROR: can't open " << txt_file << endl; return 1; }

        // train the model:
        train(infile, txt_model);
        infile.close();
        if (txt_model.empty()) { cerr << "Error: No valid data found in the input file." << endl; return 1; }

        //print_map(txt_model);
        // takes model, the first word = "", the number of words to emit, and an ostream&amp; (e.g. cout or ofstream).
        generate_text(txt_model, "", num_words, cout);
        return 0;
    } else{ cerr << "Error: Need an infile and number of words for the output" << endl; return 1; }
}

// g++ -Wall -std=c++17 -o txt_gen basic_text_generation.cpp
// ./txt_gen test_files/1Nephi.txt 75