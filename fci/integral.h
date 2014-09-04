#include <array>

#include "fci.h"

namespace fci{

struct one_integral
{
public:
  one_integral(){}
  one_integral( const int _norb ){
   store.fill( 0.0e0 );
   this->norb = _norb;
   this->norb2 = norb * norb;
   if( norb2 < NORB_THRESH*NORB_THRESH ){ 
    cout << " error: integral container cannot hold " << norb << " orbitals"; 
    abort(); 
   }
  }
  ~one_integral(){}

public:
  void resize( const int _norb ){
   this->norb = _norb;
   this->norb2 = norb * norb;
   if( norb2 < NORB_THRESH*NORB_THRESH ){ 
    cout << " error: integral container cannot hold " << norb << " orbitals"; 
    abort(); 
   }
  }

  const int get_norb() const { return this->norb; }
  int& set_norb() { return this->norb; }

  const int get_norb2() const { return this->norb2; }
  int& set_norb2() { return this->norb2; }

  void reset(){ this->store.fill(0.0e0); }

public:
  const double get_element( const int ind_i, const int ind_j ) const { 
   const int ind = ind_i * norb + ind_j;
   return this->store.at( ind );
  }

  double& operator() ( const int ind_i, const int ind_j ){
   const int ind = ind_i * norb + ind_j;
   return this->store.at( ind );
  }

private:
  std::array<double, NORB_THRESH * NORB_THRESH > store;
  int norb;
  int norb2;

};

struct two_integral
{
public:
  two_integral(){}
  two_integral( const int _norb ){
   store.fill( 0.0e0 );
   this->norb = _norb;
   this->norb4 = norb * norb * norb * norb;
   if( norb2 < NORB_THRESH*NORB_THRESH*NORB_THRESH*NORB_THRESH ){ 
    cout << " error: integral container cannot hold " << norb << " orbitals"; 
    abort(); 
   }
  }
  ~one_integral(){}

public:
  void resize( const int _norb ){
   this->norb = _norb;
   this->norb4 = norb * norb;
   if( norb4 < NORB_THRESH*NORB_THRESH ){ 
    cout << " error: integral container cannot hold " << norb << " orbitals"; 
    abort(); 
   }
  }

  const int get_norb() const { return this->norb; }
  int& set_norb() { return this->norb; }

  const int get_norb4() const { return this->norb4; }
  int& set_norb4() { return this->norb4; }

  void reset(){ this->store.fill(0.0e0); }

public:
  const double get_element( const int ind_i, const int ind_j, const int ind_k, const int ind_l ) const { 
   const int ind = ind_i * norb * norb * norb + ind_j * norb * norb + ind_k * norb + ind_l;
   return this->store.at( ind );
  }

  double& operator() ( const int ind_i, const int ind_j, const int ind_k, const int ind_l ){
   const int ind = ind_i * norb * norb * norb + ind_j * norb * norb + ind_k * norb + ind_l;
   return this->store.at( ind );
  }

private:
  std::array<double, NORB_THRESH * NORB_THRESH * NORB_THRESH * NORB_THRESH > store;
  int norb;
  int norb4;

};

}
