#include <string>
#include "errors.h"
#include "Rotor.h"
using namespace std;

string open_file_string(char filename[20]);

int verify_string(string cin_stream);
string convert_string(string cin_stream);

string encrypt(string input, char* argv[], int argc);
Rotor make_rotor(int argc, char* argv[], int number);
int exit_codes_total(int argc, char* argv[]);
char through_plugboard(int argc, char* argv[], char input);
bool rotate_true(vector<int> rotor, vector<int> notch);