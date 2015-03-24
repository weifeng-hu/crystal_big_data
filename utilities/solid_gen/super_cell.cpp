#include <string>
#include <vector>
#include "utilities/solid_gen/super_cell.h"

namespace iquads {

namespace crystal{

void super_cell::recentralize()
{

  double x_plus = 0.0e0;
  double x_minus = 0.0e0;
  double y_plus = 0.0e0;
  double y_minus = 0.0e0;
  double z_plus = 0.0e0;
  double z_minus = 0.0e0;
  size_t ncell = this->store_.size();
  for( size_t icell = 0; icell < ncell; icell++ ){
   unit_cell cellx = store_.at(icell);
   for( size_t iatom = 0; iatom < cellx.get_store().size(); iatom++ ){
    double x = cellx.get_atom(iatom).get_x();
    double y = cellx.get_atom(iatom).get_y();
    double z = cellx.get_atom(iatom).get_z();
    if( x > x_plus ) x_plus = x;
    if( y > y_plus ) y_plus = y;
    if( z > z_plus ) z_plus = z;
   }
  }
  for( size_t icell = 0; icell < ncell; icell++ ){
   unit_cell cellx = store_.at(icell);
   for( size_t iatom = 0; iatom < cellx.get_store().size(); iatom++ ){
    double x = cellx.get_atom(iatom).get_x();
    double y = cellx.get_atom(iatom).get_y();
    double z = cellx.get_atom(iatom).get_z();
    if( x < x_minus ) x_minus = x;
    if( y < y_minus ) y_minus = y;
    if( z < z_minus ) z_minus = z;
   }
  }

  double x_center = (x_plus - x_minus)/2.0e0;
  double y_center = (y_plus - y_minus)/2.0e0;
  double z_center = (z_plus - z_minus)/2.0e0;

  for( size_t icell = 0; icell < ncell; icell++ ){
   unit_cell cellx = store_.at(icell);
   for( size_t iatom = 0; iatom < cellx.get_store().size(); iatom++ ){
    double new_x = cellx.get_atom(iatom).get_x() + x_center;
    double new_y = cellx.get_atom(iatom).get_y() + y_center;
    double new_z = cellx.get_atom(iatom).get_z() + z_center;
    cellx.set_atom(iatom).set_x() = new_x;
    cellx.set_atom(iatom).set_y() = new_y;
    cellx.set_atom(iatom).set_z() = new_z;
   }
   store_.at(icell) = cellx;
  }

}

fragment super_cell::cut_spherical( double cutoff_in )
{

  fragment retval;

  vector< unit_cell > sphere;
  sphere.resize(0);
  double cutoff = cutoff_in;
  double increment = 0.3;
  bool no_cut = false;
  size_t ncell = store_.size();
  for( size_t icell = 0; icell < ncell; icell++ ){
   unit_cell cellx = store_.at(icell);
   if( cellx.out_of_range( cutoff ) == false ){
    sphere.push_back( cellx );
   }
  }

  for( size_t icell = 0; icell < sphere.size(); icell++ ){
   unit_cell cellx = sphere.at(icell);
   for( size_t iatom = 0; iatom < cellx.get_store().size(); iatom++ ){
    retval.set_store().push_back( cellx.get_atom( iatom) );
   } 
  }

  return retval;

}

fragment super_cell::cut_cubic()
{

}

fragment super_cell::cut( string cut_method, double cutoff )
{

  this->recentralize();
  fragment retval;
  if( cut_method == "spherical" ){
   retval = cut_spherical( cutoff );
  }
  else if( cut_method == "cubic" ){
   retval = cut_cubic();
  }

  return retval;

};

}

}
