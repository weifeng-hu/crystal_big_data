#include <string>
#include <iostream>

using namespace std;

namespace iqs {

namespace rcm {

void rcm_help(){

  cout << "Reversed Curtill-Mckee Program " << endl;
  cout << "to reorder orbitals for the DMRG anzatz " << endl;
  cout << "via one-electron integral matrix hij or exchange two-electron integral matrix Kij " << endl;
  cout << endl;
  cout << "usage: " ;
  cout << " reorder mode: rcm -r e/h integral_filename theshold_to_reorder threshold_to_print " << endl;
  cout << "       " << " show mode:    rcm -s e/h integral_filename reorder_filename theshold_to_print " << endl;
  cout << endl;

}

} // end of rcm

} // end of iqs
