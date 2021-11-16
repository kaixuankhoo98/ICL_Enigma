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

string open_file_string(char filename[20]) {
    ifstream input;
    input.open(filename);

    string loaded_input;
    getline(ifstream(filename), loaded_input);

    input.close();
    return loaded_input;
}

int verify_string(string cin_stream) {
    cin_stream.erase(remove(cin_stream.begin(), cin_stream.end(), ' '), cin_stream.end());
    cin_stream.erase(remove(cin_stream.begin(), cin_stream.end(), '\t'), cin_stream.end());
    cin_stream.erase(remove(cin_stream.begin(), cin_stream.end(), '\n'), cin_stream.end());
    cin_stream.erase(remove(cin_stream.begin(), cin_stream.end(), '\r'), cin_stream.end());
    for (int i = 0; i < cin_stream.length(); i++) {
        if (cin_stream[i] < 'A' || cin_stream[i] > 'Z') {
            return INVALID_INPUT_CHARACTER;
        }
    }
    return 0;
}

string convert_string(string input) {
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    input.erase(remove(input.begin(), input.end(), '\t'), input.end());
    input.erase(remove(input.begin(), input.end(), '\n'), input.end());
    input.erase(remove(input.begin(), input.end(), '\r'), input.end());
    return input;
}


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

    for (int i = 0; i < input.length(); i++)  { // go through each letter one by one.
        if (argc == 7) rotor3.rotate_rotor(rotor3.rotor_vector);
        if (argc == 6) rotor2.rotate_rotor(rotor2.rotor_vector);
        if (argc == 5) rotor1.rotate_rotor(rotor1.rotor_vector);

        int letter = input[i] - static_cast<int>('A'); // letter converted to int 

        // Plugboard swap
        for (int j = 0; j < plugboard.length; j++) {
            if (plugboard.plugboard_vector[j] == letter) {
                if (j % 2 == 0) {
                    letter = plugboard.plugboard_vector[j+1];
                }
                if (j % 2 == 1) {
                    letter = plugboard.plugboard_vector[j-1];
                }
            }
        } // Pass on letter to reflector

        // Reflector swap
        int reflected_letter;
        for (int k = 0; k < reflector.length; k++) {
            if (letter == reflector.reflector_vector[k]) {
                if (k % 2 == 0) {
                    reflected_letter = reflector.reflector_vector[k+1];
                }
                if (k % 2 == 1) {
                    reflected_letter = reflector.reflector_vector[k-1];
                }
            }
        } // At this point, reflected_letter is the value to be passed on to rotors.
        

        int rotor_1_letter, rotor_2_letter, rotor_3_letter;
        // Series of transformations through the rotor(s)
        rotor_1_letter = rotor1.rotor_vector[reflected_letter];
        if (argc >= 6) {
            rotor_2_letter = rotor2.rotor_vector[rotor_1_letter];
        } else rotor_2_letter = rotor_1_letter;
        if (argc >= 7) {
            rotor_3_letter = rotor3.rotor_vector[rotor_2_letter];
        } else rotor_3_letter = rotor_2_letter;

        if (argc == 7) {
            for (int i = 0; i < rotor3.notches.size(); i++) {
                if (rotor_3_letter == rotor3.notches[i]) {
                    rotor2.rotate_rotor(rotor2.rotor_vector);
                } // Rotates the rotor to the left if the first position is in the notches
            }
            for (int i = 0; i < rotor2.notches.size(); i++) {
                if (rotor_2_letter == rotor2.notches[i]) {
                    rotor1.rotate_rotor(rotor1.rotor_vector);
                } 
            }
        } // Rotation sequence if there are 3 rotors

        if (argc == 6) {
            for (int i = 0; i < rotor2.notches.size(); i++) {
                if (rotor_2_letter == rotor2.notches[i]) {
                    rotor1.rotate_rotor(rotor1.rotor_vector);
                } 
            }
        } // Rotation sequence if there are 2 rotors
        
        // cout << rotor_3_letter << " ";

        // cout << letter << "\t" << reflected_letter << "\t" << rotor_1_letter << "\t" << rotor_2_letter << "\t" << rotor_3_letter << "\n";

        encrypted += static_cast<char>(rotor_3_letter + 'A');
    }
    cout << "\n";
    return encrypted;
}

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