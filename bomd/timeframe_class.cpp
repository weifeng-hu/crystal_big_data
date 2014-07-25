#include <vector>
#include "timeframe.h"

namespace bomd {

timeframe :: timeframe( int n )
{
  this->natom = n;
  this->ncoord = 3 * n;

  this->element.resize(n);
  this->mass.resize(n);
  this->velocity.resize(n);
  for( int i = 0; i < n; i++ ){ velocity[i].resize(3); }
  this->force.resize(n);
  for( int i = 0; i < n; i++ ){ force[i].resize(3); }
  this->coord.resize(n);
  for( int i = 0; i < n; i++ ){ coord[i].resize(3); }

}

}
