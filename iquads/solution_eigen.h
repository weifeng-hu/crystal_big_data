#include <tuple>
#include "iquads/solution_base.h"

namespace iquads{

template < class Teigvec, class Teigval >
struct solution_eigen : public solution_base
{
public:
  solution_eigen() : solution_base( "eigen" )
    {  }

public:
  std::tuple < Teigvec, Teigval > get_eigpair() const 
    { return std::make_tuple< Teigvec, Teigval>( eigvec, eigval ) }
  std::tuple < Teigvec, Teigval > set_eigpair()
    { return std::make_tuple< Teigvec, Teigval>( eigvec, eigval ) }
  Teigvec get_eigvec() const
    { return this->eigvec; }
  Teigvec& set_eigvec()
    { return this->eigvec; }
  Teigval get_eigval() const
    { return this->eigval; }
  Teigval& set_eigval()
    { return this->}

private:
  Teigvec eigvec;
  Teigval eigval;

};

typedef solution_eigen< orb_coeff, vector<double> > orb_solution;
typedef solution_eigen< ci_vec, double > ci_solution;
typedef solution_eigen< mps, double > mps_solution;

} // end of iquads
