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


class FragmentGeneratorConfig:

  def __init__( self ):

    self.name = "fragment generator config";

    from structure.api.unit_cell_config import UnitCellConfig;
    self.unit_cell_info = UnitCellConfig();

    self.xyz_file_name = "";
    self.lattice_constants_file_name = "";
    self.order = 0;
    self.correlation = "hf";
    self.program = "molpro";
    self.basis_set = "unknown_basis";
    self.lattice_name = "";
    self.mode = "dryrun";
    self.project_name = "try";
    self.radius = 1.0;
    self.input_name = "";
    self.scratch_name = "";
    self.output_name = "";
    self.driver_name = "";
    self.makefile_name = "";
    self.a = 0;
    self.b = 0;
    self.c = 0;
    self.natom = 0;

    self.working_directory = "";

    self.iquads_root = "$(IQUADS_ROOT)";
    self.iquads_src  = "$(iquads_root)/src/";
    self.iquads_bin  = "$(iquads_root)/bin/";
    self.iquads_include = "$(iquads_root)/src/";
    self.boost_root  = "$(BOOST_ROOT)"
    self.boost_lib   = "$(BOOST_ROOT)/stage/lib/";
    self.boost_include = "$(BOOST_ROOT)";
    self.pwd = "";
    self.cc  = "gcc";
    self.copt = "-O3 "
    self.cpp = "g++";
    self.cppopt = "-O3 -std=c++11 -fopenmp"
    self.cppflags = "-I$(iquads_include) -I/usr/include -I$(boost_include)"
    self.fc  = "gfortran";
    self.cheads = "";
    self.cppsrcs = "";
    self.cppobjs = "$(CPPSRCS:.cpp=.o)";
    self.libs = "";
    import platform
    arch = platform.machine();
    if arch == "x86" or arch == "x86_64":
      self.libs = "$(iquads_src)/manybody_expansion/libiquads_manybody_expansion.a $(iquads_src)/electron_correlation/libiquads_electron_correlation.a $(iquads_src)/interface_to_third_party/libiquads_third_party.a $(iquads_src)/matrix/libiquads_matrix.a $(iquads_src)/blas/libiquads_blas_interface.a -L/$(boost_lib) -lboost_filesystem -lboost_date_time -lboost_system -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lrt -lpthread -lgfortran";
    else:
      self.libs = "$(iquads_src)/manybody_expansion/libiquads_manybody_expansion.a $(iquads_src)/electron_correlation/libiquads_electron_correlation.a $(iquads_src)/interface_to_third_party/libiquads_third_party.a $(iquads_src)/matrix/libiquads_matrix.a $(iquads_src)/blas/libiquads_blas_interface.a -L/$(boost_lib) -lboost_filesystem -lboost_date_time -lboost_system -llapack -lblas -lrt -lpthread -lgfortran";
    self.executable = "";



  def natom( self ):
    import copy;
    natom = copy.deepcopy( self.unit_cell_info.natom() );
    return natom;

  def lattice_constant( self ):
    return self.unit_cell_info.lattice_constant;

  def nodes( self ):
    return self.unit_cell_info.nodes;

  def nnode_per_unit_cell( self ):
    return self.unit_cell_info.nodes().nnode;

  def natom_per_node( self ):
    return self.unit_cell_info.nodes().natom_per_node;

  def order_string( self ):
    if self.order == 0:
      return "null";
    elif self.order == 1:
      return "m";
    elif self.order == 2:
      return "md";
    elif self.order == 3:
      return "mdt";
    elif self.order == 4:
      return "mdttr";
    else:
      print "unable to process order ", self.order;
      quit();

  def print_data( self ):

    return 0;
