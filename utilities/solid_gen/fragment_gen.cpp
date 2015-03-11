#include <string>
#include "cell.h"
#include "fragment.h"
#include "eclidean_dis_mat.h"

using namespace std;

int fragment_gen_driver( vector<string> args )
{

  const int argc = args.size();
  string input_file = args.at(1);
  iquads::crystal:crystal_info info; 
  info.read( input_file );

  iquads::crystal::super_cell big_cell;
  {
   iquads::crystal::unit_cell u_cell( info.get_unit_cell() );
   big_cell.set_unit_cell() = u_cell;
   big_cell.generate( info.get_nunit() );
  }

  iquads::crystall:eclidean_dis_mat edm;
  { 
   iquads::crystal::big_fragment big_frag = big_cell.cut( info.get_cut_method() );
   edm.compose( big_frag );
   edm.diagonalise();
   edm.print_eigen_pairs();
  }

}
