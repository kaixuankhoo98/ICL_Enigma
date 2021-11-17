#include <string>
#include <vector>
#include "errors.h"

#ifndef REFLECTOR_H
#define REFLECTOR_H

class Reflector {
    private:
    std::string name;
    std::string contents;

    public:
    Reflector(char filename[20]);
    int length;
    std::vector<int> reflector_vector;
    int load_reflector(char filename[20]);
    int exit_code = 0;
    void insert_to_vector(std::vector<int>& reflector_vector, std::string contents);
    void print_ints(std::vector<int> reflector_vector);
};

#endif