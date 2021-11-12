// Header files
#include <string>
using namespace std;

void load_plugboard(int argc, char *argv[], int plugboard[26], int& number, int& plug_count);
void load_reflector(int argc, char *argv[], int reflector[], int& number, int& refl_count);
int load_rotor(int argc, char filename[20], int rotor[52], int& number);

int notch_count(char filename[20]);
bool is_rotor_mapping(char filename[20]);
bool is_rotor_indexvalid(char filename[20], int index);
bool is_numeric(char filename[20], int index);
bool is_numeric(string input);