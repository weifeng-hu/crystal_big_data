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

class UnitCellCanonicalizeConfig:

   def __init__( self ):

     import unit_cell_config;
     import unknown_unit_cell_config;

     self.name              = "unit cell canonicalize config";
     self.unknown_unit_cell = unknown_unit_cell_config.UnknownUnitCellConfig();
     self.reference_unit_cell = unit_cell_config.UnitCellConfig();
     self.input_file_name   = "";
     self.reference_lattice_constants_file_name = "";
     self.reference_xyz_file_name               = "";
     self.target_lattice_constants_file_name    = "";
     self.target_xyz_file_name                  = "";
     self.target_gjf_file_name                  = "";
     self.lattice_name      = "";
     self.bond_length_limit = 0.0e0;

     self.project_name = "";
     self.driver_name = "";
     self.makefile_name = "";

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
     self.cppopt = "-O3 -std=c++11 -fopenmp";
     self.cppflags = "-I$(iquads_include) -I/usr/include -I$(boost_include)"
     self.fc  = "gfortran";
     self.cheads = "";
     self.cppsrcs = "";
     self.cppobjs = "$(CPPSRCS:.cpp=.o)";
     self.libs = "";
     import platform
     arch = platform.machine();
     if arch == "x86" or arch == "x86_64":
       self.libs = "$(iquads_src)/matrix/libiquads_matrix.a $(iquads_src)/blas/libiquads_blas_interface.a -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lrt -lpthread -lgfortran";
     else:
       self.libs = "$(iquads_src)/matrix/libiquads_matrix.a $(iquads_src)/blas/libiquads_blas_interface.a -llapack -lblas -lrt -lpthread -lgfortran";
     self.executable = "";
 
 
