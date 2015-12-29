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


class UnitCellConfig:

  def __init__( self ):

    import lattice_constant;
    import nodes_config;

    self.name             = "unit cell config";
    self.lattice_constant = lattice_constant.LatticeConstant();
    self.nodes            = nodes_config.NodesConfig();


  def lattice_constant( self ):
    return self.lattice_constant;

  def nodes( self ):
    return self.nodes;

  def natom( self ):
    return self.nodes.natom;

