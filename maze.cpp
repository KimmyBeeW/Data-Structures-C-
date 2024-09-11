#include <iostream>
using std::cout, std::cerr, std::cin, std::endl;
#include <string>
using std::string, std::getline;
#include <vector>
using std::vector;
#include <fstream>
using std::ifstream, std::ofstream;
#include <sstream>
using std::istringstream, std::ostringstream;
#include <ostream>
using std::ostream;

#include "Grid.h"

bool find_maze_path(Grid & maze, int row, int column, int level, vector<string> & solution){
    if (row < 0 || row >= maze.height() || column < 0 || column >= maze.width() || level < 0 || level >= maze.depth() || maze.at(row, column, level) != 1) {
        return false;
    }

    ostringstream position; // add position to solution
    position << row << " " << column << " " << level;
    // cout << position.str() << endl; // debugging only
    solution.push_back(position.str());
    maze.at(row, column, level) = 2; // set the value at a specific location. This is a great way to mark a location as visited.

    if (row == maze.height() - 1 && column == maze.width() - 1 && level == maze.depth() - 1) {
        return true;
    }

    if (find_maze_path(maze, row + 1, column, level, solution) || // down
        find_maze_path(maze, row - 1, column, level, solution) || // up
        find_maze_path(maze, row, column + 1, level, solution) || // right
        find_maze_path(maze, row, column - 1, level, solution) || // left
        find_maze_path(maze, row, column, level + 1, solution) || // forward
        find_maze_path(maze, row, column, level - 1, solution)) { // backward
        return true;
    }
    // first solution hit dead end
    maze.at(row, column, level) = 1;
    solution.pop_back();
    return false;
}

int main(int argc, char const* argv[]){
    if (argc == 3) {
        // open the files:
        const string maze_file = argv[1], out_file = argv[2];
        ifstream infile(maze_file);
        ofstream outfile(out_file);
        if (!infile.is_open()) { cerr << "ERROR: can't open " << maze_file << endl; return 1; }
        if (!outfile.is_open()) { cerr << "ERROR: can't open " << out_file << endl; return 1; }

        // The first line of the maze file indicates the dimensions of the maze: number of rows, number of columns, number of levels.
        Grid maze; // allocate a new, blank Grid
        infile >> maze; // read the entire input file into maze
        // cout << "The maze is " << maze.height() << " spaces tall, " << maze.width() << " spaces wide, and " << maze.depth() << " spaces deep" << std::endl; // access the maze's dimensions

        int row = 0, column = 0, level = 0;
        vector<string> solution;
        if(find_maze_path(maze, row, column, level, solution)){
            outfile << "SOLUTION" << endl;
            for(const auto & i : solution) {
                outfile << i << endl;
            }
            infile.close(); outfile.close(); return 0;
        } else{
            outfile << "NO SOLUTION";
            infile.close(); outfile.close(); return 0;
        }
    } else{ cerr << "Error: Need an maze file and solution output file" << endl; return 1; }
}

// g++ -Wall -std=c++17 -o maze maze.cpp
// ./maze test_files/solvable1.maze.txt solvable1.solution.txt
// ./maze test_files/solvable2.maze.txt solvable2.solution.txt
