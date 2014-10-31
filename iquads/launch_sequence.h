#ifndef LAUNCH_SEQUENCE_H
#define LAUNCH_SEQUENCE_H

#include <string>
#include <vector>

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

}

struct step
{
public:
  step(){};
  ~step(){};

public:
  void setup( const string keyword ){
   this->program_name = setup_program_name( keyword );
   this->input_name   = work_dir + op_code_name + keyword + ".inp";
   this->output_name  = work_dir + op_code_name + keyword + ".out";
   this->execution_cmdline = setup_cmdline();
   write_input( this->input_name );
  }

private:
  string setup_program_name(){
   return iquads::py_interface::get_program_name( keyword );
  }
  void write_input( input_name ){};

private:
  platform_info platf_info;

  vector< string > opts;
  vector< string > input_container;
  string keyword;
  string op_code_name;
  string program_name;
  string work_dir;
  string input_name;
  string output_name;
  string execution_cmdline;

}

struct launch_sequence
{
public:
  launch_sequence(){};
  ~launch_sequence(){};

public:
  void setup_seqs( iquads :: command cmd ){
   this->steps.resize(0);
   const vector<string> keywords = cmd.get_keywords();
   for( int i = 0; i < keywords.size(); i++ ){
    for( int j = 0; j < (iquads :: known_seqs).size(); j++ ){
     const string known_seq = known_seqs.at(j);
     if( boost::iequals( keywords, known_seq ) ){
      steps.push_back( load_seq_default( known_eq ) );
     }
    }
   }
  }

private:
  vector< step > steps;

};

}

#endif
