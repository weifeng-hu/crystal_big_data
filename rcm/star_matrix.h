
namespace iqs {

namespace rcm {

class star_matrix
{
private:
  double** orig_mat;
  int dim0, dim1;
  char** star_mat;
  double threshold;
  int nstar_;

public:
  void set_dim0( int dim ){ this->dim0 = dim; }
  void set_dim1( int dim ){ this->dim1 = dim; }
  void set_threshold( double thres ){ this->threshold = thres; };

  int& get_dim0(){ return this->dim0; }
  int& get_dim1(){ return this->dim1; }
  double& get_threshold(){ return this->threshold; }

  void generate_star_mat();
  void print_star_mat();
  int nstar(){ return this->nstar_; }

  void generate_adj( std::vector<int>& xadj, std::vector<int>& adj );
  vector<int> reorder( vector<int>& xadj, vector<int>& adj );

public:
  star_matrix( double thres, iqs::matrix::square_matrix mtr );
  star_matrix(){};
  ~star_matrix(){};

};

} // end of rcm

} // end of iqs
