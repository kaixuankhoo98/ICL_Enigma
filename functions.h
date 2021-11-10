// Header files
#include <string>
using namespace std;

void load_plugboard(int argc, char *argv[], int plugboard[26], int& number, int& plug_count);
void load_reflector(int argc, char *argv[], int reflector[], int& number, int& refl_count);

bool is_numeric(string input);