
namespace ithaca { namespace integral {

class gaussian
{
public:
 gaussian();
 gaussian( double z, int i, double a, double A );
 ~gaussian(){};

public:
 double value;

private:
 double zeta;
 double power;
 double alpha;
 double center;

public:
 void set_values( z, i, a, A);
 double calc_val( double x );

};

} }
