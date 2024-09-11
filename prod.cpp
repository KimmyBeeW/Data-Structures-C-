//  :)
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
//double num1, num2; cin >> num1; cin >> num2; cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
    if (argc < 3){
        cerr << "prod requires 2 arguments" << endl;
        return 1;
    }
    double num1 = atof(argv[1]);
    double num2 = atof(argv[2]);
    cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
    return 0;
}

/* compile then run:

g++ -std=c++17 -o prod prod.cpp
./prod # #

 */