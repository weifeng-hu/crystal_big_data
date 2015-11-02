/**
 * @file
 * @author Weifeng Hu
 *
 * @section LICENSE
 *
 * Copyright (C) 2013, 2014, 2015  Weifeng Hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 *
 */

#ifndef MATRIX_FUNCTION_HPP
#define MATRIX_FUNCTION_HPP

#include <vector>
#include <tuple>
#include <matrix/matrix_typedef.hpp>

namespace iquads {

namespace matrix {

  void symmetric_diag( DMatrixHeap& a, DMatrixHeap& eigvec, DMatrixHeap& eigval );

  void symmetric_diag_big( DMatrixHeap& a, DMatrixHeap& eigvec, DMatrixHeap& eigval );

  double distance_of_two_matrices( const DMatrixHeap& mat_a, const DMatrixHeap& mat_b );

  bool is_the_same( const DMatrixHeap& eigval_a, const DMatrixHeap& eigval_b );

  IMatrixHeap compute_boolean_mat( const std :: vector<DMatrixHeap>& eigvals, double tol );

  IMatrixHeap compute_boolean_mat( const std :: vector<DMatrixHeap>& all_matrices );

  std :: vector< std :: tuple< double, int, int> > get_degeneracy_groups( const DMatrixHeap& eigval );

  std :: vector< std :: vector<int> > get_degeneracy_group( const DMatrixHeap& mat );

  std :: vector< std :: vector<int> > get_groups( const IMatrixHeap& boolean_mat );

} // end of namespace matrix

} // end of namespace iquads

#endif
