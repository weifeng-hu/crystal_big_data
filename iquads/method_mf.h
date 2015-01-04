#include <stdio.h>
#include "iquads/method_base.h"

namespace iquads {

class meanfield_method : public method_base
{
protected:
  virtual orb_solution run( const condition_scf condition ) = 0;

};

class scf : public meanfield_method
{
public:
  orb_solution run( const condition_scf condition )
   {
    this->init( condition.bin_dir() );
    this->spawn( this->program_name, condition.input_name(), condition.output_name(), condition.nprocs() );
    orb_solution sol;
    sol.get_solution( condition.solution_file() );
    return sol;
   }

private:
  void init( const string bin_dir )
   {
     this->program_name = bin_dir + "scf";
   }

};

class dft : public meanfield_method
{
public:
  orb_solution run( const condition_dft condition )
   { /* to be defined */ }

}

class orca_scf : public meanfield_method
{
public:
  orb_solution run( const condition_scf condition )
   {
     this->init( condition.bin_dir(), ( condition.nprocs() > 1 ) );
     this->spawn( this->program_name, condition.input_name(), condition.output_name(), condition.nprocs() );
     this->convert_format( condition_scf.gbwfile(), condition.solution_file() );
     orb_solution sol;
     sol.get_solution( condition.solution_file() );
     return sol;
   }

private:
  void init( const string bin_dir_orca, const bool parallel )
   {
     if( parallel )
      { this->program_name = bin_dir_orca + "/orca_scf"; }
     else
      { this->program_name = bin_dir_orca + "/orca_scf_mpi"; }
   }
  void convert_orb_from_orca( const string input, const string output )
   {
     /* to be defined */
   }

};

} // end of iquads
