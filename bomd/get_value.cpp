#include "get_value.h"

#define DBG 1

namespace bomd {

template < typename T > 
T get_value( const char* key, std::string filename )
{
  char line[1000];
  T value;

  ifstream file;
  file.open( filename.c_str(), ios::in );
  if( file.good() == false ){ cout << "error: get_value(): error in opening file "<< filename << endl; exit(1); }

  std::string ln;
  while( !file.eof() ){
   file.getline( line, 1000 );
    ln = line;
    if( ln.find( key, 0 ) != std::string::npos ){
     stringstream ss;
     std::string _key;

     ss << line;
     ss >> _key >> value;

     //if( strcmp( _key.c_str(), key ) != 0 ){ cout << "error: get_value(): a value found : " << _key << " but not match required value " <<  key << endl; exit(1); };
     
    };
  }
  if( file.eof() == true ){ cout << "warning: get_value(): cannot find value " << key << " in " << filename << endl; }

#if DBG
  cout << " get_value(): key = " << key << " value = " << value << endl;
#endif

  return value;

} // end of < typename T > get_value()

template < typename T >
std::vector<T>& get_value( const char* key, std::string filename )
{

  char line[1000];
  std::vector<T> value;

  ifstream file;
  file.open( filename.c_str(), ios::in );
  if( file.good() == false ){ cout << "error: get_value(): error in opening file " << filename << endl; exit(1); }

  std::string ln;
  while( !file.eof() ){
   file.getline( line, 1000 );
    ln = line;
    if( ln.find( key, 0 ) != std::string::npos ){

     stringstream ss; 
    // get the vector content
     size_t start_pos = ln.find( "=" , 0 ) + 1; // if( start_pos == std::string::npos ){ cout << "warning: get_value(): key " << key << " is not well-defined " << endl; }
     size_t end_pos; 
     while( true ){
       end_pos = ln.find( ",", start_pos );
       std::string element( ln, start_pos, end_pos - start_pos );
       ss << element;
       if( end_pos == std::string::npos )break;
     }

     while( !ss.eof() ){
      T tmp;
      ss >> tmp;
      value.push_back(tmp);
     }

     //if( strcmp( _key.c_str(), key ) != 0 ){ cout << "error: get_value(): a value found : " << _key << " but not match required value " <<  key << endl; exit(1); };
     
    }
  }
  if( file.eof() == true ){ cout << "warning: get_value(): cannot find value " << key << " in " << filename << endl; }

#if DBG
  cout << " get_value(): key = " << key << " value = ";
  for( int i = 0; i < value.size(); i++ ){
   cout << value[i] << " " ;
  }
  cout << endl;
#endif
  return value;

}

} // end of bomd
