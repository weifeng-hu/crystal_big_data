#ifndef CMD_OPTION_BASE_H
#define CMD_OPTION_BASE_H

namespace iqs { 

class cmd_option_base
{

private:
  std::string prefix_;

public:
  cmd_option_base(){};
  ~cmd_option_base(){};

public:
  std::string& prefix() { return this->prefix_; }
  const std::string get_prefix() const { return this->prefix_; }

};

}  // end of iqs

#endif
