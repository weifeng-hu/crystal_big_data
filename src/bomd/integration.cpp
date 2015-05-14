#include "integration.h"

int get_R( timeframe& oldframe, timeframe& newframe, double t)
{
  for( int i = 0; i < natom ; i++ ){
   for( int j = 0; j < 3; j++ ){
    newframe.velocity[i][j] = oldframe.velocity[i][j] + oldframe.force[i][j] * t /(2 * oldframe.mass[i] );
    newframe.coord[i][j] = oldframe.coord[i][j] + t * newframe.velocity[i][j];
   }
  }

}
