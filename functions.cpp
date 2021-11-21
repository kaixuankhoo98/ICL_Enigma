#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "functions.h"
#include "errors.h"

#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"
#include "Position.h"
using namespace std;

// Returns a string containing first line of the file opened
string open_file_string(char filename[20]) {
    ifstream input;
    input.open(filename);

    string loaded_input;
    getline(ifstream(filename), loaded_input);

    input.close();
    return loaded_input;
}

// Verifies if the user's input only contains upper-case characters
int verify_string(string cin_stream) {
    cin_stream.erase(remove(cin_stream.begin(), cin_stream.end(), ' '), cin_stream.end());
    cin_stream.erase(remove(cin_stream.begin(), cin_stream.end(), '\t'), cin_stream.end());
    cin_stream.erase(remove(cin_stream.begin(), cin_stream.end(), '\n'), cin_stream.end());
    cin_stream.erase(remove(cin_stream.begin(), cin_stream.end(), '\r'), cin_stream.end());
    for (size_t i = 0; i < cin_stream.length(); i++) {
        if (cin_stream[i] < 'A' || cin_stream[i] > 'Z') {
            return INVALID_INPUT_CHARACTER;
        }
    }
    return 0;
}

// Converts user's input string into a string without any whitespaces
string convert_string(string input) {
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    input.erase(remove(input.begin(), input.end(), '\t'), input.end());
    input.erase(remove(input.begin(), input.end(), '\n'), input.end());
    input.erase(remove(input.begin(), input.end(), '\r'), input.end());
    return input;
}

// Big function to encrypt the entire user input message
string encrypt(string input, char* argv[], int argc) {
    Plugboard plugboard(argv[1]);
    Reflector reflector(argv[2]);
    Rotor rotor1 = make_rotor(argc, argv, 1);
    Rotor rotor2 = make_rotor(argc, argv, 2);
    Rotor rotor3 = make_rotor(argc, argv, 3);
    // Current capacity up to 3 rotors. Can add more if necessary. 
    Position position(argv[argc-1], argc-1);

    string encrypted = "";
    

    // Set starting positions of rotors
    if (argc >= 5) {
        while (rotor1.rotor_vector[0] != position.position_vector[0]) {
            rotor1.rotate_rotor(rotor1.rotor_vector);
        } // Rotor 1
    }
    if (argc >= 6) {
        while (rotor2.rotor_vector[0] != position.position_vector[1]) {
            rotor2.rotate_rotor(rotor2.rotor_vector);
        } // Rotor 2
    }
    if (argc >= 7) {
        while (rotor3.rotor_vector[0] != position.position_vector[2]) {
            rotor3.rotate_rotor(rotor3.rotor_vector);
        } // Rotor 3 
    }

    for (size_t i = 0; i < input.length(); i++)  { // go through each letter one by one.
        if (argc == 7) rotor3.rotate_rotor(rotor3.rotor_vector);
        if (argc == 6) rotor2.rotate_rotor(rotor2.rotor_vector);
        if (argc == 5) rotor1.rotate_rotor(rotor1.rotor_vector);

        int letter = input[i] - static_cast<int>('A'); // letter converted to int 
        
        // ENTER PLUGBOARDS
        letter = through_plugboard(argc, argv, letter);    // Pass on letter to rotors

        // GO THROUGH ROTORS, depends on number of inputs
        int through_rotors;
        if (argc == 7) through_rotors = rotor3.rotor_vector[rotor2.rotor_vector[rotor1.rotor_vector[letter]]];
        if (argc == 6) through_rotors = rotor2.rotor_vector[rotor1.rotor_vector[letter]];
        if (argc == 5) through_rotors = rotor1.rotor_vector[letter];
        if (argc == 4) through_rotors = letter;

        // SWAP AT REFLECTOR
        int reflected_letter;
        for (int k = 0; k < reflector.length; k++) {
            if (through_rotors == reflector.reflector_vector[k]) {
                if (k % 2 == 0) {
                    reflected_letter = reflector.reflector_vector[k+1];
                }
                if (k % 2 == 1) {
                    reflected_letter = reflector.reflector_vector[k-1];
                }
            }
        }

        // PASS BACK THROUGH ROTORS
        int back_through_rotors;
        if (argc == 7) {
            for (int j = 0; j < 26; j++) {
                if (rotor3.rotor_vector[rotor2.rotor_vector[rotor1.rotor_vector[j]]] == reflected_letter)
                    back_through_rotors = j;
            }
        } 
        if (argc == 6) {
            for (int j = 0; j < 26; j++) {
                if (rotor2.rotor_vector[rotor1.rotor_vector[j]] == reflected_letter)
                    back_through_rotors = j;
            }
        }
        if (argc == 5) {
            for (int j = 0; j < 26; j++) {
                if (rotor1.rotor_vector[j] == reflected_letter)
                    back_through_rotors = j;
            }
        }
        if (argc == 4) {
            back_through_rotors = reflected_letter;
        }

        // FINAL PASS BACK THROUGH PLUGBOARDS
        int output = back_through_rotors;
        output = through_plugboard(argc, argv, output);


        // ROTATION ACCORDING TO NOTCHES
        if (argc == 7) {
            for (size_t i = 0; i < rotor3.notches.size(); i++) {
                if (rotate_true(rotor3.rotor_vector, rotor3.notches)) {
                    rotor2.rotate_rotor(rotor2.rotor_vector);
                } // Rotates the rotor to the left if the first position is in the notches
            }
            for (size_t i = 0; i < rotor2.notches.size(); i++) {
                if (rotate_true(rotor2.rotor_vector, rotor2.notches)) {
                    rotor1.rotate_rotor(rotor1.rotor_vector);
                } 
            }
        } // Rotation sequence if there are 3 rotors
        if (argc == 6) {
            for (size_t i = 0; i < rotor2.notches.size(); i++) {
                if (rotate_true(rotor2.rotor_vector, rotor2.notches)) {
                    rotor1.rotate_rotor(rotor1.rotor_vector);
                } 
            }
        } // Rotation sequence if there are 2 rotors
        // No rotation of other rotors if there is only 1 rotor

        encrypted += static_cast<char>(output + 'A');
    }
    return encrypted;
}

