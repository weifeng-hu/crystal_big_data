// dmrg_quantum_class.h 
// 
// ===================================================
//
//   This is the class for dining the quantum number 
//   set for a state in dmrg, including:
//   1. particle number symmetry
//   2. spin symmetry
//   3. point group symmetry
//   Also the auxiliary functions 
//
// ===================================================
//

namespace ithaca {  namespace dmrg {

class quantum()
{
public:
   quantum(){};
   ~quantum(){};

public:
// ======== quantum number set =======
   int n;       // particle number, must be integer
   double s;     // spin number, must be multiple of 0.5
   int g;       // group symmetry, must be integer

// ===== Auxiliary functions =====

public:
   int get_n(){ return this->n; };
   double get_s(){ return this->s; };
   int get_g(){ return this->g; };

   void set_n( int val ){ this->n = val; }
   void set_s( double val ){ this->s = val; }
   void set_g( int val ){ this->g = val; };

};   // end of class quantum

} }  // end of ithaca::dmrg
