##  
#  @file
#  @author Weifeng Hu
#  
#  @section LICENSE
#  
#  Copyright (C) 2013, 2014, 2015  Weifeng Hu
#  
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#  
#  @section DESCRIPTION
#  
#  
## 


def read_xyz( xyz_file_name ):

  coordinates = [];
  
  f_xyz = open( xyz_file_name , "rt" );
  natom_txt = f_xyz.read();
  natom = int( natom_txt );

  for iatom in range( 0, natom ):
    line = f_xyz.readline();
    words = line.split();
    element = words[0];
    x = float( words[1] );
    y = float( words[2] );
    z = float( words[3] );
    new_coordinate = [ element, x, y, z ];
    coordinates.append( new_coordinate );

  f_xyz.close();

  return coordinates;


def read_const( const_file_name ):

  constants = [];

  f_const = open( const_file_name, "rt" );
  word_a = f_const.readline();
  word_b = f_const.readline();
  word_c = f_const.readline();
  word_alpha = f_const.readline();
  word_beta  = f_const.readline();
  word_gamma = f_const.readline();
  f_const.close();

  a = float( word_a );
  b = float( word_b );
  c = float( word_c );
  alpha = float( word_alpha );
  beta  = float( word_beta  );
  gamma = float( word_gamma );

  constants = [ a, b, c, alpha, beta, gamma ];

  return constants;
