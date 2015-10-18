#ifndef INVOKER_NUNERICAL_NONADIABATIC_COUPLING_H
#define INVOKER_NUMERICAL_NONADIABATIC_COUPLING_H

#include <string>
#include <vector>
#include <ifstream>
#include <numerical_nonadiabatic_coupling_config.h>
#include <numerical_nonadiabatic_coupling_typedef.h>
#include <numerical_nonadiabatic_coupling_factory.h>
#include <invoker_base.h>

namespace iquads {

class Invoker_NumericalNonAdiabaticCoupling 
 : public Invoker_Base
{
using std::string;
using std::vector;
using std::ifstream;

public:
  void process_request()
  {
    this->reset_invoker();
    this->get_config();
    if( this->is_sane() ){
     NumericalNonAdiabaticCoupling_Base* coupling_solver 
      = this->setup_solver( this->config_.solver_tag() );
     coupling_solver->execute( this->config_ );
    }
  }

private:
  void reset_invoker(){
   this->reset_invoker_base();
  }
  void read_config_file(){
   ifstream ifs( this->config_file_.c_str(), std::ios::in );
   ifs >> this->config_;
   ifs.close();
  }
  void read_config_file_ssl()
  { /* TBI */ }
  void receive_network_config()
  { /* TBI */ }
  void receive_network_config_ssl()
  { /* TBI */ }
  bool is_sane()
  {
    bool retval = true;
    if( this->config_.is_sane() == false ) { retval = false; }
    return retval;
  }
  void* setup_solver( string solver_tag ){
   return this->factory_.get_product( solver_tag );
  }

private:
  NumericalNonAdiabaticCoupling_Config get_config(){
   switch( this->config_mode_ ){
    case file_:
     this->read_config_file();
     break;
    case file_ssl_:
     this->read_config_file_ssl();
     break;
    case network_:
     this->receive_network_config();
     break;
    case network_ssl_:
     this->receive_network_config_ssl();
     break;
    default:
     abort();
     break;
   }
   return this->config_;
  }

private:
  NumericalNonAdiabaticCoupling_Config config_;
  NumericalNonAdiabaticCoupling_Factory factory_;

}; // end of class Invoker_NumericalNonAdiabaticCoupling

} // end of namespace iquads

#endif
