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

#include <file_system/filepath.hpp>

int main( int argc, char* argv[] ) {

  iquads :: file_system :: Directory dir("/usr/bin/");
  iquads :: file_system :: Directory dir2( "./result/sub/sub/sub" ); 
  dir2.create();
  iquads :: file_system :: Filepath filepath( iquads :: file_system :: Directory( "./" ), iquads :: file_system :: Filename( "main", "cpp" ) );
  std :: cout << filepath ;
  std :: cout << filepath.exists() << std :: endl; ;
//  filepath.rename_if_exists();
//  std :: cout << filepath ;
  std :: cout <<  ( dir == dir2 ) << std :: endl;

  filepath.copy_to( dir2 );

};
