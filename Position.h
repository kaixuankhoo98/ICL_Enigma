#include <string>
#include <vector>
#include "errors.h"
using namespace std;

#ifndef POSITION_H
#define POSITION_H

class Position {
    private:
    string name;
    string contents;
    vector<int> inputInts;

    public:
    Position(char filename[20], int argc);
    int load_position(char filename[20], int number_of_rotors);
    int exit_code = 0;
    void insert_to_vector(vector<int>& position_vector, string contents);
    void print_ints(vector<int> position_vector);
};

#endif