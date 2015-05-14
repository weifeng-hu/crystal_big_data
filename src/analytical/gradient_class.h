
namespace ithaca { namespace analytical {

extern "C" {
 void hf_gradient_( int* nbas, int* norb, int* nocc, double* ha_ao, double* eria_ao, double* c, double* sa, double* eps, double* gradient );

 void fci_gradient_( int* norb, double* q, double* g, double* h, double* eri, double* h_a, double* tei_a, double* u, double* gradient );

 void core_act_gradient_( int* norb, int* ncore, int* nact, double* q, double* tei, double* tei_a, double* u, double* gradient );

 void get_h_core_( int* norb, int* ncore, double* h, double* h_core );

 void get_eri_core_( int* norb, int* ncore, double* eri, double* eri_core );

 void get_c_core_( int* norb, int* ncore, double* c, double* c_core );

 void get_eps_core_( int* norb, int* ncore, double* eps, double* eps_core );

 void get_2_act_( int* norb, int* ncore, int* nact, double* t, double* newt );

 void get_4_act_( int* norb, int* ncore, int* nact, double* t, double* newt );

 void get_u_act_( int* norb, int* ncore, int* nact, double* u, double* u_act );

 void build_one_pdm_( int* norb, int* ncore, int* nact, double* one_pdm_act, double* one_pdm );

 void build_two_pdm_( int* norb, int* ncore, int* nact, double* one_pdm, double* two_pdm_act, double* two_pdm );
}

class gradient_class{
public:
  gradient_class( ithaca::analytical::cphf cphf_data, ithaca::analytical::qcdmrg dmrg_data );
  ~gradient_class(){};

public:
  double* q;
  double* g;

  double* gradient;

public:
  void build_one_pdm( double* one_pdm_act ){
     build_one_pdm_( &(this->norb), &(this->ncore), &(this->nact), one_pdm_act, this->q );
  }

  void build_two_pdm( double* one_pdm, double* two_pdm_act ){
     build_two_pdm_( &(this->norb), &(this->ncore), &(this->nact), this->q, two_pdm_act, this->g );
  }

public:
  double E_core;
  double* E_core_a;

  double E_act;
  double* E_act_a;

  double* E_core_act_a;


  int nbas,norb;
  int nocc,nvir;
  int ncore,nact;

  double* h_core;
  double* eri_core;
  double* c_core;
  double* eps_core;

  void get_h_core( int* norb, int* ncore, double* h, double* h_core ){
    get_h_core_( &norb, &ncore, h, h_core );
  };

  void get_eri_core( int* norb, int* ncore, double* eri, double* eri_core ){
    get_eri_core_( &norb, &ncore, eri, eri_core );
  };

  void get_c_core( int* norb, int* ncore, double* c, double* c_core ){
    get_c_core_( &norb, &ncore, c, c_core);
  };

  void get_eps_core( int* norb, int* ncore, double* eps, double* eps_core ){
    get_eps_core_( &norb, &ncore, eps, eps_core );
  };

  double hf_gradient( int nbas, int norb, int nocc, double* ha_ao, double* eria_ao, double* c, double* sa, double* eps, double gradient ){
    hf_gradient_( &nbas, &norb, &nocc, ha_ao, eria_ao, c, sa, eps, &gradient);
    return gradient;
  };

  double fci_gradient( int norb, double* q, double* g, double* h, double* eri, double* h_a, double* tei_a, double* u, double* gradient ){
    fci_gradient_( &norb, q, g, h, eri, h_a, tei_a, u, &gradient);
    return gradient;
  };

  double core_act_gradient( int norb, int ncore, int nact, double* q, double* tei, double* tei_a, double* u, double* gradient ){
    core_act_gradient_( &norb, &ncore, &nact, q, tei, tei_a, u, &gradient );
  };

  void get_u_act( int norb, int ncore, int nact, double* u, double* u_act ){
    get_u_act_( &norb, &ncore, &nact, u, u_act );
  };

  void get_2_act( int norb, int ncore, int nact, double* t, double* newt ){
    get_2_act_( &norb, &ncore, &nact, t, newt );
  }

  void get_4_act( int norb, int ncore, int nact, double* t, double* newt ){
    get_4_act_( &norb, &ncore, &nact, t, newt );
  }

};

} }