// Creates a rotor based on file name
Rotor make_rotor(int argc, char* argv[], int number) {
    if (argc >= 5 && number == 1) {
        return Rotor(argv[3]);
    }
    if (argc >= 6 && number == 2) {
        return Rotor(argv[4]);
    }
    if (argc >= 7 && number == 3) {
        return Rotor(argv[5]);
    }
    return Rotor();
}

// Loads all the files, imports them into their respective class
// Returns the exit code starting from the earliest file read
int exit_codes_total(int argc, char* argv[]) {
    Plugboard plugboard(argv[1]);
    Reflector reflector(argv[2]);
    Rotor rotor1 = make_rotor(argc, argv, 1);
    Rotor rotor2 = make_rotor(argc, argv, 2);
    Rotor rotor3 = make_rotor(argc, argv, 3);
    // Current capacity up to 3 rotors. Can add more if necessary. 
    Position position(argv[argc-1], argc-1);

    if (plugboard.exit_code != 0) return plugboard.exit_code;
    if (reflector.exit_code != 0) return reflector.exit_code;
    if (rotor1.exit_code != 0) return rotor1.exit_code;
    if (rotor2.exit_code != 0) return rotor2.exit_code;
    if (rotor3.exit_code != 0) return rotor3.exit_code;
    if (position.exit_code != 0) return position.exit_code;

    return 0;
}
int exit_code_plugboard(int argc, char* argv[]) {
    Plugboard plugboard(argv[1]);
    if (plugboard.exit_code != 0) return plugboard.exit_code;
    return 0;
}
int exit_code_reflector(int argc, char* argv[]) {
    Reflector reflector(argv[2]);
    if (reflector.exit_code != 0) return reflector.exit_code;
    return 0;
}
int exit_code_rotor(int argc, char* argv[]) {
    Rotor rotor1 = make_rotor(argc, argv, 1);
    Rotor rotor2 = make_rotor(argc, argv, 2);
    Rotor rotor3 = make_rotor(argc, argv, 3);
    // Current capacity up to 3 rotors. Can add more if necessary. 
    if (rotor1.exit_code != 0) return rotor1.exit_code;
    if (rotor2.exit_code != 0) return rotor2.exit_code;
    if (rotor3.exit_code != 0) return rotor3.exit_code;
    return 0;
}
int exit_code_position(int argc, char* argv[]) {
    Position position(argv[argc-1], argc-1);
    if (position.exit_code != 0) return position.exit_code;
    return 0;
}

// Pass the input char through the plugboard
char through_plugboard(int argc, char* argv[], char input) {
    Plugboard plugboard(argv[1]);

    for (int k = 0; k < plugboard.length; k++) {
            if (plugboard.plugboard_vector[k] == input) {
                if (k % 2 == 0) {
                    return plugboard.plugboard_vector[k+1];
                }
                if (k % 2 == 1) {
                    return plugboard.plugboard_vector[k-1];
                }
            }
        }

    return input;
}

// Returns true if the first position of the rotor is in the notches
bool rotate_true(vector<int> rotor, vector<int> notch) {
    for (size_t i = 0; i < notch.size(); i++) {
        if (rotor[0] == notch[i])
            return true;
    }
    return false;
}