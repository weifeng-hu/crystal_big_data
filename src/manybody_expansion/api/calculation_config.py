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

class CalculationConfig:

  def __init__( self ):

    self.lattice_name = "";
    self.natom = 0;
    self.xyz_file_name = "";
    self.lattice_constant_file_name = "";
    self.a = 0;
    self.b = 0;
    self.c = 0;
    self.basis_set = "unknown";
    self.radius = 0.0;
    self.correlation = "unknown";
    self.order = 0;
    self.working_directory = "";
    self.notes = "";

