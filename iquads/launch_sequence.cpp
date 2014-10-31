#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include "iquads/launch_sequence.h"

using namespace std;

namespace iquads{

void launch_sequence :: setup_seqs ( iquads :: command cmd )
{

  this->steps.resize(0);
  const vector<string> keywords = cmd.get_keywords();
  for( int i = 0; i < keywords.size(); i++ ){
   for( int j = 0; j < (iquads :: known_seqs).size(); j++ ){
    const string known_seq = known_seqs.at(j);
    if( boost::iequals( keywords, known_seq ) ){
     steps.push_back( load_seq_default( known_eq ) );
    }
   }
  }

}

}
