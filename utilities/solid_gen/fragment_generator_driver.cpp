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

int fragment_generator_driver( vector<string> args )
{

  using namespace std;
  using namespace iquads::crystal;

  cout << endl;
  cout << "===========================================" << endl;
  cout << " Fragment Generator for Molecular Crystals" << endl;
  cout << "===========================================" << endl;
  cout << endl;
  cout << "Starting ..." << endl;

  // get crystal information
  molecular_crystal_info info;
  {
   cout << "Reading input ..."; 
   // read the input file
   const int argc = args.size();
   string input_file = args.at(1);
   info.read( input_file );
   cout << " ok" << endl;
  }

  // construct the interaction content for the crystal
  interaction interact_picture;
  interact_picture.set_short_range_radius() 
    = info.get_short_range_radius();
  interact_picture.set_long_range_radius() 
    = info.get_long_range_radius();
  {
   // construct the molecule bulk from the molecular lattice
   molecule_bulk mole_bulk;
   {
    // generate the molecule lattice from unit cell
    molecular_lattice mole_latt;
    mole_latt.set_primitive( info.get_molecular_cell() );
    mole_latt.generate( info.get_sizes() );
    mole_bulk.init_from( &mole_latt );
    cout << "Found " << mole_bulk.get_nmolecule() << " molecules in the bulk BEFORE cut: " << endl;
    // cut the lattice by a radius
    mole_bulk.cut( info.get_radius() );
    cout << "Found " << mole_bulk.get_nmolecule() << " molecules in the bulk AFTER cut: " << endl;
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
    cout << "Identifying short range dimers ... " << endl;
    cout << "   Averaged intermolecular distance (center of mass): " << info.get_short_range_radius() << " Angstrom " << endl;
    fragment_group_info short_range_dimer_info 
     = interact_picture.identify_subgroups<2>( info.get_short_range_radius() );
    interact_picture.add_fragment_group( short_range_dimer_info );
   }
   // long range dimers
   if( info.long_range_requested() == true ){
    cout << "long range dimers: radius " << info.get_long_range_radius() << " Angstrom " << endl;
    fragment_group_info long_range_dimer_info 
     = interact_picture.identify_subgroups<2>( info.get_long_range_radius() );
    interact_picture.add_fragment_group( long_range_dimer_info );
   }
  }

  if( info.trimer_requested() == true )
  {
   // short range trimers
   if( info.short_range_requested() == true ){
    fragment_group_info short_range_trimer_info 
     = interact_picture.identify_subgroups<3>( info.get_short_range_radius() );
    interact_picture.add_fragment_group( short_range_trimer_info );
   }
   // long range trimers
   if( info.long_range_requested() == true ){
    fragment_group_info long_range_trimer_info 
     = interact_picture.identify_subgroups<3>( info.get_long_range_radius() );
    interact_picture.add_fragment_group( long_range_trimer_info );
   }
  }

  if( info.tetramer_requested() == true )
  {
   // short range tetramers
   if( info.short_range_requested() == true ){
    fragment_group_info short_range_tetramer_info
      = interact_picture.identify_subgroups<4>( info.get_short_range_radius() );
    interact_picture.add_fragment_group( short_range_tetramer_info );
   }
   // long range tetramers
   if( info.long_range_requested() == true ){
    fragment_group_info long_range_tetramer_info 
      = interact_picture.identify_subgroups<4>( info.get_long_range_radius() );
    interact_picture.add_fragment_group( long_range_tetramer_info );
   }
  }

  cout << endl;
  interact_picture.print_summary();   
  if( info.visual_requested() )interact_picture.run_gview();   
  // the generator ends here
  // further functionalties are anticipated

  return 0;

}  // end of fragment_generator_driver()
