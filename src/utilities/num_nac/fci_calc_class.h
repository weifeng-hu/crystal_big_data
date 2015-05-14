#ifndef FCI_SETTING_H
#define FCI_SETTING_H

#include <string>
#include <fstream>

namespace iquads{

namespace num_nac{

struct fci_setting{
public:
 fci_setting(){
  fci_exe = "not set";
  fci_input = "not set";
  fci_output = "not set";
  nelec = -1;
  sz = -1;
  s_square = -1;
  guess = -1;
 }

public:
 void write_input( string subdir ){
  ofstream ofs;
  ofs.open( fci_input.c_str(), ios::out );
  ofs << subdir << endl;
  ofs << molecule << endl;
  ofs << scientific << nel_d << endl;
  ofs << scientific << sz_d << endl;
  ofs << scientific << s_sq_d << endl;
  ofs << guess << endl;
  ofs.close();
 }
 void run(){

 }
 void collect_solution();


public:
 string get_fci_exe() const { return this->fci_exe; }
 string& set_fci_exe() { return this->fci_exe; }

 string get_fci_input() const { return this->fci_input; }
 string& set_fci_input() { return this->fci_input; }

 string get_molecule_name() const { return this->molecule_name; }
 string& set_molecule_name() { return this->molecule_name; }

 int get_nelec() const { return this->nelec; }
 int& set_nelec() { return this->nelec; }

 int get_sz() const { return this->sz; }
 int& set_sz() { return this->sz; }

 int get_s_square() const { return this->s_square; }
 int& set_s_square() { return this->s_square; }

 int get_guess() const { return this->guess; }
 int& set_guess() { return this->guess; }

private:
 string fci_exe;
 string fci_input;
 string fci_output;
 string molecule_name;
 int nelec;
 int sz;
 int s_square;
 int guess;

};

}

}

#endif
