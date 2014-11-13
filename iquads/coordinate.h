#ifndef IQUADS_COORDINATE_H
#define IQUADS_COORDINATE_H

#include <cstddef>
#include <tuple>
#include <string>
#include <vector>

using namespace std;

namespace iquads {

struct coordinate
{
  typedef tuple< string, double, double, double > coord_atom;
  typedef vector< tuple< string, double, double, double > > coord_list;

public;
  coordinate()
    {  this->init(); }
  coordinate( const coord_list input_coord )
    {  this->store_ = input_coord; }

public:
  void init()
    { this->store_.resize(0); }
  void resize( const size_t size )
    { this->store_.resize( size ); }
  void push_back( const coord_atom single_set )
    { this->store_.push_back( single_set ); }
  void push_back( const string element, const double x, const double y, const double z )
    {
      const coord_atom singlet_set = make_tuple< string, double, double, double >( element, x, y, z );
      this->store_.push_back( single_set );
    }

public:
  const coord_list& store() const 
    { return this->store_; }
  const size_t& n() const 
    { return this->store_.size(); }
  const string& element( const size_t ind ) const 
    { return get< 0 > ( this->store_.at(ind) ); }
  const double& x( const size_t ind ) const 
    { return get< 1 > ( this->store_.at(ind) ); }
  const double& y( const size_t ind ) const 
    { return get< 2 > ( this->store_.at(ind) ); }
  const double& z( const size_t ind ) const 
    { return get< 3 > ( this->store_.at(ind) ); }

  coord_list& store() 
    { return this->store_; }
  size_t& n()
    { return this->store.size(); }
  string& element( const size_t ind )
    { return get< 0 > ( this->store_.at(ind) ); }
  double& x( const size_t ind )
    { return get< 1 > ( this->store_.at(ind) ); }
  double& y( const size_t ind )
    { return get< 2 > ( this->store_.at(ind) ); }
  double& z( const size_t ind )
    { return get< 3 > ( this->store_.at(ind) ); }

private:
  vector< coord_atom > store_;

}; // end of struct coordinate

} // end of iquads

#endif
