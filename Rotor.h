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
    Rotor();
    int length;
    vector<int> rotor_vector;
    vector<int> notches;
    int load_rotor(char filename[20]);
    int exit_code = 0;
    void insert_to_vector(vector<int>& rotor_vector, string contents);
    void get_notches(vector<int>& notches, vector<int> rotor_vector);
    void rotate_rotor(vector<int>& rotor_vector);
    void print_ints(vector<int> rotor_vector);
};

#endif