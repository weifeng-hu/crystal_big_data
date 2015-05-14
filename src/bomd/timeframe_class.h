#include <vector>

namespace bomd {

class timeframe
{
public:
  int natom;
  int ncoord;
 
  std::vector<char> element;
  std::vector<double> mass;
  std::vector< std::vector<double> > coord;
  std::vector< std::vector<double> > velocity;
  std::vector< std::vector<double> > force;

  double energy;

public:
  timeframe( int n );
  ~timeframe();

public:
  // need to add an operator = to assign the content of the whole class

}; // end of class

} // end of bomd
