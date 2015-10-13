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

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <tuple>
#include <array>
#include <string>

namespace iquads {

namespace chemistry {

using std :: string;
using std :: array;

class Element {
public:
  struct ElectronConfiguration {
    public:
      constexpr ElectronConfiguration(
         size_t n_1s = 0,
         size_t n_2s = 0, size_t n_2p = 0,
         size_t n_3s = 0, size_t n_3p = 0, size_t n_3d = 0,
         size_t n_4s = 0, size_t n_4p = 0, size_t n_4d = 0, size_t n_4f = 0, 
         size_t n_5s = 0, size_t n_5p = 0, size_t n_5d = 0, size_t n_5f = 0, size_t n_5g = 0,
         size_t n_6s = 0, size_t n_6p = 0, size_t n_6d = 0, size_t n_6f = 0, size_t n_6g = 0, size_t n_6h = 0,
         size_t n_7s = 0, size_t n_7p = 0, size_t n_7d = 0, size_t n_7f = 0, size_t n_7g = 0, size_t n_7h = 0, size_t n_7i = 0 
      ): 
          shell_occ_ ( array < size_t, 28 > { n_1s,
                                              n_2s, n_2p,
                                              n_3s, n_3p, n_3d,
                                              n_4s, n_4p, n_4d, n_4f, 
                                              n_5s, n_5p, n_5d, n_5f, n_5g,
                                              n_6s, n_6p, n_6d, n_6f, n_6g, n_6h,
                                              n_7s, n_7p, n_7d, n_7f, n_7g, n_7h, n_7i } ) 
       {
         /**
          * the constructor body must be either deleted or defaulted or contain only the following:
          *  - null statements
          *  - static_assert declarations
          *  - typedef declarations and alias declarations that do not define classes or enumerations
          *  - using declarations
          *  - using directives
          */
       }

//    public:
//      struct SubShellConfiguration {
//        public:
//        private:
//          array< array< 2 * NUM + 1 >, NUM > store;
//      };
//    public:
//      ElectronConfiguration() { };
//      ElectronConfiguration( string config_info ) {
//
//      };
//    private:
//      array< array< array< int, MSHELL = 2 * JSHELL + 1 >, ISHELL >, N_SHELL > config_;
    public:
      size_t nelec() const {
        size_t retval;
        for( size_t isubshell = 0; isubshell < this->shell_occ_.size(); isubshell++ ) {
          retval += shell_occ_[isubshell];
        }
      }
    private:
      array< size_t, 28 > shell_occ_;
  }; // end of struct ElectronConfiguration

public:
  /**
   *  std :: string is not used here, because it has non-trivial destructors 
   *  thus prevents the use of constexpr declaration of this class objects.
   */
//  typedef char element_name_type;      // DO NOT change this size!
//  typedef char chemical_symbol_type;  // DO NOT change this size!
  typedef size_t atomic_number_type;
  typedef float  atomic_weight_value_type;
  typedef size_t group_number_type;
  typedef size_t period_number_type;
//  typedef ElectronConfiguration electron_config_type;

public:
  /**
   *  Default and initialize list constructors
   */
  Element() :
    electron_config_ ( ElectronConfiguration() ), // it will probably use the constexpr constructor and the default one is deleted
    element_name_ ("unknown"),
    chemical_symbol_ ("unknown"),
    atomic_number_ (0),
    atomic_weight_ (0.0),
    group_ (0),
    period_ (0) { };

  /**
   *  7.1.5/9
   *  " A constexpr specifier in an object declaration declares the object as const. 
   *    Such an object shall have literal type(has a trival destructor) and shall be 
   *    initialized. If it is initialized by a constructor call, that call shall be 
   *    a constant expression. "
   */
  constexpr Element( ElectronConfiguration       electron_config_obj, 
           char*                      element_name_value,
           char*                      chemical_symbol_value,
           atomic_number_type         atomic_number_value,
           atomic_weight_value_type   atomic_weight_value,
           group_number_type          group_value,
           period_number_type         period_value ):
    electron_config_ ( electron_config_obj ),
    element_name_    ( element_name_value ),
    chemical_symbol_ ( chemical_symbol_value ),
    atomic_number_   ( atomic_number_value ),
    atomic_weight_   ( atomic_weight_value ),
    group_           ( group_value ),
    period_          ( period_value )  {/* element_name_ = element_name_value; chemical_symbol_ = chemical_symbol_value; */};
//  ~Element(){};

public:
  /**
   *  Accessors
   *   ( Mutators are not allowed for an Element )
   */
  electron_config_type electron_config () const 
    { return this->electron_config_; }
  const char* element_name() const
    { return this->element_name_; }
  const char* chemical_symbol() const
    { return this->chemical_symbol_; }
  atomic_number_type atomic_number() const
    { return this->atomic_number_; }
  atomic_weight_value_type atomic_weight() const
    { return this->atomic_weight_; }
  group_number_type group() const
    { return this->group_; }
  period_number_type period() const
    { return this->period_; }

  /**
   *  Axiliary Accessors
   */
  size_t nelec()
    { return this->electron_config_.nelec(); }

private:
  ElectronConfiguration       electron_config_;
  /**
   *  About the data type of element name and chemical symbol
   *  (1) we cannot use std :: string since this will disable the use of constexpr of this class
   *  (2) we cannot use char*, instead we have to use const char*, since the standard has 
   *      deleted the functionality to convert const char*(which is the actual type of arguments ) to char*
   */
  const char*          element_name_;
  const char*       chemical_symbol_;
  atomic_number_type         atomic_number_;
  atomic_weight_value_type   atomic_weight_;
  group_number_type          group_;
  period_number_type         period_;

}; // end of struct Element

} // end of namespace chemistry

} // end of namespace iquads

#endif
