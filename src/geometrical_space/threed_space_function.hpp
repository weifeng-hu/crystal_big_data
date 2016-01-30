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

#ifndef THREED_SPACE_FUNCTION_HPP
#define THREED_SPACE_FUNCTION_HPP

#include <array>
#include <tuple>
#include <math.h>
#include <geometrical_space/threed_space.hpp>
#include <geometrical_space/coordinate.hpp>

namespace iquads {

  namespace geometrical_space {
  
    using std::array;

    namespace threed_space {
    
      typedef CartesianCoordinate3D Coord;
    
      inline
      void operator+= ( Coord& lhs, const Coord& rhs ) {
        using std :: get;
        get<0> ( lhs ) += get<0>( rhs );
        get<1> ( lhs ) += get<1>( rhs );
        get<2> ( lhs ) += get<2>( rhs );
      }

      inline
      void operator*= ( Coord& lhs, const double rhs ) {
        using std :: get;
        get<0> ( lhs ) *= rhs;
        get<1> ( lhs ) *= rhs;
        get<2> ( lhs ) *= rhs;
      }
    
      inline
      double compute_distance( Coord coord_a, Coord coord_b ) {
    
        double retval = 0.0e0;
        {
          using std::get;
          const double x_a = get<0>(coord_a);
          const double y_a = get<1>(coord_a);
          const double z_a = get<2>(coord_a);
        
          const double x_b = get<0>(coord_b);
          const double y_b = get<1>(coord_b);
          const double z_b = get<2>(coord_b);
        
          const double dx = x_a - x_b;
          const double dy = y_a - y_b;
          const double dz = z_a - z_b;
        
          const double dis_sqr = dx * dx + dy * dy + dz * dz;
          retval = sqrt( dis_sqr );
        }
     
        return retval;
    
      } // end of compute_distance()
    
      inline
      double compute_charge_weighted_distance( Coord coord_a, Coord coord_b, int charge_a, int charge_b ) { 
         double retval = 0.0e0;
         {
           using std::get;
           const double x_a = get<0>(coord_a); //* charge_a/10.0e0;
           const double y_a = get<1>(coord_a); //* charge_a/10.0e0;
           const double z_a = get<2>(coord_a); //* charge_a/10.0e0;
         
           const double x_b = get<0>(coord_b); //* charge_b/10.0e0;
           const double y_b = get<1>(coord_b); //* charge_b/10.0e0;
           const double z_b = get<2>(coord_b); //* charge_b/10.0e0;
         
           const double dx = x_a - x_b;
           const double dy = y_a - y_b;
           const double dz = z_a - z_b;
         
           const double dis_sqr = dx * dx + dy * dy + dz * dz;
           retval = sqrt( dis_sqr ) * charge_a * charge_b;
         }
         return retval;
      } // end of function compute_charge_weighted_distance()
      
      inline
      array< double, 3 > compute_recenter_vec( Interval3D edges ) {
        using std :: get;
        const double x_plus  = get<0> ( get<0> ( edges ) );
        const double x_minus = get<1> ( get<0> ( edges ) );
        const double y_plus  = get<0> ( get<1> ( edges ) );
        const double y_minus = get<1> ( get<1> ( edges ) );
        const double z_plus  = get<0> ( get<2> ( edges ) );
        const double z_minus = get<1> ( get<2> ( edges ) );
        array<double, 3 > retval = { -(x_plus+x_minus)/2, -(y_plus+y_minus)/2, -(z_plus+z_minus)/2 };
        return retval;
      } // end of function compute_recenter_vec()

      inline
      double compute_angle_between_two_vectors( const array< double, 3 >& ra, const array< double, 3 >& rb ) {
        double inner_prod =  ra[0] * rb[0];
               inner_prod += ra[1] * rb[1];
               inner_prod += ra[2] * rb[2];
        double inner_a =  ra[0] * ra[0];
               inner_a += ra[1] * ra[1];
               inner_a += ra[2] * ra[2];
        double norm_a = sqrt( inner_a );

        double inner_b =  rb[0] * rb[0];
               inner_b += rb[1] * rb[1];
               inner_b += rb[2] * rb[2];
        double norm_b = sqrt( inner_b );
        double cos_theta = inner_prod / ( norm_a * norm_b );
        double theta = acos( cos_theta );
        return theta / pi * 180.0e0;
      }

    } // end of namespace threed_space
    
  } // end of namespace geometrical_space

} // end of namespace iquads

#endif
