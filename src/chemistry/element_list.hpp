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

#ifndef ELEMENT_LIST_HPP
#define ELEMENT_LIST_HPP

#include <chemistry/element.hpp>

namespace iquads {

  namespace chemistry {
  
    namespace element {

    /**
     *  Compile-time initialization of all element objects
     */
      constexpr Element H   = Element( Element :: ElectronConfiguration(1),                                                 (char*)("Hydrogen"     ) , (char*)("H"  ),   1, 1.0079, 1,  1 );
      /**
       *  We have to use (char*) cast because in ISO C++ now the conversion from constant string like "Hydrogen" to char* has been deprecated
       */
      constexpr Element He  = Element( Element :: ElectronConfiguration(2),                                                 (char*)("Hellium"      ) , (char*)("He" ),   2, 4.003,  18, 1 );
      constexpr Element Li  = Element( Element :: ElectronConfiguration(2,1),                                               (char*)("Lithium"      ) , (char*)("Li" ),   3, 6.941,  1,  2 );
      constexpr Element Be  = Element( Element :: ElectronConfiguration(2,2),                                               (char*)("Beryllium"    ) , (char*)("Be" ),   4, 9.012,  2,  2 );
      constexpr Element B   = Element( Element :: ElectronConfiguration(2,2,1),                                             (char*)("Boron"        ) , (char*)("B"  ),   5, 10.81,  13, 2 );
      constexpr Element C   = Element( Element :: ElectronConfiguration(2,2,2),                                             (char*)("Carbon"       ) , (char*)("C"  ),   6, 12.01,  14, 2 );
      constexpr Element N   = Element( Element :: ElectronConfiguration(2,2,3),                                             (char*)("Nitrogen"     ) , (char*)("N"  ),   7, 14.01,  15, 2 );
      constexpr Element O   = Element( Element :: ElectronConfiguration(2,2,4),                                             (char*)("Oxygen"       ) , (char*)("O"  ),   8, 16.00,  16, 2 );
      constexpr Element F   = Element( Element :: ElectronConfiguration(2,2,5),                                             (char*)("Fluro"        ) , (char*)("F"  ),   9, 19.00,  17, 2 );
      constexpr Element Ne  = Element( Element :: ElectronConfiguration(2,2,6),                                             (char*)("Neon"         ) , (char*)("Ne" ),  10, 20.18,  18, 2 );
      constexpr Element Na  = Element( Element :: ElectronConfiguration(2,2,6,1),                                           (char*)("Sodium"       ) , (char*)("Na" ),  11, 22.99,  1,  3 );
      constexpr Element Mg  = Element( Element :: ElectronConfiguration(2,2,6,2),                                           (char*)("Magnesium"    ) , (char*)("Mg" ),  12, 24.31,  2,  3 );
      constexpr Element Al  = Element( Element :: ElectronConfiguration(2,2,6,2,1),                                         (char*)("Aluminium"    ) , (char*)("Al" ),  13, 26.98,  13, 3 );
      constexpr Element Si  = Element( Element :: ElectronConfiguration(2,2,6,2,2),                                         (char*)("Silicon"      ) , (char*)("Si" ),  14, 28.09,  14, 3 );
      constexpr Element P   = Element( Element :: ElectronConfiguration(2,2,6,2,3),                                         (char*)("Phosphorus"   ) , (char*)("P"  ),  15, 30.97,  15, 3 );
      constexpr Element S   = Element( Element :: ElectronConfiguration(2,2,6,2,4),                                         (char*)("Sulfur"       ) , (char*)("S"  ),  16, 32.07,  16, 3 );
      constexpr Element Cl  = Element( Element :: ElectronConfiguration(2,2,6,2,5),                                         (char*)("Chlorine"     ) , (char*)("Cl" ),  17, 35.45,  17, 3 );
      constexpr Element Ar  = Element( Element :: ElectronConfiguration(2,2,6,2,6),                                         (char*)("Argon"        ) , (char*)("Ar" ),  18, 39.95,  18, 3 );
      constexpr Element K   = Element( Element :: ElectronConfiguration(2,2,6,2,6,0,1),                                     (char*)("Potassium"    ) , (char*)("K"  ),  19, 39.10,  1,  4 );
      constexpr Element Ca  = Element( Element :: ElectronConfiguration(2,2,6,2,6,0,2),                                     (char*)("Calcium"      ) , (char*)("Ca" ),  20, 40.08,  2,  4 );
      constexpr Element Sc  = Element( Element :: ElectronConfiguration(2,2,6,2,6,1,2),                                     (char*)("Scandium"     ) , (char*)("Sc" ),  21, 44.96,  3,  4 );
      constexpr Element Ti  = Element( Element :: ElectronConfiguration(2,2,6,2,6,2,2),                                     (char*)("Titanium"     ) , (char*)("Ti" ),  22, 47.87,  4,  4 );
      constexpr Element V   = Element( Element :: ElectronConfiguration(2,2,6,2,6,3,2),                                     (char*)("Vanadium"     ) , (char*)("V"  ),  23, 50.94,  5,  4 );
      constexpr Element Cr  = Element( Element :: ElectronConfiguration(2,2,6,2,6,5,1),                                     (char*)("Chromium"     ) , (char*)("Cr" ),  24, 52.00,  6,  4 );
      constexpr Element Mn  = Element( Element :: ElectronConfiguration(2,2,6,2,6,5,2),                                     (char*)("Manganese"    ) , (char*)("Mn" ),  25, 54.96,  7,  4 );
      constexpr Element Fe  = Element( Element :: ElectronConfiguration(2,2,6,2,6,6,2),                                     (char*)("Iron"         ) , (char*)("Fe" ),  26, 55.84,  8,  4 );
      constexpr Element Co  = Element( Element :: ElectronConfiguration(2,2,6,2,6,7,2),                                     (char*)("Cobalt"       ) , (char*)("Co" ),  27, 58.93,  9,  4 );
      constexpr Element Ni  = Element( Element :: ElectronConfiguration(2,2,6,2,6,8,2),                                     (char*)("Nickel"       ) , (char*)("Ni" ),  28, 58.69,  10, 4 );
      constexpr Element Cu  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,1),                                    (char*)("Copper"       ) , (char*)("Cu" ),  29, 63.55,  11, 4 );
      constexpr Element Zn  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2),                                    (char*)("Zinc"         ) , (char*)("Zn" ),  30, 65.41,  12, 4 );
      constexpr Element Ga  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,1),                                  (char*)("Gallium"      ) , (char*)("Ga" ),  31, 69.72,  13, 4 );
      constexpr Element Ge  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,2),                                  (char*)("Germanium"    ) , (char*)("Ge" ),  32, 72.61,  14, 4 );
      constexpr Element As  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,3),                                  (char*)("Arsenic"      ) , (char*)("As" ),  33, 74.92,  15, 4 );
      constexpr Element Se  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,4),                                  (char*)("Selenium"     ) , (char*)("Se" ),  34, 78.96,  16, 4 );
      constexpr Element Br  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,5),                                  (char*)("Bromine"      ) , (char*)("Br" ),  35, 79.90,  17, 4 );
      constexpr Element Kr  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6),                                  (char*)("Krypton"      ) , (char*)("Kr" ),  36, 83.80,  18, 4 );
      constexpr Element Rb  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,0,0,1),                            (char*)("Rubidium"     ) , (char*)("Rb" ),  37, 85.47,  1,  5 );
      constexpr Element Sr  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,0,0,2),                            (char*)("Strontium"    ) , (char*)("Sr" ),  38, 87.62,  2,  5 );
      constexpr Element Y   = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,1,0,2),                            (char*)("Yttrium"      ) , (char*)("Y"  ),  39, 88.91,  3,  5 );
      constexpr Element Zr  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,2,0,2),                            (char*)("Zirconium"    ) , (char*)("Zr" ),  40, 91.22,  4,  5 );
      constexpr Element Nb  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,3,0,2),                            (char*)("Niobium"      ) , (char*)("Nb" ),  41, 92.91,  5,  5 );
      constexpr Element Mo  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,5,0,1),                            (char*)("Molybdenum"   ) , (char*)("Mo" ),  42, 95.94,  6,  5 );
      constexpr Element Tc  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,5,0,2),                            (char*)("Technetium"   ) , (char*)("Tc" ),  43, 99.00,  7,  5 );
      constexpr Element Ru  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,6,0,2),                            (char*)("Ruthenium"    ) , (char*)("Ru" ),  44, 101.07, 8,  5 );
      constexpr Element Rh  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,7,0,2),                            (char*)("Rhodium"      ) , (char*)("Rh" ),  45, 102.91, 9,  5 );
      constexpr Element Pd  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,8,0,2),                            (char*)("Palladium"    ) , (char*)("Pd" ),  46, 106.42, 10, 5 );
      constexpr Element Ag  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,1),                           (char*)("Silver"       ) , (char*)("Ag" ),  47, 107.87, 11, 5 );
      constexpr Element Cd  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,2),                           (char*)("Cadmium"      ) , (char*)("Cd" ),  48, 112.41, 12, 5 );
      constexpr Element In  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,2,1),                         (char*)("Indium"       ) , (char*)("In" ),  49, 114.82, 13, 5 );
      constexpr Element Sn  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,2,2),                         (char*)("Tin"          ) , (char*)("Sn" ),  50, 118.71, 14, 5 );
      constexpr Element Sb  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,2,3),                         (char*)("Antimony"     ) , (char*)("Sb" ),  51, 121.76, 15, 5 );
      constexpr Element Te  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,2,4),                         (char*)("Tellurium"    ) , (char*)("Te" ),  52, 127.60, 16, 5 );
      constexpr Element I   = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,2,5),                         (char*)("Iodine"       ) , (char*)("I"  ),  53, 126.90, 17, 5 );
      constexpr Element Xe  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,2,6),                         (char*)("Xenon"        ) , (char*)("Xe" ),  54, 131.29, 18, 5 );
      constexpr Element Cs  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,2,6,0,0,0,1),                 (char*)("Caesium"      ) , (char*)("Cs" ),  55, 132.91, 1,  6 );
      constexpr Element Ba  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,2,6,0,0,0,2),                 (char*)("Barium"       ) , (char*)("Ba" ),  56, 137.33, 2,  6 );
      constexpr Element La  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,0,2,6,1,0,0,2),                 (char*)("Lanthanium"   ) , (char*)("La" ),  57, 138.91, 3,  6 );
      constexpr Element Ce  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,1,2,6,1,0,0,2),                 (char*)("Cerium"       ) , (char*)("Ce" ),  58, 140.12, 3,  6 );
      constexpr Element Pr  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,3,2,6,0,0,0,2),                 (char*)("Praseodymium" ) , (char*)("Pr" ),  59, 140.91, 3,  6 );
      constexpr Element Nd  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,4,2,6,0,0,0,2),                 (char*)("Neodymium"    ) , (char*)("Nd" ),  60, 144.24, 3,  6 );
      constexpr Element Pm  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,5,2,6,0,0,0,2),                 (char*)("Promethium"   ) , (char*)("Pm" ),  61, 145.00, 3,  6 );
      constexpr Element Sm  = Element( Element :: ElectronConfiguration(2,2,6,2,6,10,2,6,10,6,2,6,0,0,0,2),                 (char*)("Samarium"     ) , (char*)("Sm" ),  62, 150.36, 3,  6 );
      constexpr Element Eu  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,7,2,6,0,0,0,2),                 (char*)("Europium"     ) , (char*)("Eu" ),  63, 151.96, 3,  6 );
      constexpr Element Gd  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,7,2,6,1,0,0,2),                 (char*)("Gadolinium"   ) , (char*)("Gd" ),  64, 157.25, 3,  6 );
      constexpr Element Tb  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,9,2,6,0,0,0,2),                 (char*)("Terbium"      ) , (char*)("Tb" ),  65, 158.93, 3,  6 );
      constexpr Element Dy  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,10,2,6,0,0,0,2),                (char*)("Dysprosium"   ) , (char*)("Dy" ),  66, 162.50, 3,  6 );
      constexpr Element Ho  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,11,2,6,0,0,0,2),                (char*)("Holmium"      ) , (char*)("Ho" ),  67, 164.93, 3,  6 );
      constexpr Element Er  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,12,2,6,0,0,0,2),                (char*)("Erbium"       ) , (char*)("Er" ),  68, 167.26, 3,  6 );
      constexpr Element Tm  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,13,2,6,0,0,0,2),                (char*)("Thullium"     ) , (char*)("Tm" ),  69, 168.93, 3,  6 );
      constexpr Element Yb  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,0,0,0,2),                (char*)("Ytterbium"    ) , (char*)("Yb" ),  70, 173.04, 3,  6 );
      constexpr Element Lu  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,1,0,0,2),                (char*)("Lutetium"     ) , (char*)("Lu" ),  71, 174.97, 3,  6 );
      constexpr Element Hf  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,2,0,0,2),                (char*)("Halnium"      ) , (char*)("Hf" ),  72, 178.49, 4,  6 );
      constexpr Element Ta  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,3,0,0,2),                (char*)("Tantalum"     ) , (char*)("Ta" ),  73, 180.95, 5,  6 );
      constexpr Element W   = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,4,0,0,2),                (char*)("Tungstren"    ) , (char*)("W"  ),  74, 183.84, 6,  6 );
      constexpr Element Re  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,5,0,0,2),                (char*)("Rhenium"      ) , (char*)("Re" ),  75, 186.21, 7,  6 );
      constexpr Element Os  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,6,0,0,2),                (char*)("Osmium"       ) , (char*)("Os" ),  76, 190.23, 8,  6 );
      constexpr Element Ir  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,7,0,0,2),                (char*)("Iridium"      ) , (char*)("Ir" ),  77, 192.22, 9,  6 );
      constexpr Element Pt  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,8,0,0,2),                (char*)("Platinum"     ) , (char*)("Pt" ),  78, 195.08, 10, 6 );
      constexpr Element Au  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,1),               (char*)("Gold"         ) , (char*)("Au" ),  79, 196.97, 11, 6 );
      constexpr Element Hg  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2),               (char*)("Mercury"      ) , (char*)("Hg" ),  80, 200.59, 12, 6 );
      constexpr Element Tl  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2,1),             (char*)("Thallium"     ) , (char*)("Tl" ),  81, 204.38, 13, 6 );
      constexpr Element Pb  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2,2),             (char*)("Lead"         ) , (char*)("Pb" ),  82, 207.20, 14, 6 );
      constexpr Element Bi  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2,3),             (char*)("Bismuth"      ) , (char*)("Bi" ),  83, 208.98, 15, 6 );
      constexpr Element Po  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2,4),             (char*)("Polonium"     ) , (char*)("Po" ),  84, 209.00, 16, 6 );
      constexpr Element At  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2,5),             (char*)("Astatine"     ) , (char*)("At" ),  85, 210.00, 17, 6 );
      constexpr Element Rn  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2,6),             (char*)("Radon"        ) , (char*)("Rn" ),  86, 222.00, 18, 6 );
      constexpr Element Fr  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2,6,0,0,0,0,1),   (char*)("Francium"     ) , (char*)("Fr" ),  87, 223.00, 1,  7 );
      constexpr Element Ra  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2,6,0,0,0,0,2),   (char*)("Radium"       ) , (char*)("Ra" ),  88, 226.00, 2,  7 );
      constexpr Element Ac  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2,6,1,0,0,0,2),   (char*)("Actinium"     ) , (char*)("Ac" ),  89, 227.00, 3,  7 );
      constexpr Element Th  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,0,0,2,6,2,0,0,0,2),   (char*)("Thorium"      ) , (char*)("Th" ),  90, 232.04, 3,  7 );
      constexpr Element Pa  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,2,0,2,6,1,0,0,0,2),   (char*)("Protactinium" ) , (char*)("Pa" ),  91, 231.04, 3,  7 );
      constexpr Element U   = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,3,0,2,6,1,0,0,0,2),   (char*)("Uranium"      ) , (char*)("U"  ),  92, 238.03, 3,  7 );
      constexpr Element Np  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,4,0,2,6,1,0,0,0,2),   (char*)("Neptunium"    ) , (char*)("Np" ),  93, 237.00, 3,  7 );
      constexpr Element Pu  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,6,0,2,6,0,0,0,0,2),   (char*)("Plutonium"    ) , (char*)("Pu" ),  94, 244.00, 3,  7 );
      constexpr Element Am  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,7,0,2,6,0,0,0,0,2),   (char*)("Americium"    ) , (char*)("Am" ),  95, 243.00, 3,  7 );
      constexpr Element Cm  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,7,0,2,6,1,0,0,0,2),   (char*)("Curium"       ) , (char*)("Cm" ),  96, 247.00, 3,  7 );
      constexpr Element Bk  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,9,0,2,6,0,0,0,0,2),   (char*)("Berkelium"    ) , (char*)("Bk" ),  97, 247.00, 3,  7 );
      constexpr Element Cf  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,10,0,2,6,0,0,0,0,2),  (char*)("Californium"  ) , (char*)("Cf" ),  98, 251.00, 3,  7 );
      constexpr Element Es  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,11,0,2,6,0,0,0,0,2),  (char*)("Einsteinium"  ) , (char*)("Es" ),  99, 252.00, 3,  7 );
      constexpr Element Fm  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,12,0,2,6,0,0,0,0,2),  (char*)("Fermium"      ) , (char*)("Fm" ), 100, 257.00, 3,  7 );
      constexpr Element Md  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,13,0,2,6,0,0,0,0,2),  (char*)("Mendelevium"  ) , (char*)("Md" ), 101, 258.00, 3,  7 );
      constexpr Element No  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,0,0,0,0,2),  (char*)("Nobelium"     ) , (char*)("No" ), 102, 259.00, 3,  7 );
      constexpr Element Lr  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,1,0,0,0,2),  (char*)("Lawrencium"   ) , (char*)("Lr" ), 103, 262.00, 3,  7 );
      constexpr Element Rf  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,2,0,0,0,2),  (char*)("Rutherfordium") , (char*)("Rf" ), 104, 263.00, 4,  7 );
      constexpr Element Db  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,3,0,0,0,2),  (char*)("Dubnium"      ) , (char*)("Db" ), 105, 262.00, 5,  7 );
      constexpr Element Sg  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,4,0,0,0,2),  (char*)("Seaborgium"   ) , (char*)("Sg" ), 106, 266.00, 6,  7 );
      constexpr Element Bh  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,5,0,0,0,2),  (char*)("Bohrium"      ) , (char*)("Bh" ), 107, 264.00, 7,  7 );
      constexpr Element Hs  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,6,0,0,0,2),  (char*)("Hassium"      ) , (char*)("Hs" ), 108, 269.00, 8,  7 );
      constexpr Element Mt  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,7,0,0,0,2),  (char*)("Meitnerium"   ) , (char*)("H"  ), 109, 268.00, 9,  7 );
      constexpr Element Ds  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,8,0,0,0,2),  (char*)("Darmstadtium" ) , (char*)("Ds" ), 110, 272.00, 10, 7 );
      constexpr Element Rg  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,9,0,0,0,2),  (char*)("Roentgenium"  ) , (char*)("Rg" ), 111, 272.00, 11, 7 );
      constexpr Element Cn  = Element( Element :: ElectronConfiguration(2,6,2,2,6,10,2,6,10,14,2,6,10,14,0,2,6,10,0,0,0,2), (char*)("Copernicium"  ) , (char*)("Cn" ), 112, 277.00, 12, 7 );
    
    } // end of namespace element
  
  } // end of namespace chemistry

} // end of namespace iquads

#endif
