#include <iostream>
#include <fstream>
#include "errors.h"
using namespace std;

int main(int argc, char** argv) {
    cout << "The files loaded are: " << endl;
    cout << "Plugboard: " << argv[1] << endl;
    cout << "Reflector: " << argv[2] << endl;
    cout << "Rotors (1, 2 and 3): " << argv[3] 
        << " " << argv[4] << " " << argv[5] << endl;
    cout << "Rotor position: " << argv[6] << "\n" << endl;

    

    return 0;
}