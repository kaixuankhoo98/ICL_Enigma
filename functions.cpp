#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "functions.h"
#include "errors.h"
using namespace std;

string open_file_string(char filename[20]) {
    ifstream input;
    input.open(filename);

    string loaded_input;
    getline(ifstream(filename), loaded_input);

    input.close();
    return loaded_input;
}
