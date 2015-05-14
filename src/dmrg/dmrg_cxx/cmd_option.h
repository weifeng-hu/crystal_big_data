#include "dmrg/dmrg_define.h"
#include "cmd_option/cmd_option_base.h"

#ifndef CMD_OPTION_H
#define CMD_OPTION_H

using namespace std;

namespace iqs {  namespace dmrg  {

class cmd_option : public iqs :: cmd_option_base
{

private:
  string dmrg_conf_;
  string output_;

private:
  RUN_MODE run_mode_;

public:
  cmd_option(){};
  cmd_option( int argc, char* argv[] );
  ~cmd_option(){};

public:
  string& dmrg_conf()   { return this->dmrg_conf_; }
  string& output()      { return this->output_   ; }
  RUN_MODE& run_mode()  { return this->run_mode_ ; }

  const std::string get_dmrg_conf() const { return this->dmrg_conf_; }
  const std::string get_output()    const { return this->output_   ; }
  const RUN_MODE    get_run_mode()  const { return this->run_mode_ ; }

public:
  void set_default();
  void help();
  void check_cmd();

};

} }  // end of iqs :: dmrg

#endif
