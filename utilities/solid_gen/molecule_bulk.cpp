#include <vector>
#include <string>
#include <tuple>
#include <iostream>
#include "utilities/solid_gen/matrix.h"
#include "utilities/solid_gen/matrix_function.h"
#include "utilities/solid_gen/atom.h"
#include "utilities/solid_gen/molecule.h"
#include "utiltties/solid_gen/mole_bulk.h"

namespace iquads{

namespace crystal{

void mole_bulk :: cut( double Radius )
{

};

void mole_bulk :: find_unique_dimers()
{

  vector< tuple< vector<double>, int, int > > eigval_tuples;
  for( size_t imole = 0; imole < n_molecule; imole++ ){
   molecule molei = bulk.get(imole);
   for( size_t jmole = 0; jmole < imole; jmole++ ){
    molecule molej = bulk.get(jmole);
    vector<molecule> dimerij;
    dimerij.push_back(molei);
    dimerij.push_back(molej);
    dimer dimer_tmp( dimerij );
    tuple< vector<double>, int, int > eigval_tuple_tmp;
         = make_tuple( dimer_tmp.get_distm_eigval(), imole, jmole );
    eigval_tuples.push_back( eigval_tuple_tmp );
   }
  }

//  this->dimerlist = matrix :: eval_group_list( eigval_tuples );
  size_t nset = eigvals_tuples.size();
  vector<double> diff_mat;
  diff_mat.resize( nset*nset );
  vector<double> eigvec_diff_mat;
  eigvec_diff_mat.resize( nset*nset );
  vector<double> eigval_diff_mat;
  eigval_diff_mat.resize( nset );
  for( size_t iset = 0; iset < nset; iset++ ){
   vector<double> eigvali = get<0>( eigval_tuples.at(iset) );
   for( size_t jset = 0; jset < nset; jset++ ){
    vector<double> eigvalj = get<1>( eigval_tuples.at(jset) );
    diff_mat( iset * nset + jset ) = is_the_same( eigvali, eigvalj ) ? 1.0e0 : 0.0e0;
   }
  }
  diag( diff_mat.data(), eigvec_diff_mat.data(), eigval_diff_mat.data(), nset );
  vector< tuple< double, int, int > > eigen_struct = matrix :: get_degeneracy_struct( eigval_diff_mat );
  vector< vector<int> > groups = matrix :: judge_groups( eigen_structure );
  this->identical_dimerlist.resize(groups.size());
  for( size_t igroup = 0; igroup < groups.size(); igroup++ ){
   this->identical_dimerlist.at(igroup).resize( group.at(igroup).size() );
   for( size_t iset = 0; iset < group.at(igroup).size(); iset++ ){
    size_t set = group.at(iset);
    this->identical_dimerlist.at(igroup).at(iset) = make_tuple( get<1>( eigval_tuples.at(set) ), get<2>( eigval_tuples.at(set) ) );
   }
  }

};

void mole_bulk :: find_unique_trimers()
{

  for( size_t imole = 0; imole < n_molecule; imole++ ){
   molecule molei = bulk.get(imole);
   for( size_t jmole = 0; jmole < n_molecule; jmole++ ){
    molecule molej = bulk.get(jmole);
    for( size_t kmole = 0; kmole < n_molecule; kmole++ ){
     molecule molek = bulk.get(kmole);
    }
   }
  }

};

void mole_bulk :: find_unique_tetramers()
{

  for( size_t imole = 0; imole < n_molecule; imole++ ){
   molecule molei = bulk.get(imole);
   for( size_t jmole = 0; jmole < n_molecule; jmole++ ){
    molecule molej = bulk.get(jmole);
    for( size_t kmole = 0; kmole < n_molecule; kmole++ ){
     molecule molek = bulk.get(kmole);
     for( size_t lmole = 0; lmole < n_molecule; lmole++ ){
      molecule molel = bulk.get(lmole);
     }
    }
   }
  }

};

} // end of crystal

} // end of iquads
