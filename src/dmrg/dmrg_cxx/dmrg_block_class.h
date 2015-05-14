// dmrg_block_class.h
//
// ==============================================
//
//  Class for defining a block.
//  A block can be a single site, or renormzalized 
//  sites, system, environment.
//  
// ==============================================

namespace iqs {  namespace dmrg {

class block()
{
public:
  block(){};
  ~block(){};

public:
  int sitenum;      // A block should have defined number of sites

public:
 // QuantumMap  QM;     // A matrix that defines the quantum number structure for operators

public:
 // vector<site> SiteSer;

public:
  


};   // end of class block

} }  // end of ithaca::dmrg
