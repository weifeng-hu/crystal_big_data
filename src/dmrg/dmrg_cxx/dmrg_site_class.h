// dmrg_site_class.h

// ========================================================
//
//   The class for all site objects.
//   A site can be any single site, or orbital, in quantum
//   chemistry language
//   This site can be derived into original 4x4 site,
//   direct producted site 4^n by 4^n,
//   and can be a renormalized siie
//
// ========================================================

// by Weifeng


namespace ithaca { namespace dmrg {

// ==========================
//     The prototype class
// ==========================
class site()
{
public:
  site(){};
  ~site(){};

public:
  QuantumMap QM;     // A site has a quantum number map recording the state quantum numbers 
                        // which construct the quantum number strctures of this site

  // A site has 4 kinds of essential operators
public:
  UpCreator Cu;
  DnCreator Cd;
  UpDestoryer Au;
  DnDestoryer Ad;


};   // end of class site


// ==========================
//        Site of 4x4
// ==========================
class osite() : site
{
public:

};

// ==========================
//       Site of n x n
// ==========================
class dsite() : site
{
public:

};


} }  // end of ithaca::dmrg
