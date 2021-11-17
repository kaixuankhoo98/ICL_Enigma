#include <string>
#include <vector>
#include "errors.h"

#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard {
    private:
    std::string name;
    std::string contents;
    
    public:
    Plugboard(char filename[20]);
    int length;
    std::vector<int> plugboard_vector;
    int load_plugboard(char filename[20]);
    int exit_code = 0;
    void insert_to_vector(std::vector<int>& plugboard_vector, std::string contents);
    void print_ints(std::vector<int> plugboard_vector);
};

#endif