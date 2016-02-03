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
#include <fstream>
#include <string>
#include <geometrical_space/rotator.hpp>
#include <structure/atom_list.hpp>
#include <structure/molecule.hpp>
#include <structure/molecule_isolator.hpp>
#include <structure/euclidean_distance_matrix.hpp>
#include <structure/unit_cell_canonicalizer.hpp>

int main( int argc, char* argv[] ) {

  typedef std :: array< double, 3 > threed_vector_type;
  typedef iquads :: structure :: AtomList atom_list_type;
  typedef iquads :: structure :: MolecularUnitCell unit_cell_type;

  std :: vector< iquads :: structure :: Molecule > node_list;
  node_list.resize(0);

  iquads :: structure :: AtomList atom_list_0 = {
              iquads :: structure :: Atom( std :: string("O"), 7.09340, 0.92990, -0.59850, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 6.54740, 0.20310, -0.72450, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 5.64120, 1.22240, 1.07300, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 8.99530, 2.73870, -1.00620, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 10.15490, 1.43610, 0.41770, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 7.29530, 2.88320, 0.74970, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 8.41970, 3.39390, 0.08800, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 8.97780, 4.60780, 0.45630, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 9.73360, 4.94520, -0.01000, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 8.43030, 5.32800, 1.50650, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 8.81610, 6.15790, 1.76200, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 7.32070, 4.84250, 2.18660, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 6.94960, 5.33440, 2.90940, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 6.75810, 3.63360, 1.80170, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 5.99300, 3.30860, 2.26110, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 6.60940, 1.60170, 0.41880, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 9.85210, 1.71650, -0.70950, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 10.33780, 1.04860, -1.95000, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 10.94400, 0.31640, -1.71150, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 10.81540, 1.69950, -2.50550, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 9.57360, 0.69050, -2.44950, std :: string( "angstrom" ) ),
          };
  iquads :: structure :: Molecule molecule_0( atom_list_0, 0); 
  node_list.push_back( molecule_0 );

  iquads :: structure :: AtomList atom_list_1 = {
              iquads :: structure :: Atom( std :: string("O"), 3.61100, 4.20570, 6.20640, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 4.15690, 3.47900, 6.33240, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 5.06310, 4.49830, 4.53480, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 1.70910, 6.01450, 6.61410, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 0.54950, 4.71190, 5.19020, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 3.40900, 6.15910, 4.85820, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 2.28470, 6.66980, 5.51990, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 1.72650, 7.88370, 5.15160, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 0.97070, 8.22110, 5.61790, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 2.27400, 8.60380, 4.10130, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 1.88830, 9.43370, 3.84580, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 3.38370, 8.11830, 3.42120, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 3.75480, 8.61020, 2.69850, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 3.94620, 6.90940, 3.80610, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 4.71140, 6.58450, 3.34670, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 4.09490, 4.87750, 5.18900, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 0.85230, 4.99230, 6.31730, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 0.36650, 4.32440, 7.55790, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), -0.23960, 3.59220, 7.31930, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), -0.11100, 4.97540, 8.11340, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 1.13070, 3.96630, 8.05730, std :: string( "angstrom" ) ),
          };
  iquads :: structure :: Molecule molecule_1( atom_list_1, 0); 
  node_list.push_back( molecule_1 );

  iquads :: structure :: AtomList atom_list_2 = {
              iquads :: structure :: Atom( std :: string("O"), 3.03770, 5.62180, 11.81420, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 3.58360, 6.34860, 11.94020, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 4.48980, 5.32930, 10.14260, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 1.13580, 3.81300, 12.22190, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), -0.02380, 5.11560, 10.79800, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 2.83570, 3.66850, 10.46600, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 1.71140, 3.15780, 11.12770, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 1.15320, 1.94390, 10.75940, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 0.39740, 1.60650, 11.22570, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 1.70080, 1.22370, 9.70920, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 1.31500, 0.39380, 9.45370, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 2.81040, 1.70920, 9.02900, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 3.18150, 1.21730, 8.30630, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 3.37300, 2.91810, 9.41400, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 4.13810, 3.24310, 8.95460, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 3.52160, 4.95000, 10.79690, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 0.27900, 4.83520, 11.92510, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), -0.20680, 5.50310, 13.16570, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), -0.81290, 6.23530, 12.92720, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), -0.68430, 4.85220, 13.72120, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 0.55740, 5.86120, 13.66510, std :: string( "angstrom" ) ),
          };
  iquads :: structure :: Molecule molecule_2( atom_list_2, 0); 
  node_list.push_back( molecule_2 );

  iquads :: structure :: AtomList atom_list_3 = {
              iquads :: structure :: Atom( std :: string("O"), 6.52010, 2.34600, 5.00920, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 5.97410, 3.07270, 4.88330, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 5.06790, 2.05340, 6.68080, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 8.42200, 0.53720, 4.60160, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("O"), 9.58160, 1.83980, 6.02550, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 6.72200, 0.39260, 6.35750, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 7.84640, -0.11810, 5.69580, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 8.40450, -1.33200, 6.06410, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 9.16030, -1.66940, 5.59770, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 7.85700, -2.05210, 7.11430, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 8.24270, -2.88200, 7.36980, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 6.74730, -1.56660, 7.79440, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 6.37630, -2.05850, 8.51720, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 6.18480, -0.35770, 7.40950, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 5.41970, -0.03280, 7.86890, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 6.03610, 1.67420, 6.02660, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 9.27870, 1.55940, 4.89830, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("C"), 9.76450, 2.22730, 3.65780, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 10.37070, 2.95950, 3.89630, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 10.24210, 1.57630, 3.10220, std :: string( "angstrom" ) ),
              iquads :: structure :: Atom( std :: string("H"), 9.00030, 2.58540, 3.15830, std :: string( "angstrom" ) ),
           };
  iquads :: structure :: Molecule molecule_3( atom_list_3, 0 ); 
  node_list.push_back( molecule_3 );

  iquads :: structure :: LatticeParameter lattice_parameter_ref( 11.27762, 6.55171, 11.27412, 95.8371, 90.0, 90.0 );

  iquads :: structure :: MolecularUnitCell unit_cell_reference( node_list, lattice_parameter_ref );

  iquads :: structure :: UnitCellCanonicalizer canonicalizer( unit_cell_reference, 1.5e0 );

  iquads :: structure :: AtomList new_atom_list = {
              iquads :: structure :: Atom ( std :: string("H"),  2.9044 , 1.5499 , 11.1926,  std :: string( "angstrom" ) ), 
              iquads :: structure :: Atom ( std :: string("H"),  7.0958 , 4.9624 , -0.0045,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  3.5555 , 1.7062 , 5.5466 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  6.4447 , 4.8061 , 5.6415 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  3.2299 , 0.2293 , 1.7827 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  6.7702 , 6.283  , 9.4053 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  2.5789 , 3.0268 , 7.4288 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  7.4213 , 3.4855 , 3.7593 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  1.2278 , 1.1151 , 3.0079 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  8.7724 , 5.3972 , 8.1802 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  0.5767 , 2.1411 , 8.6539 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  9.4235 , 4.3712 , 2.5341 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  0.2256 , 3.2763 , 2.3108 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  9.7746 , 3.236  , 8.8773 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  -0.4254, 6.4921 , 7.9568 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  10.4256, 0.0202 , 3.2313 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  4.0198 , 6.3583 , 9.598  ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  5.9804 , 0.154  , 1.5901 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  4.6708 , 3.4101 , 3.952  ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  5.3294 , 3.1022 , 7.2361 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  2.6077 , 5.7122 , 8.6808 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  7.3925 , 0.8001 , 2.5073 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  3.2588 , 4.0563 , 3.0348 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  6.7414 , 2.456  , 8.1533 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  4.104  , 4.7786 , 8.7666 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  5.8962 , 1.7337 , 2.4215 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  4.7551 , 4.9898 , 3.1206 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  5.2451 , 1.5225 , 8.0675 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  -0.4418, 6.4579 , 10.5519,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  10.442 , 0.0544 , 0.6362 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  0.2092 , 3.3106 , 4.9059 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("H"),  9.791  , 3.2017 , 6.2822 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  1.6486 , 3.6543 , 0.7496 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  8.3516 , 2.858  , 10.4385,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  0.9975 , 6.1142 , 6.3956 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  9.0027 , 0.3982 , 4.7925 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  2.7857 , 3.1423 , 0.0854 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  7.2145 , 3.37   , 11.1026,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  2.1346 , 0.1138 , 5.7314 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  7.8655 , 6.3985 , 5.4566 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  3.3405 , 1.9161 , 0.45   ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  6.6597 , 4.5962 , 10.7381,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  2.6894 , 1.3401 , 6.096  ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  7.3108 , 5.1722 , 5.0921 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  2.7879 , 1.1854 , 1.5056 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  7.2123 , 5.327  , 9.6825 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  2.1369 , 2.0708 , 7.1516 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  7.8633 , 4.4415 , 4.0365 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  1.6677 , 1.6753 , 2.1859 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  8.3325 , 4.837  , 9.0022 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  1.0167 , 1.5809 , 7.8319 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  8.9835 , 4.9314 , 3.3561 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  1.1062 , 2.8907 , 1.8024 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  8.894  , 3.6216 , 9.3857 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  0.4551 , 0.3655 , 7.4484 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  9.545  , 6.1468 , 3.7397 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  0.9552 , 4.9309 , 0.4186 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  9.045  , 1.5814 , 10.7695,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  0.3041 , 4.8376 , 6.0646 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  9.6961 , 1.6748 , 5.1234 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  2.9709 , 4.7934 , 10.5813,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  7.0293 , 1.7189 , 0.6068 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  3.6219 , 4.9751 , 4.9352 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  6.3783 , 1.5373 , 6.2528 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  3.4536 , 5.4617 , 9.3295 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  6.5466 , 1.0506 , 1.8585 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  4.1047 , 4.3068 , 3.6835 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("C"),  5.8955 , 2.2055 , 7.5046 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  0.1336 , 5.6196 , 10.6966,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  9.8666 , 0.8927 , 0.4915 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  0.7847 , 4.1488 , 5.0506 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  9.2155 , 2.3635 , 6.1375 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  -0.0322, 5.3013 , 1.079  ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  10.0324, 1.211  , 10.1091,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  -0.6833, 4.4672 , 6.725  ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  10.6835, 2.0451 , 4.4631 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  2.0614 , 3.8018 , 10.2931,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  7.9387 , 2.7105 , 0.895  ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  2.7125 , 5.9666 , 4.647  ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  7.2877 , 0.5457 , 6.541  ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  4.6165 , 5.0442 , 0.4264 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  5.3837 , 1.4681 , 10.7617,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  3.9655 , 4.7242 , 6.0724 ,  std :: string( "angstrom" ) ),  
              iquads :: structure :: Atom ( std :: string("O"),  6.0347 , 1.7881 , 5.1157 ,  std :: string( "angstrom" ) ),  
  };

  threed_vector_type a_vec = { 11.3023e0, 0.0e0, -0.1039486e0 };
  threed_vector_type b_vec = { 0.0e0, 6.5123078e0, 0.0e0 };
  threed_vector_type c_vec = { -1.3021083e0, 0.0e0, 11.2920255e0 };
  std :: array< threed_vector_type, 3 > lattice_vectors = { a_vec, b_vec, c_vec };

  unit_cell_type new_unit_cell = canonicalizer.canonicalize( new_atom_list, lattice_vectors );

  std :: ofstream ofs_coord( "aspirin_form_1_canonicalized.coord", std :: ios :: out );
  ofs_coord << new_unit_cell.size() << std :: endl;
  ofs_coord << new_unit_cell[0].size() << std :: endl;
  for( size_t inode = 0; inode < new_unit_cell.size(); inode++ ) {
    ofs_coord << iquads :: structure :: geometry_unit :: return_unit_name( new_unit_cell[0].geometry_unit() ) << std :: endl;
    ofs_coord << new_unit_cell[inode]; 
  }
  ofs_coord.close();

  using iquads :: geometrical_space :: threed_space :: pi;
  std :: ofstream ofs_const( "aspirin_form_1_canonicalized.const", std :: ios :: out );
  ofs_const << "a\t"     << std :: setw(12) << std :: setprecision(8) << new_unit_cell.lattice_parameter().a()     << std :: endl;   
  ofs_const << "b\t"     << std :: setw(12) << std :: setprecision(8) << new_unit_cell.lattice_parameter().b()     << std :: endl;   
  ofs_const << "c\t"     << std :: setw(12) << std :: setprecision(8) << new_unit_cell.lattice_parameter().c()     << std :: endl;   
  ofs_const << "alpha\t" << std :: setw(12) << std :: setprecision(8) << 180.0e0 * new_unit_cell.lattice_parameter().alpha()/pi << std :: endl;   
  ofs_const << "beta\t"  << std :: setw(12) << std :: setprecision(8) << 180.0e0 * new_unit_cell.lattice_parameter().beta()/pi  << std :: endl;   
  ofs_const << "gamma\t" << std :: setw(12) << std :: setprecision(8) << 180.0e0 * new_unit_cell.lattice_parameter().gamma()/pi << std :: endl;   
  ofs_const.close();

  return 0;

} // end of main()
