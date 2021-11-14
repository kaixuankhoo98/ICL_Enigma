#include <string>
#include <vector>
#include "errors.h"
using namespace std;

#ifndef ROTOR_H
#define ROTOR_H

class Rotor {
    private:
    string name;
    string contents;
    vector<int> inputInts;

    public:
    Rotor(char filename[20]);
    int load_rotor(char filename[20]);
    int exit_code = 0;
    void insert_to_vector(vector<int>& rotor_vector, string contents);
    void print_ints(vector<int> rotor_vector);
};

#endif