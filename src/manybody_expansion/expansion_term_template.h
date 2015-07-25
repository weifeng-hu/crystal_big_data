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
 * the Free Software Foundation, either version 3 of the License, or
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

namespace iquads {

namespace manybody_expansion {

template < size_t Order >
class ExpansionFormula
{

};

template <>
class ExpansionFormula<1>
{
  compute()
  {
   return compute_expansion_term<1>();
  };
}

template <>
class ExpansionFormula<2>
{
  compute()
   {
     return compute_expansion_term<1> + compute_expasion_term<2>;
   }
}

} // end of manybody_expansion

} // end of namespace iquads
