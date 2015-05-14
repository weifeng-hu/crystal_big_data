#ifndef IQUADS_CONDITION_BASE_H
#define IQUADS_CONDITION_BASE_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

namespace iquads{

struct condition_base
{
public:
  condition_base()
   {
    this->workdir_ = "unset";
    this->input_name_ = "unset";
    this->output_name_ = "unset";
    this->type_tag_ = "unset";
    this->sol_type_tag_ = "unset";
    this->parallelizable_ = false;
   }

protected:
  bool is_base_allset()
   {
    if( this->workdir_ == "unset" )
     { return false; }
    if( this->input_name_ == "unset" )
     { return false; }
    if( this->output_name_ == "unset" )
     { return false; }
    if( this->type_tag_ == "unset")
     { return false; }
    if( this->sol_type_tag_ = "unset")
     { return false; }
    return true;
   }

public:
  // non-const member access method
  hardware_info& hw_info()
   { return this->hw_info_; }
  stringstream& input_stream()
   { return this->input_stream_; }
  stringstream& output_stream()
   { return this->output_stream_; }
  string& workdir()
   { return this->workdir_; }
  string& input_name()
   { return this->input_name_; }
  string& output_name()
   { return this->output_name_; }
  string& type_tag()
   { return this->type_tag_; }
  string& sol_type_tag()
   { return this->sol_type_tag_; }

  // const member access method
  const hardware_info& hw_info() const 
   { return this->hw_info_; }
  const stringstream& input_stream() const 
   { return this->input_stream_; }
  const stringstream& output_stream() const 
   { return this->output_stream_; }
  const string& workdir() const 
   { return this->workdir_; }
  const string& input_name() const 
   { return this->input_name_; }
  const string& output_name() const 
   { return this->output_name_; }
  const string& type_tag() const 
   { return this->type_tag_; }
  const string& sol_type_tag() const 
   { return this->sol_type_tag_; }

private:
  hardware_info hw_info_;
  stringstream input_stream_;
  stringstream output_stream_;
  string workdir_;
  string input_name_;
  string output_name_;
  string type_tag_;
  string sol_type_tag_;

}; // end of struct condition_base

} // end of namespace iquads

#endif
