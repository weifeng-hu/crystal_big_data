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


def import_unit_cell( fg_config ):

  natom = fg_config.natom;

  xyz_file_name   = config.xyz_name;
  from geometry_file import read_xyz;
  coordinates = [];
  coordinates = read_xyz( xyz_file_nam );

  natom_imported = len( coordinates );

  if natom_imported != natom:
    print "warning: import number of atom ", natom_import, " not equal to preset natom", natom;

  const_file_name = config.const_name;
  from geometry_file import read_const;
  constants = [];
  constants = config.read_const( const_file_name );

  import copy;
  fg_config.coordinates = copy.deepcopy( coordinates );
  fg_config.constants   = copy.deepcopy( constants   );

  return 0;

