#include <vector>
#include <string>

using namespace std;

namespace iqs { namespace utilities {

struct ao2mo_config
{

  int nbas, norb, nocc, nele, ns;
  vector<int> orbital_window;
  double nucl_rep;

  string c_file;
  string one_integral_file;
  string two_integral_file;

  ao2mo_config( string input );
  ~ao2mo_config(){};

};

} } // end of iqs::utilities
