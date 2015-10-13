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

#include <iostream>
#include <chemistry/element.hpp>
#include <chemistry/element_list.hpp>
#include <chemistry/periodic_table.hpp>

int main( int argc, char* argv[] ) {

  iquads :: chemistry :: Element element( iquads :: chemistry :: Element :: ElectronConfiguration(1), (char*)("unknown"), (char*)("unkown"), 1, 1, 1, 1 );
  iquads :: chemistry :: Element element_2 = iquads :: chemistry :: element :: H;
  iquads :: chemistry :: Element element_3 = iquads :: chemistry :: element :: He;

  std :: cout << element.chemical_symbol()  << std :: endl;
  std :: cout << element.element_name()  << std :: endl;
  std :: cout << element.atomic_number() << std :: endl;
  std :: cout << element.atomic_weight() << std :: endl;
  std :: cout << element.group() << std :: endl;
  std :: cout << element.period() << std :: endl;

  iquads :: chemistry :: PeriodicTable table;

}
