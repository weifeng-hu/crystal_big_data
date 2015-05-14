#include <cmath.h>
#include "gxyz.h"

namespace ithaca { namespace integral {

double gxyz::calc_val( double rx, double ry, double rz )
{
  double retval;

  double val_x = (this->gx)->calc_val(rx);
  double val_y = (this->gy)->calc_val(ry);
  double val_z = (this->gz)->calc_val(rz);

  retval = val_x * val_y * val_z;

  return retval;

};

double gxyz::set_values(double x, double y, double z, int i, int j, int k, double ax, double ay, double az, double Ax, double Ay, double Az)
{
  this->zeta_x = x;
  this->power_x = i;
  this->alpha_x = ax;
  this->center_x = Ax;

  this->zeta_y = y;
  this->power_y = j;
  this->alpha_y = ay;
  this->center_y = Ay;

  this->zeta_z = z;
  this->power_z = k;
  this->alpha_z = az;
  this->center_z = Az;

}

gxyz::gxyz( double x, double y, double z, int i, int j, int k, double ax, double ay, double az, double Ax, double Ay, double Az)
{

  this->zeta_x = x;
  this->power_x = i;
  this->alpha_x = ax;
  this->center_x = Ax;

  this->zeta_y = y;
  this->power_y = j;
  this->alpha_y = ay;
  this->center_y = Ay;

  this->zeta_z = z;
  this->power_z = k;
  this->alpha_z = az;
  this->center_z = Az;

  this->gx = (gaussian*) operator new ( sizeof(gaussian) );  gx->set_value( x, i, ax, Ax);
  this->gy = (gaussian*) operator new ( sizeof(gaussian) );  gy->set_value( y, j, ay, Ay);
  this->gz = (gaussian*) operator new ( sizeof(gaussian) );  gz->set_value( z, k, az, Az);

}

} }
