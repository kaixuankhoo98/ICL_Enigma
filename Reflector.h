#include <string>
#include <vector>
#include "errors.h"
using namespace std;

#ifndef REFLECTOR_H
#define REFLECTOR_H

class Reflector {
    private:
    string name;
    string contents;

    public:
    Reflector(char filename[20]);
    int load_reflector(char filename[20]);
    int exit_code = 0;
    void insert_to_vector(vector<int>& reflector_vector, string contents);
    void print_ints(vector<int> reflector_vector);
};

#endif