// ++++++++++++++++++++++++++++++++++++++++++++++
//
//         FRAGMENT GENERATOR MAIN DRIVER
//
// ++++++++++++++++++++++++++++++++++++++++++++++

#include <string>
#include <vector>
#include "utilities/solid_gen/lattice.h"
#include "utilities/solid_gen/crystal_info.h"
#include "utilities/solid_gen/interaction.h"
#include "utilities/solid_gen/fragment_info.h"

int fragment_generator_driver( vector<string> args )
{

  using namespace std;
  using namespace iquads::crystal;

  // get crystal information
  crystal_info info;
  {
   // read the input file
   const int argc = args.size();
   string input_file = args.at(1);
   info.read( input_file );
  }

  // construct the interaction content for the crystal
  interaction interact_picture;
  interact_picture.set_short_range_radius() 
    = info.get_short_range_radius();
  interact_picture.set_long_range_radius() 
    = info.get_long_range_radius();
  interact_picture.set_n_fragment_type() = info.;
  {
   // construct the molecule bulk from the molecular lattice
   molecule_bulk mole_bulk;
   {
    // generate the molecule lattice from unit cell
    molecular_lattice mole_latt( info.get_unit_cell(), info.get_nunits() );
    // initialise the molecule bulk from the whole lattice
    mole_bulk.init_from( &mol_latt );
    // cut the lattice by a radius
    mole_bulk.cut( info.get_bulk_radius() );
   }
   // the interaction object gains a copy of the molecule bulk
   // the original molecule bulk object will be destructed
   interact_picture.set_bulk() = mole_bulk;
  }

  // actual fragment identification
  // base on the interaction setting

  if( info.dimer_requested() == true )
  {
   // short range dimers
   if( info.short_range_requested() == true ){
    fragment_info short_range_dimer_info 
     = interact_picture.identify_subgroups<2>( info.get_short_range_radius() );
    interact_picture.add_fragment_info( short_range_dimer_info );
   }
   // long range dimers
   if( info.long_range_requested() == true ){
    fragment_info long_range_dimer_info 
     = interact_picture.identify_subgroups<2>( inf.get_long_range_radius() );
    interact_picture.add_fragment_info( long_range_dimer_info );
   }
  }

  if( info.trimer_requested() == true )
  {
   // short range trimers
   if( info.short_range_requested() == true ){
    fragment_info short_range_trimer_info 
     = interact_picture.identify_subgroups<3>( info.get_short_range_radius() );
    interact_picture.add_fragment_info( short_range_trimer_info );
   }
   // long range trimers
   if( info.long_range_requested() == true ){
    fragment_info long_range_trimer_info 
     = interact_picture.identify_subgroups<3>( info.get_long_range_radius() );
    interact_picture.add_fragment_info( long_range_trimer_info );
   }
  }

  if( info.tetramer_requested() == true )
  {
   // short range tetramers
   if( info.short_range_requested() == true ){
    fragment_info short_range_tetramer_info
      = interact_picture.identify_subgroups<4>( info.get_short_range_radius() );
    interact_picture.add_fragment_info( short_range_tetramer_info );
   }
   // long range tetramers
   if( info.long_range_requested() == true ){
    fragment_info long_range_tetramer_info 
      = interact_picture.identify_subgroups<4>( info.get_long_range_radius() );
    interact_picture.add_fragment_info( long_range_tetramer_info );
   }
  }

  interact_picture.print_fragment_info();   
  // the generator ends here
  // further functionalties are anticipated

  return 0;

}  // end of fragment_generator_driver()
