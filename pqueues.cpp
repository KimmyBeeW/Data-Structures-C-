//Support add and take operations:
//add requires a Name and Priority input
//take will display the next person in line according to their priority
//Higher numbers indicate higher priority
//If nobody is in the queue, print There are no more people in line
//Use a std::priority_queue to store entries
//The entries should include the assigned priority and name, separated by " - "
//Pad priority numbers with a leading zero if they are in the range 0-9
//An empty operation exits the program
//Follow the formatting demonstrated in the example

#include <iostream>
#include <string>
#include <queue>
#include <functional>
using std::cout, std::cin, std::endl, std::string, std::cerr, std::priority_queue, std::greater, std::less;


int main() {
    string operation, name, priority, entry;
    priority_queue<string> names;
    while (true) {
        cout << "What do you want to do? ";
        getline(cin, operation);
        if ((operation != "add") and (operation != "take")){
            if (operation.empty()){ break; }
            cout << operation << " isn't a valid operation" << endl;
        } else if (operation == "add"){
            cout << "Name: ";
            getline(cin, name);
            cout << "Priority: ";
            getline(cin, priority);
            if (priority.size() <= 1) {
                entry = "0" + priority + " - " + name;
            } else {
                entry = priority + " - " + name;
            }
            names.push(entry);
        } else if (!names.empty()){
            cout << names.top() << endl;
            names.pop();
        } else {
            cout << "There are no more people in line" << endl;
        }
    }
    return 0;
}

// g++ -Wall -std=c++17 -o pqueues pqueues.cpp
