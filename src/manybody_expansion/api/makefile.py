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



def write( fg_config ):

  makefile_name = fg_config.makefile_name;

  import os;
  current_directory = os.getcwd();

  f_makefile = open( makefile_name, "wt" );
  f_makefile.write( "iquads_root\t= " + fg_config.iquads_root + "\n");
  f_makefile.write( "iquads_src\t= " + fg_config.iquads_src + "\n" );
  f_makefile.write( "iquads_bin\t= " + fg_config.iquads_bin + "\n" );
  f_makefile.write( "boost_include\t= " + fg_config.boost_include + "\n" );
  f_makefile.write( "boost_lib\t= " + fg_config.boost_lib + "\n" );
  f_makefile.write( "CC\t = " + fg_config.cc + "\n" );
  f_makefile.write( "COPT\t = " + fg_config.copt + "\n" );
  f_makefile.write( "CPP\t = " + fg_config.cpp + "\n" );
  f_makefile.write( "CPPOPT\t = " + fg_config.cppopt + "\n" );
  f_makefile.write( "CPPFLAGS\t = " + fg_config.cppflags + "\n" );
  f_makefile.write( "FC\t = " + fg_config.fc + "\n" );
  f_makefile.write( "CHEADS\t = " + fg_config.cheads + "\n" );
  f_makefile.write( "CPPSRCS\t = " + fg_config.cppsrcs + "\n" );
  f_makefile.write( "CPPOBJS\t = " + fg_config.cppobjs + "\n" );
  f_makefile.write( "LIBS\t = " + fg_config.libs + "\n" );
  f_makefile.write( "executable\t = " + fg_config.executable + "\n" );
  f_makefile.write( "\n" );
  f_makefile.write( "all: $(executable)\n" );
  f_makefile.write( "\n" );
  f_makefile.write( "$(executable): $(CPPOBJS)\n" );
  f_makefile.write( "\t$(CPP) -o $(executable) $(CPPFLAGS) $(CPPOPT) $(CPPOBJS) $(LIBS)\n" );
  f_makefile.write( "\n" );
  f_makefile.write( fg_config.cppobjs + ":\t" + fg_config.cppsrcs + "\n" );
  f_makefile.write( "\t$(CPP) -o " + fg_config.cppobjs + " -c $(CPPFLAGS) $(CPPOPT) " + fg_config.cppsrcs + "\n" );
  f_makefile.write( "\n" );
  f_makefile.write( "clean:\n" );
  f_makefile.write( "\trm " + fg_config.executable + " ./*.o " + "\n" );

  f_makefile.close();

  return 0;
