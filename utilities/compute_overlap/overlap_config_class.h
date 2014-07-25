#include <string>
#include <fstream>

using namespace std;

namespace iqs {

namespace utilities {

class overlap_config
{

private:
  int nbas_, norb_ ;

  // filenames
  string ov_file_ ;
  string c1_file_ ;
  string c2_file_ ;
  string reorder1_ao_file_ ;
  string reorder2_ao_file_ ;
  string reorder1_file_ ;
  string reorder2_file_ ;

  bool same_c1c2_;
  bool do_reorder1_, do_reorder2_;
  bool do_reorder1_ao_, do_reorder2_ao_ ;

public:
  overlap_config( string configfile );
  ~overlap_config(){};

public:
  int nbas(){ return this->nbas_; }
  int norb(){ return this->norb_; }

  string ov_file(){ return this->ov_file_ ; }
  string c1_file(){ return this->c1_file_ ; }
  string c2_file(){ return this->c2_file_ ; }
  string reorder1_ao_file(){ return this->reorder1_ao_file_ ; }
  string reorder2_ao_file(){ return this->reorder2_ao_file_ ; }
  string reorder1_file(){ return this->reorder1_file_ ; }
  string reorder2_file(){ return this->reorder2_file_ ; }

  bool same_c1c2(){ return this->same_c1c2_ ; }
  bool do_reorder1(){ return this->do_reorder1_ ; }
  bool do_reorder2(){ return this->do_reorder2_ ; }
  bool do_reorder1_ao(){ return this->do_reorder1_ao_ ; }
  bool do_reorder2_ao(){ return this->do_reorder2_ao_ ; }

}; // end of overlap_config

} // end of utilities

} // end of iqs
