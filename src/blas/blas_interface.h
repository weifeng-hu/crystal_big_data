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

#ifndef BLAS_INTERFACE_H
#define BLAS_INTERFACE_H

void ax_b( const double* a, const double* b, const double* x, const int dimen );
void mat_x_mat( const double* a, const double* b, double* c, const double coeff, const int nrow_a, const int ncol_a, const int nrow_b, const int ncol_b, const bool transa, const bool transb );

void diag( const double* mat, double* eigvec, double* eigval, const int dim );

void a_x_b_x_at( double* newmat, const double* b, const double* a, const int nrow_a, const int ncol_a );

extern "C"
{

  void ax_b_( const double* a, const double* b, const double* x, const int* dimen );

  void mat_x_mat_( const double* a, const double* b, double* c, const double* coeff, const int* nrow_a, const int* ncol_a, const int* nrow_b, const int* ncol_b, const int* _transa, const int* _transb );

  void symdiag_( double* eigvec, double* eigval, const int* n );

}

#endif
