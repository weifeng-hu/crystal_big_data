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

#ifndef BULK_INSTANT_HPP
#define BULK_INSTANT_HPP

#include <string>
#include <vector>
#include <structure/atom.hpp>
#include <structure/molecule.hpp>
#include <structure/bulk_template.hpp>

namespace iquads {

namespace structure {

  /**
   * explicit template instantiation and typedef for lattice
   */
  template class Bulk< Atom >;
  template class Bulk< Molecule >;

  typedef Bulk< Atom >    AtomicBulk;
  typedef Bulk< Molecule > MolecularBulk;

} // end of namespace structure

} // end of namespace iquads

#endif
