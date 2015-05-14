#ifndef IQUADS_MOLEINFO_H
#define IQUADS_MOLEINFO_H

#include <string>
#include "iquads/coordinate.h"

namespace iquads{

struct molecule_info
{
public:
  molecule_info()
    {
      this->coord_.resize(0);
      this->basis_set_tag_ = "not set";
      this->point_group_tag_ = "c1";
      this->norb_ = -1;
      this->nele_ = -1;
    }
  molecule_info( const coordinate coord, const string basis_set, const int norb, const int nele, const string pg = "c1" )
    {
      this->coord_ = coord;
      this->basis_set_tag_ = basis_set;
      this->point_group_tag_ = pg;
      this->norb_ = norb;
      this->nele_ = nele;
    }

public:
  bool is_allset()
    {
      if( coord_.n() == 0 )
       { return false; }
      if( basis_set_tag_ == "not set" )
       { return false; }
      if( norb_ == -1 )
       { return false; }
      if( nele_ == -1 )
       { return false; }

      return true;
    }

public:
  const coordinate& coord() const 
    { return this->coord_; }
  const string& basis_set_tag() const
    { return this->basis_set_tag_; }
  const string& point_group_tag() const 
    { return this->point_group_tag_; }
  const int& norb() const 
    { return this->norb_; }
  const int& nele() const
    { return this->nele_; }

  coordinate& coord()
    { return this->coord_; }
  string& basis_set_tag()
    { return this->basis_set_tag_; }
  string& point_group_tag()
    { return this->point_group_tag_; }
  int& norb()
    { return this->norb_; }
  int& nele()
    { return this->nele_; }

private:
  coordinate coord_;
  string basis_set_tag_;
  string point_group_tag_;
  int norb_;
  int nele_;

}; // end of struct molecule_info

} // end of namespace iquads

#endif
