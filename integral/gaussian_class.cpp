#include <cmath.h>
#include "basisfunction.h"

namespace ithaca { namespace integral {

double gaussian::calc_val( double x )
{
  return power(zeta,power) * exp(-1.0e0 * alpha * power( ( x - center ),2) );
}

void gaussian::set_values( double z, int i, double a, double A )
{
  this->zeta = z;
  this->power = i;
  this->alpha = a;
  this->center = A;
}

gaussian::gaussian( double z, int i, double a, double A )
{

  this->zeta   = z;
  this->power  = i;
  this->alpha  = a;
  this->center = A;

}

/*
gaussian::gaussian( double z, int i, double a, double A, double r )
{

  this->zeta   = z;
  this->power  = i;
  this->alpha  = a;
  this->center = A;

  this->value = power(zeta,power) * exp( -1.0e0 * alpha * power( ( r - center ),2) );

}
*/

} } 
