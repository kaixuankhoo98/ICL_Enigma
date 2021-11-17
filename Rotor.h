#include <string>
#include <vector>
#include "errors.h"

#ifndef ROTOR_H
#define ROTOR_H

class Rotor {
    private:
    std::string name;
    std::string contents;
    std::vector<int> inputInts;

    public:
    Rotor(char filename[20]);
    Rotor();
    int length;
    std::vector<int> rotor_vector;
    std::vector<int> notches;
    int load_rotor(char filename[20]);
    int exit_code = 0;
    void insert_to_vector(std::vector<int>& rotor_vector, std::string contents);
    void get_notches(std::vector<int>& notches, std::vector<int> rotor_vector);
    void rotate_rotor(std::vector<int>& rotor_vector);
    void print_ints(std::vector<int> rotor_vector);
};

#endif