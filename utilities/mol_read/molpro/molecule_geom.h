#include <string>
#include <vector>

struct atom
{
  std::string element;
  double x;
  double y;
  double z;

};

class molecule_geom
{
public:
  int natom;
  std::vector< atom > coord;

public:
  molecule_geom( int n ){
   coord.resize(n);
  };
  ~molecule_geom(){};

};
