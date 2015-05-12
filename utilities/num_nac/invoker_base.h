#ifndef INVOKER_BASE_H
#define INVOKER_BASE_H

#include <string>
#include <vector>

namespace iquads {

class Invoker_Base
{
using std::string;
using std::vector;

protected:
  enum ConfigMode { unset_, file_, file_ssl_, network_, network_ssl_ };

public:
  Invoker_Base(){
   this->reset_invoker_base();
  }
  Invoker_Base( vector<string> args ){
   this->reset_invoker_base();
   this->command_copy_ = args;
   this->process_command();
  }

protected:
  virtual void reset_invoker() = 0;
  virtual void process_request() = 0;
  virtual void read_config_file() = 0;
  virtual void read_config_file_ssl() = 0;
  virtual void receive_network_config() = 0;
  virtual void receive_network_config_ssl() = 0;
  virtual bool is_sane() = 0;
  virtual void* setup_solver( string solver_tag ) = 0;

protected:
  void reset_invoker_base(){
   this->command_copy_.resize(0);
   this->config_mode_ = this->ConfigMode::unset_;
   this->config_file_ = "unset";
   this->config_is_set_ = false;
   this->nomore_request_ = false;
  }
  void process_command()
  {
   for( size_t i = 0; i < this->command_copy_.size(); i++ ){
    string command_string_local = command_copy_.at(i);
    if( command_string_local == "--config_file" ){
     this->config_mode_ = this->ConfigMode::file_;
     this->config_file_ = command_copy_.at(i+1);
     this->config_is_set_ = true;
     break;
    }
    else if( command_string_local == "--config_ssl" ){
     this->config_mode_ = this->ConfigMode::file_ssl_;
     this->config_file_ = command_copy_.at(i+1);
     this->config_is_set_ = true;
     break;
    }
    else if( command_string_local == "--network" ){
     this->config_mode_ = this->ConfigMode::network_;
     this->config_is_set_ = true;
     break;
    }
    else if( command_string_local == "--network_ssl" ){
     this->config_mode_ = this->ConfigMode::network_ssl_;
     this->config_is_set_ = true;
     break;
    }
   }
  }

public:
  vector<string> command_copy() const { return this->command_copy_; }
  string config_file() const { return this->config_file_; }
  Invoker_Base::ConfigMode config_mode() const { return this->config_mode_; }
  bool config_is_set() const { return this->config_is_set_; }
  bool nomore_request() const { return this->nomore_request_; }

protected:
  vector<string> command_copy_;
  string config_file_;
  ConfigMode config_mode_;
  bool config_is_set_;
  bool nomore_request_;

}; // end of class Invoker_Base

} // end of namespace iquads

#endif
