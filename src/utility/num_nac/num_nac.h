#include <vector>
#include <string>

double R_bohr = 5.291772109217e-1;
string orca_exe = "/home/wh288/Development/orca_dyn/x86_exe/orca";
string fci_exe = "/home/wh288/iquads/fci//fci_6/Be";
bool execution = true;
bool verbose = true;

void numerical_nac_driver( vector<string> args );
