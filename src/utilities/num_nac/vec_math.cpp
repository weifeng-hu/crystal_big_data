#include <vector>
#include "utilities/num_nac/vec_math.h"

using namespace std;

namespace iquads{

namespace num_nac{

double product( vector<double> wave1, vector<double> wave2 )
{

  double retval = 0.0e0;
  const int len = wave1.size();

  for( size_t i = 0; i < len; i++ ){
   retval += wave1.at(i) * wave2.at(i);
  }

  return retval;

}

void scale( vector<double>& wave, double scale )
{
  for( size_t i = 0; i < wave.size(); i++ ){
   wave.at(i) *= scale;
  }
}

}

}
