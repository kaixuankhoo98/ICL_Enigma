#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "functions.h"
#include "errors.h"

#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"
#include "Position.h"
using namespace std;

int main(int argc, char** argv) {
    if (argc < 4) {
        cerr << "Insufficient number of parameters.";
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

    int number_of_rotors = 0;
    // Tests for loading the correct files from the command line
    cout << argc << "The files loaded are: " << endl;
    cout << "Plugboard: " << argv[1] << endl;
    cout << "Reflector: " << argv[2] << endl;
    cout << "Rotors: ";
    for (int i = 0; i <= argc-5; i++) {
        cout << argv[3+i] << " ";
        number_of_rotors++;
    } cout << "(Total of " << number_of_rotors << " rotors) " << endl;
    cout << "Rotor position: " << argv[argc-1] << "\n" << endl;

    /*
    Plugboard plugboard(argv[1]);
    cout << "Plugboard exit code: " << plugboard.exit_code << endl << endl;
    Reflector reflector(argv[2]);
    cout << "Reflector exit code: " << reflector.exit_code << endl << endl;
    Rotor rotor1(argv[3]); 
    cout << "Rotor exit code: " << rotor1.exit_code << endl << endl;
    Position position(argv[argc-1], argc-1);
    cout << "Position exit code: " << position.exit_code << endl << endl;
    */
    
    // CREATE INPUTS TO ALLOW OPTION TO CHOOSE ENCRYPTION OR DECRYPTION
    int mode;
    cout << "Please enter 1 if you would like to encrypt a message, or 2 if you would like to decrypt."
    << endl;
    cin >> mode;
    if (mode < 1 || mode > 2) {
        cout << "Please enter either 1 (for encryption) or 2 (for decryption):" << endl;
        cin >> mode;
    }

    if (mode == 1) {
        string input, converted;
        cout << "Please enter the message you would like to encrypt in all upper-case:" << endl;
        getline(cin >> ws, input);
        int input_exit_code;
        input_exit_code = verify_string(input);

        if (input_exit_code != 0) {
            cerr << "Input exit code: " << input_exit_code;
            return input_exit_code;
        }

        converted = convert_string(input);
        // cout << converted << endl;
        cout << encrypt(converted, argv, argc);
    }

    if (mode == 2) {
        string input, converted;
        cout << "Please enter the message you would like to have decrypted in all upper-case:" << endl;
        getline(cin >> ws, input);
        int input_exit_code;
        input_exit_code = verify_string(input);

        if (input_exit_code != 0) {
            cout << "Input exit code: " << input_exit_code;
            return input_exit_code;
        }
        
        converted = convert_string(input);
        // cout << converted << endl;
        // cout << decrypt(converted, argv, argc);
    }

    return 0;
}