#include <string>
#include "errors.h"
#include "Rotor.h"

std::string open_file_string(char filename[20]);

int verify_string(std::string cin_stream);
std::string convert_string(std::string cin_stream);

std::string encrypt(std::string input, char* argv[], int argc);
Rotor make_rotor(int argc, char* argv[], int number);
int exit_codes_total(int argc, char* argv[]);
int exit_code_plugboard(int argc, char* argv[]);
int exit_code_reflector(int argc, char* argv[]);
int exit_code_rotor(int argc, char* argv[]);
int exit_code_position(int argc, char* argv[]);
char through_plugboard(int argc, char* argv[], char input);
bool rotate_true(std::vector<int> rotor, std::vector<int> notch);