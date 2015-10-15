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

#ifndef PERIODIC_TABLE_HPP
#define PERIODIC_TABLE_HPP

#include <iostream>
#include <array>
#include <string>
#include <chemistry/element_list.hpp>

namespace iquads {

namespace chemistry {

using chemistry :: Element;
using std :: array;
using std :: string;
using namespace chemistry :: element;

constexpr size_t N_ELEMENT = 112;

class PeriodicTable {
public:
  constexpr PeriodicTable() :
    element_list_ ( 
      array< Element, N_ELEMENT > 
      {
      /*  1   2    3                                                         (3)  4   5   6   7   8   9   10  11  12    13  14  15  16  17  18  */
    /*1*/ H,                                                                                                                                He,
    /*2*/ Li, Be,                                                                                                       B,  C,  N,  O,  F,  Ne,
    /*3*/ Na, Mg,                                                                                                       Al, Si, P,  S,  Cl, Ar,
    /* */                                                                    // <------------ d-block ----------->//
    /*4*/ K,  Ca,                                                             Sc, Ti, V,  Cr, Mn, Fe, Co, Ni, Cu, Zn,   Ga, Ge, As, Se, Br, Kr,
    /*5*/ Rb, Sr,                                                             Y,  Zr, Nb, Mo, Tc, Ru, Rh, Pd, Ag, Cd,   In, Sn, Sb, Te, I,  Xe,
    /* */          // <------------------- f-block --------------------> //
    /*6*/ Cs, Ba,   La, Ce, Pr, Nd, Pm, Sm, Eu, Gd, Tb, Dy, Ho, Er, Tm, Yb,   Lu, Hf, Ta, W,  Re, Os, Ir, Pt, Au, Hg,   Tl, Pb, Bi, Po, At, Rn,
    /*7*/ Fr, Ra,   Ac, Th, Pa, U,  Np, Pu, Am, Cm, Bk, Cf, Es, Fm, Md, No,   Lr, Rf, Db, Sg, Bh, Hs, Mt, Ds, Rg, Cn
      }
    )
    { }

public:
  Element get_element_by_symbol( string symbol ) {
    for( size_t ielement = 0; ielement < N_ELEMENT; ielement++ ) {
      Element element_i = this->element_list_[ielement];
      if( symbol == element_i.chemical_symbol() ) {
        return element_i;
      }
    }
    std :: cout << "element " << symbol << "not found" << std :: endl;
    abort();
  }

private:
  array< Element, N_ELEMENT > element_list_;

}; // end of class PeriodicTable

} // end of namespace chemistry

} // end of namespace iquads

#endif
