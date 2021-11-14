#include <string>
#include <vector>
#include "errors.h"
using namespace std;

#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard {
    private:
    string name;
    string contents;
    
    public:
    Plugboard(char filename[20]);
    int load_plugboard(char filename[20]);
    int exit_code = 0;
    void insert_to_vector(vector<int>& plugboard_vector, string contents);
    void print_ints(vector<int> plugboard_vector);
};

#endif