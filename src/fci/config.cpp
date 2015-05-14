#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>

#include "config.h"

using namespace std;

namespace fci{

struct config
{

void read_integral()
{

  ifstream ifs;
  ifs.open( this->dumpfile.c_str(), std::ifstream::in );

  cout << " reading integrals" << endl;
  string entry;
  {
   char sbuf[512];
   ifs.getline( sbuf, 512 );
   entry = sbuf;

   vector<string> fields;
   split( fields, entry, boost::algorithm::is_any_of("=, \t"), boost::algorithm::token_compress_on );
   for( int i = 0; i < fields.size(); i++ ){
    if( fields.at(i) == "NORB" ){ this->norb = atoi( fields.at(i+1).c_str() ); break; }
   }

   while( ifs >> entry ){ if( entry == "&END" || entry == "/" ) break; } 

   double val; int p1, p2, p3, p4;
   while( file >> val >> p1 >> p2 >> p3 >> p4 ){
    if( p1 != 0 && p2 != 0 && p3 != 0 && p4 != 0 ){
     v2( p1, p2, p3, p4 ) = val;
    }
    if( p1 != 0 && p2 != 0 && p3 == 0 && p4 == 0 ){
     v1( p1, p2 ) = val;
    }
    if( p1 == 0 && p2 == 0 && p3 == 0 && p4 == 0 ){
     cor_energy = val;
    }
   }

  }
  ifs.close();

}

void read()
{

  ifstream ifs;
  ifs.open( this->configfile.c_str(), std::ifstream::in );
  cout << " reading config file " << configfile << endl;
  {
    string entry;
    while( ifs.good() ){
     ifs >> entry;
     if( entry == "nblock"){
       this->nblock = atoi( entry.c_str() );
       this->blocks.resize(nblock);

       string sub_entry;
       ifs >> sub_entry;
       while( sub_entry != "end" ){
        ifs >> sub_entry;
        if( sub_entry == "nroots" ){
         for( int i = 0; i < nblock; i++ ){
          ifs >> this->blocks[i].set_nroots();
          this->blocks[i].resize( this->block[i].get_nroots() ) ;
         }
        }
        if( sub_entry == "partcle" ){
         for( int i = 0; i < nblock; i++ ){
          ifs >> this->block[i].set_particle();
         }
        }
        if( sub_entry == "sz" ){
         for( int i = 0; i < nblocks; i++ ){
          ifs >> this->block[i].set_sz();
         }
        }
       }

     }
     if( entry == "dumpfile" ){ ifs >> this->dumpfile; }
     if( entry == "lanczos_tol" ){ ifs >> this->lanczos_tol; }
    }
  }
  ifs.close();

}

config( string _configfile )
{

  this->configfile = _configfile;
  this->dumpfile = "not set";
  this->lancsoz_tol = 1.0e-8;
  this->norb = 0;
  this->core_energy = 0.0e0;
  this->nblock = 0;
  this->blocks.resize( nblock );

  this->read();

  if( norb == 0 ){ cout << " error: norb is zero! " << endl; abort(); }
  if( nblock == 0 ){ cout << " error: nblock is zero! " << endl; abort(); }
  if( dumpfile == "not set" ){ cout << " error: FCIDUMP file not set" << endl; abort(); }

  cout << " FCIDUMP file = " << dumpfile << endl;
  cout << " lanczos_tol = " << lanczos_tol << endl;
  cout << " nblock = " << nblock << endl;
  for( int i = 0; i < nblock; i++ ){
   cout << "  block " << i << "  nroots = " << blocks[i].get_nroots() << "  particle = " << block[i].get_particle() << "  sz = " << block[i].get_sz() << endl;
  }

  this->v1.resize( norb );
  this->v2.resize( norb );

  this->read_integal();
  cout << " norb = " << endl;
  cout << " core energy = " << core_energy << endl;

}

};

}
