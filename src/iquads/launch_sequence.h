#ifndef LAUNCH_SEQUENCE_H
#define LAUNCH_SEQUENCE_H

#include <memory>
#include <cstddef>
#include <string>
#include <vector>
#include "iquads/step.h"
#include "iquads/coordinate.h"
#include "iquads/platform_info.h"

namespace iquads {

struct sequence
{
public:
  sequence(){};
  sequence( const iquads::command cmd )
  {
    steps.resize(0);
    this->coords = cmd.get_coordinate();
    this->op_code_name = cmd.get_op_code_name();
    this->workdir = cmd.get_workdir();
    this->instruct_code = cmd.get_instruct_code();
  }
  ~sequence(){};

public:
  void setup_codes()
   { /* to be defined*/ }
  void setup_stages()
   {
    stage_factory factory = *(createStageFactory( /*condition*/ ));
    for( size_t i = 0; i < nstages; i++){
      stages.push_back( factory.get_stage( code.at(i) ) );
    }
   } // end of set
  void launch()
  {
    const size_t n_stage = stages.size();
    for( size_t i = 0; i < n_stage; i++ ){
     (stage.at(i))->perform();
    }
  }

private:
  vector< unique_ptr< stage > > stages;
  vector< unsigned int > codes;
  coordinate coords;
  platform_info platform;

  string op_code_name;
  string workdir;
  unsigned int instruct_code;

};

}

#endif
