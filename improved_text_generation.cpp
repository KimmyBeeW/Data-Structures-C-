// Implement at least one of the following features:
// *** accept the starting word from the commandline (instead of using "" as the starting word)
// *** train on an input file of your choosing - instead of using the provided text files, create your own. Be creative.
    // - rename your file to have the suffix ".custom-input.txt" and submit it with your code
// - train on multiple input files - read them all into the same map, then generate text from the aggregated model
    // - try sources that are similar and sources that are dissimilar
// - group by prev 2 words
// - use "", "" as the "starting word"
// - group by prev N words - N can be defined in the code, or taken as an argument from the commandline
// - stretch goal: - include previous N, N-1, N-2, etc. words as keys - if the previous N words isn't in the map, use N-1, etc.
// - treat punctuation (e.g. .,!? ) as separate tokens
// - stretch goal: - handle spacing and capitalization appropriately
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

void generate_text(unordered_map<string, vector<string> > &txt_model, string &start, int num_words, ostream &out){
    out << endl;
    for (int i = 0; i < num_words; i++){  // - Repeat until the specified number of words have been printed
        vector<string>& values = txt_model[start]; // - Select the bucket of words that followed the previous word
        int length = static_cast<int>(values.size()); // convert unsigned long to int so that uniform_int_dist doesn't throw errors

        random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, length - 1);
        int randomIndex = dist(gen);
        string word = values[randomIndex];  // - Randomly select a word from that bucket

        out << word << " "; // - Print the word to the provided stream followed by a space
        start = word; // - Set the previous word to the current word
    }
    out << "\n" << endl;
}

int main(int argc, char const* argv[]){
    unordered_map<string, vector<string> > txt_model;
    if (argc >= 3) {
        int num_words = atoi(argv[2]);
        if (num_words <= 0) { cerr << "Error: Number of words must be positive." << endl; return 1; }

        // open the text file input:
        const string txt_file = argv[1];
        ifstream infile(txt_file);
        if (!infile.is_open()) { cerr << "ERROR: can't open " << txt_file << endl; return 1; }

        // train the model:
        string line;
        train(infile, txt_model);
        infile.close();
        if (txt_model.empty()) { cerr << "Error: No valid data found in the input file." << endl; return 1; }

        string start;
        if ((argc >= 4) && (txt_model.find(string(argv[3])) != txt_model.end())){
            start = string(argv[3]);
        } else {
            start = "";
        }

        //debug: print_map(txt_model);

        // takes model, the first word, the number of words to emit, and an ostream&amp; (e.g. cout or ofstream).
        generate_text(txt_model, start, num_words, cout);
        return 0;
    } else{ cerr << "Error: Needs at least an infile and number of words for the output" << endl; return 1; }
}

// g++ -Wall -std=c++17 -o improved_text_generation improved_text_generation.cpp
// ./improved_text_generation poem.custom-input.txt 100 Jabberwocky
// ./improved_text_generation test_files/1Nephi.txt 75
