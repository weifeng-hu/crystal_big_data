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

#ifndef VECTOR_MATRIX_INSTANT_HPP
#define VECTOR_MATRIX_INSTANT_HPP

#include <matrix/vector_matrix_template.hpp>

namespace iquads {

namespace matrix {

  // explicit template instantiation
  template class VectorMatrix< int >;
  template class VectorMatrix< float >;
  template class VectorMatrix< double >;

} // end of namespace matrix

} // end of namespace iquads

#endif
