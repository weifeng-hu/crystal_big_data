#include "utilities/compute_overlap/overlap_config_class.h"

namespace iqs {

namespace utilities {

overlap_config :: overlap_config( string configfile )
{

  this->same_c1c2_ 	= true;
  this->do_reorder1_ 	= false;
  this->do_reorder2_	= false;
  this->do_reorder1_ao_	= false;
  this->do_reorder1_ao_	= false;

  ifstream file;
  file.open( configfile.c_str(), std::ios::in );
  string entry;
  while( file >> entry ){
   if( entry == "nbas" )	 file >> this->nbas_;
   if( entry == "norb" )	 file >> this->norb_;
   if( entry == "overlap" )	 file >> this->ov_file_;
   if( entry == "c1" ) 	 	 file >> this->c1_file_;
   if( entry == "c2" ){	same_c1c2_ = false;  file >> this->c2_file_; }
   if( entry == "reorder1" ){ do_reorder1_ = true;  file >> this->reorder1_file_; }
   if( entry == "reorder2" ){ do_reorder2_ = true;  file >> this->reorder2_file_; }
   if( entry == "reorder1_ao" ){ do_reorder1_ao_ = true;  file >> this->reorder1_ao_file_; }
   if( entry == "reorder2_ao" ){ do_reorder2_ao_ = true;  file >> this->reorder2_ao_file_; }
  }
  file.close();

} 

} // end of utilities

} // end of iqs
