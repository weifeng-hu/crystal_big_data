#ifndef IQUADS_PLATFORM_INFO_H
#define IQUADS_PLATFORM_INFO_H

#include <string>

namespace iquads {

struct platform_info
{
public:
  platform_info(){}
  ~platform_info(){}

private:
  string platform_kind;
  string cpu_model;
  string gpu_model;
  unsigned int launch_mode;
  bool parallel;
  unsigned int nprocs;
  unsigned int nthread_procs;

};

}

#endif
