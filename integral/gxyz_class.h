#include "gaussian.h"

namespace ithaca { namespace integral {

class gxyz
{

public:
  gxyz();
  gxyz( double x, double y, double z, int i, int j, int k, double ax, double ay, double az, double Ax, double Ay, double Az );
  ~gxyz(){};

public:
  double value;
  double calc_val(double rx, double ry, double rz);


public:
  gaussian *gx;
  gaussian *gy;
  gaussian *gz;

private:
  double zeta_x;
  int    power_x; 
  double alpha_x;
  double center_x;

  double zeta_y;
  int    power_y; 
  double alpha_y;
  double center_y;

  double zeta_z;
  int    power_z; 
  double alpha_z;
  double center_z;

  double set_values(double x, double y, double z, int i, int j, int k, double ax, double ay, double az, double Ax, double Ay, double Az);

};

} }
