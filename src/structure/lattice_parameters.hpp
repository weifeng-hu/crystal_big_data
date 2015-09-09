/**
 *  This source code applies all the terms in 
 *  GNU GENERAL PUBLIC LICENSE (GPL), Version3, 29 June 2007.
 *
 *  Copyright (C) 2013-2015 Weifeng Hu, all rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#ifndef LATTICE_PARAMETERS_HPP
#define LATTICE_PARAMETERS_HPP

#include <array>
#include <tuple>
#include <iostream>
#include <fstream>
#include <math.h>
#include <blas/blas_interface.hpp>
#include <geometrical_space/threed_space.hpp>

using std::array;
using std::tuple;
using std::cout;
using std::endl;
using std::fstream;

namespace iquads {

using namespace iquads :: geometrical_space :: threed_space;

namespace structure {

struct LatticeParameters 
{
public:
  LatticeParameters(){
   this->reset();
  }
  LatticeParameters( tuple<double, double, double> edge_lengths,
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

  friend ifstream& operator>> ( ifstream& ifs, LatticeParameters& lp ){
   double a,b,c,aa,ab,ay;
   ifs >> a >> b >> c >> aa >> ab >> ay;
   lp = LatticeParameters( make_tuple(a,b,c),make_tuple(aa,ab,ay) );
   lp.compute_translational_vectors();
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

  array<double, 9> get_trans_mat(){
   array<double, 9> retval;
   retval[0] = this->trans_vectors.at(0).at(0);
   retval[1] = this->trans_vectors.at(0).at(1);
   retval[2] = this->trans_vectors.at(0).at(2);
   retval[3] = this->trans_vectors.at(1).at(0);
   retval[4] = this->trans_vectors.at(1).at(1);
   retval[5] = this->trans_vectors.at(1).at(2);
   retval[6] = this->trans_vectors.at(2).at(0);
   retval[7] = this->trans_vectors.at(2).at(1);
   retval[8] = this->trans_vectors.at(2).at(2);
   return retval;
  }

public:
  array< double, 3 > compute_coeffs_of_abc( array< double, 3 > xyz ){
   array< double, 3 > nvec;
   nvec.fill(0.0e0);
   array< double, 9 > trans_mat = this->get_trans_mat();
   ax_b( trans_mat.data(), xyz.data(), nvec.data(), 3 );
   return nvec;
  }

private:
  array< array< double, 3 >, 3 > trans_vectors;
  double length_a_;
  double length_b_;
  double length_c_;
  double angle_alpha_;
  double angle_beta_;
  double angle_gamma_;

}; // end of struct LatticeParameters

} // end of namespace structure

} // end of namespace iquads

#endif
