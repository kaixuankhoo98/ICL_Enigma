#include <string>
#include <vector>
#include "errors.h"

#ifndef POSITION_H
#define POSITION_H

class Position {
    private:
    std::string name;
    std::string contents;
    std::vector<int> inputInts;

    public:
    Position(char filename[20], int argc); // argc is necessary to determine how many rotors there are.
    std::vector<int> position_vector;
    int load_position(char filename[20], size_t number_of_rotors);
    int exit_code = 0;
    void insert_to_vector(std::vector<int>& position_vector, std::string contents);
    void print_ints(std::vector<int> position_vector);
};

#endif