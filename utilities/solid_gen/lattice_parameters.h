#ifndef LATTICE_PARAMETERS_H
#define LATTICE_PARAMETERS_H

#include <array>
#include <tuple>
#include <iostream>
#include <math.h>
#include "utilities/solid_gen/threed_space.h"

using namespace std;

namespace iquads {

using namespace iquads :: threed_space;

namespace crystal {

struct lattice_parameters
{
public:
  lattice_parameters(){
   this->reset();
  }
  lattice_parameters( tuple<double, double, double> edge_lengths,
                     tuple<double, double, double> angles )
  {
   this->reset();

   this->length_a_ = get<0>( edge_lengths );
   this->length_b_ = get<1>( edge_lengths );
   this->length_c_ = get<2>( edge_lengths );

   this->angle_alpha_ = get<0>( angles ) *pi/180e0;
   this->angle_beta_  = get<1>( angles ) *pi/180e0;
   this->angle_gamma_ = get<2>( angles ) *pi/180e0;
  }

public:
  void reset(){
   this->length_a_ = 0.0e0;
   this->length_b_ = 0.0e0;
   this->length_c_ = 0.0e0;
   this->angle_alpha_ = 0.0e0;
   this->angle_beta_ = 0.0e0;
   this->angle_gamma_ = 0.0e0;
   for( size_t i = 0; i < 3; i++ ){
    this->trans_vectors.at(i).fill(0.0e0);
   }
  }

public:
  array<double, 3> get_trans_vector_a() const 
   { return this->trans_vectors.at(0); }
  array<double, 3> get_trans_vector_b() const
   { return this->trans_vectors.at(1); }
  array<double, 3> get_trans_vector_c() const
   { return this->trans_vectors.at(2); }

public:
  void compute_translational_vectors(){
   // the order must be maintained
   array< double, 3 > a_vec = this->set_a_vec();
   array< double, 3 > b_vec = this->set_b_vec();
   array< double, 3 > c_vec = this->set_c_vec();
   this->trans_vectors = array<array<double, 3>, 3> { a_vec, b_vec, c_vec };
  }

  void print_info(){
   char line[100];
   cout << "Lattice Parameters:" << endl;
   sprintf(line," length a: %12.8f", this->length_a_);
   cout << line << endl;
   sprintf(line," length b: %12.8f", this->length_b_);
   cout << line << endl;
   sprintf(line," length c: %12.8f", this->length_c_);
   cout << line << endl;

   sprintf(line," angle alpha: %12.8f", this->angle_alpha_);
   cout << line << endl;
   sprintf(line," angle beta: %12.8f", this->angle_beta_);
   cout << line << endl;
   sprintf(line," angle gamma: %12.8f", this->angle_gamma_);
   cout << line << endl;

   cout << "Lattice vectors" << endl;
   sprintf(line," vector a: [ %12.8f %12.8f %12.8f ]", 
     this->trans_vectors.at(0).at(0), this->trans_vectors.at(0).at(1),
     this->trans_vectors.at(0).at(2));
   cout << line << endl;
   sprintf(line," vector b: [ %12.8f %12.8f %12.8f ]", 
     this->trans_vectors.at(1).at(0), this->trans_vectors.at(1).at(1),
     this->trans_vectors.at(1).at(2));
   cout << line << endl;
   sprintf(line," vector c: [ %12.8f %12.8f %12.8f ]", 
     this->trans_vectors.at(2).at(0), this->trans_vectors.at(2).at(1),
     this->trans_vectors.at(2).at(2));
   cout << line << endl;

  }

private:
  array< double, 3 > set_a_vec(){
   array< double, 3 > retval = { this->length_a_, 0.0e0, 0.0e0 };
   return retval;
  };

  array< double, 3 > set_b_vec(){
   array< double, 3 > retval;
   retval.at(0) = this->length_b_ * cos( this->angle_gamma_ );
   retval.at(1) = this->length_b_ * sin( this->angle_gamma_ );
   retval.at(2) = 0.0e0;
   return retval;
  };

  array< double, 3 > set_c_vec(){
   array< double, 3 > retval;
   retval.at(0) = this->length_a_ * cos( this->angle_alpha_ );
   {
    retval.at(1) = 1.0e0/ ( this->length_b_ * sin( this->angle_gamma_ ) ) *
     ( this->length_c_ * this->length_b_ * cos( this->angle_beta_ ) - 
       this->length_c_ * this->length_b_ * cos( this->angle_gamma_ ) * cos( this->angle_alpha_ ) );
   }
   retval.at(2) 
    = sqrt( pow( this->length_c_, 2 ) - pow( retval.at(0), 2) - pow( retval.at(1), 2 ) );
   return retval;
  };

private:
  array< array< double, 3 >, 3 > trans_vectors;
  double length_a_;
  double length_b_;
  double length_c_;
  double angle_alpha_;
  double angle_beta_;
  double angle_gamma_;

}; // end of struct lattice_constants

} // end of namespace crystal

} // end of namespace iquads

#endif
