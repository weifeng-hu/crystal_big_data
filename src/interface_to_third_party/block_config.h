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
 */

namespace iquads { 

namespace interface_to_third_party { 

class Block_Config
{
public:
 struct schedule{
   int iter_index;
   int M;
   double david_tol;
   double noice;
 }; // end of structure schedule

public:
  Input( ithaca::interfaces::qcdmrg::cmd_options cmd_opt ) : ithaca::dmrg::Input( cmd_opt ) 
  ~Input();


// Essential parameters for QCDMRG Input files
public:
  bool defaulthf;
  bool bigdavid;
  bool docd;
  bool onepdm;
  bool twopdm;

  int norb;
  int na,nb;
  int num_schedule;
  int nroot;
  int maxiter
  int twodot_to_onedot;

  float* weights;
  double* sweep_tol;

  std::string file_one_int;
  std::string file_two_int;

  schedule* iter;

public:
  int write_config();

}; // end of class Block_Config

} // end of namespace interface_to_third_party

} // end of namespace iquads
