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

#ifndef PROGRESS_DISPLAY_HPP
#define PROGRESS_DISPLAY_HPP

#include <vector>
#include <array>
#include <iostream>

namespace iquads {

namespace timer {

class ProgressDisplay {
public:
  typedef ProgressDisplay this_type;

public:
  ProgressDisplay( size_t total_step ) {
    this->current_step_ = 0;
    this->total_step_   = total_step;
    this->n_tic_ = 50;
    std :: cout << "|----|----|----|----|----|----|----|----|----|----|" << std :: endl;
  };
  ProgressDisplay( std :: string event_name, size_t total_step ) {
    this->current_step_ = 0;
    this->total_step_   = total_step;
    this->n_tic_ = 50;
    std :: cout << event_name << std :: endl;
    std :: cout << "|----|----|----|----|----|----|----|----|----|----|" << std :: endl;
  };

public:
  this_type& operator++() {
    this->current_step_ += 1;
    this->update_progress_bar();
    return *this;
  }
  this_type operator++( int ) {
    this_type tmp( *this );
    this->operator++();
    return tmp;
  }

private:
  void update_progress_bar() {
    int number_of_tics_to_show = (int) ( ( double )( current_step_/total_step_ ) * 50.0e0 );
    std :: cout << "\r";
    for( int i = 0; i < number_of_tics_to_show; i++ ) {
      std :: cout << "*";
    }
    if( current_step_ == this->total_step_ ) {
      std :: cout << "*" << std :: endl;
    }
  }

private:
  size_t current_step_;
  size_t total_step_;
  const size_t n_tic_;

}; // end of class ProgressDisplay

} // end of namespace timer

} // end of namespace iquads

#endif
