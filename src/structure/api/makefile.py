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



def write( uc_config ):

  makefile_name = uc_config.makefile_name;

  f_makefile = open( makefile_name, "wt" );
  f_makefile.write( "iquads_root\t= " + uc_config.iquads_root + "\n");
  f_makefile.write( "iquads_src\t= " + uc_config.iquads_src + "\n" );
  f_makefile.write( "iquads_bin\t= " + uc_config.iquads_bin + "\n" );
  f_makefile.write( "iquads_include\t= " + uc_config.iquads_include + "\n" );
  f_makefile.write( "CPP\t = " + uc_config.cpp + "\n" );
  f_makefile.write( "CPPOPT\t = " + uc_config.cppopt + "\n" );
  f_makefile.write( "CPPFLAGS\t = " + uc_config.cppflags + "\n" );
  f_makefile.write( "FC\t = " + uc_config.fc + "\n" );
  f_makefile.write( "CHEADS\t = " + uc_config.cheads + "\n" );
  f_makefile.write( "CPPSRCS\t = " + uc_config.cppsrcs + "\n" );
  f_makefile.write( "CPPOBJS\t = " + uc_config.cppobjs + "\n" );
  f_makefile.write( "LIBS\t = " + uc_config.libs + "\n" );
  f_makefile.write( "executable\t = " + uc_config.executable + "\n" );
  f_makefile.write( "\n" );
  f_makefile.write( "all: $(executable)\n" );
  f_makefile.write( "\n" );
  f_makefile.write( "$(executable): $(CPPOBJS)\n" );
  f_makefile.write( "\t$(CPP) -o $(executable) $(CPPFLAGS) $(CPPOPT) $(CPPOBJS) $(LIBS)\n" );
  f_makefile.write( "\n" );
  f_makefile.write( uc_config.cppobjs + ":\t" + uc_config.cppsrcs + "\n" );
  f_makefile.write( "\t$(CPP) -o " + uc_config.cppobjs + " -c $(CPPFLAGS) $(CPPOPT) " + uc_config.cppsrcs + "\n" );
  f_makefile.write( "\n" );
  f_makefile.write( "clean:\n" );
  f_makefile.write( "\trm " + uc_config.executable + " ./*.o " + "\n" );

  f_makefile.close();

  return 0;
