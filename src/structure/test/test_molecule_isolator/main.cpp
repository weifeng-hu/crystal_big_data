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

#include <structure/atom_list.hpp>
#include <structure/molecule.hpp>
#include <structure/molecule_isolator.hpp>

int main( int argc, char* argv[] ) {

   iquads :: structure :: AtomList new_atom_list;
   new_atom_list.resize(0);

   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    7.09340,    0.92990,   -0.59850, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    6.54740,    0.20310,   -0.72450, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    5.64120,    1.22240,    1.07300, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    8.99530,    2.73870,   -1.00620, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,   10.15490,    1.43610,    0.41770, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    7.29530,    2.88320,    0.74970, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    8.41970,    3.39390,    0.08800, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    8.97780,    4.60780,    0.45630, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    9.73360,    4.94520,   -0.01000, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    8.43030,    5.32800,    1.50650, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    8.81610,    6.15790,    1.76200, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    7.32070,    4.84250,    2.18660, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    6.94960,    5.33440,    2.90940, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    6.75810,    3.63360,    1.80170, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    5.99300,    3.30860,    2.26110, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    6.60940,    1.60170,    0.41880, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    9.85210,    1.71650,   -0.70950, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,   10.33780,    1.04860,   -1.95000, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,   10.94400,    0.31640,   -1.71150, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,   10.81540,    1.69950,   -2.50550, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    9.57360,    0.69050,   -2.44950, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    3.61100,    4.20570,    6.20640, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    4.15690,    3.47900,    6.33240, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    5.06310,    4.49830,    4.53480, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    1.70910,    6.01450,    6.61410, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    0.54950,    4.71190,    5.19020, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    3.40900,    6.15910,    4.85820, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    2.28470,    6.66980,    5.51990, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    1.72650,    7.88370,    5.15160, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    0.97070,    8.22110,    5.61790, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    2.27400,    8.60380,    4.10130, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    1.88830,    9.43370,    3.84580, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    3.38370,    8.11830,    3.42120, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    3.75480,    8.61020,    2.69850, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    3.94620,    6.90940,    3.80610, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    4.71140,    6.58450,    3.34670, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    4.09490,    4.87750,    5.18900, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    0.85230,    4.99230,    6.31730, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    0.36650,    4.32440,    7.55790, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,   -0.23960,    3.59220,    7.31930, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,   -0.11100,    4.97540,    8.11340, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    1.13070,    3.96630,    8.05730, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    3.03770,    5.62180,   11.81420, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    3.58360,    6.34860,   11.94020, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    4.48980,    5.32930,   10.14260, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    1.13580,    3.81300,   12.22190, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,   -0.02380,    5.11560,   10.79800, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    2.83570,    3.66850,   10.46600, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    1.71140,    3.15780,   11.12770, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    1.15320,    1.94390,   10.75940, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    0.39740,    1.60650,   11.22570, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    1.70080,    1.22370,    9.70920, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    1.31500,    0.39380,    9.45370, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    2.81040,    1.70920,    9.02900, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    3.18150,    1.21730,    8.30630, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    3.37300,    2.91810,    9.41400, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    4.13810,    3.24310,    8.95460, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    3.52160,    4.95000,   10.79690, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    0.27900,    4.83520,   11.92510, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,   -0.20680,    5.50310,   13.16570, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,   -0.81290,    6.23530,   12.92720, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,   -0.68430,    4.85220,   13.72120, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    0.55740,    5.86120,   13.66510, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    6.52010,    2.34600,    5.00920, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    5.97410,    3.07270,    4.88330, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    5.06790,    2.05340,    6.68080, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    8.42200,    0.53720,    4.60160, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "O" ,    9.58160,    1.83980,    6.02550, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    6.72200,    0.39260,    6.35750, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    7.84640,   -0.11810,    5.69580, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    8.40450,   -1.33200,    6.06410, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    9.16030,   -1.66940,    5.59770, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    7.85700,   -2.05210,    7.11430, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    8.24270,   -2.88200,    7.36980, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    6.74730,   -1.56660,    7.79440, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    6.37630,   -2.05850,    8.51720, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    6.18480,   -0.35770,    7.40950, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    5.41970,   -0.03280,    7.86890, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    6.03610,    1.67420,    6.02660, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    9.27870,    1.55940,    4.89830, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "C" ,    9.76450,    2.22730,    3.65780, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,   10.37070,    2.95950,    3.89630, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,   10.24210,    1.57630,    3.10220, "angstrom" ) ); 
   new_atom_list.push_back( iquads :: structure :: Atom ( "H" ,    9.00030,    2.58540,    3.15830, "angstrom" ) ); 

   iquads :: structure :: MoleculeIsolator molecule_isolator( 1.7e0 );  

   std :: vector< iquads :: structure :: Molecule > molecule_list 
     = molecule_isolator.split( new_atom_list );

} // end of main()
