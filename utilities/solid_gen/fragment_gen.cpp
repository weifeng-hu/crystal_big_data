#include <string>
#include "utilities/solid_gen/super_cell.h"
#include "utilities/solid_gen/crystal_info.h"
#include "utilities/solid_gen/fragment.h"
#include "utilities/solid_gen/eclidean_dis_mat.h"

int fragment_gen_driver( vector<string> args )
{

  using namespace std;

  const int argc = args.size();
  string input_file = args.at(1);
  iquads::crystal::crystal_info info; 
  info.read( input_file );

  iquads::crystal::super_cell big_cell;
  {
   big_cell.set_primitive( info.get_unit_cell() );
   big_cell.generate( info.get_nunits() );
  }

  iquads::crystal::eclidean_dis_mat edm(0);
  { 
   iquads::crystal::fragment big_frag = big_cell.cut( info.get_cut_method(), info.get_cutoff() );
   edm.compose( big_frag );
   edm.diagonalise();
   edm.print_eigen_pairs();
  }

}
