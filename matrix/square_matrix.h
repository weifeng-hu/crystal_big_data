#include <vector>
#include <string>
#include <fstream>

using namespace std;

namespace iqs {

namespace matrix {

class square_matrix
{

private:
  int dim;
  vector< vector<double> > data;

public:
  square_matrix( int d );
  square_matrix( int d, double** mat){};
  square_matrix(){};
  ~square_matrix(){};

public:
  vector< vector<double> >& get_matrix(){ return this->data; };
  int get_dim(){ return this->dim; }

  double& get_element( int i1, int i2){ return data.at(i1).at(i2); }
  double& operator() ( int i1, int i2 ){ return data.at(i1).at(i2); } 

  square_matrix transform( square_matrix& u_mtr );

public:
  void read_matrix( string filename );

};

} // end of matrix

} // end of iqs
