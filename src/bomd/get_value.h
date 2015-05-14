#include <vector>
#include <string>
#include <iostream>
#include <stringstream>
#include <fstream>

namespace bomd {

template < typename T >
T get_value( const char* key, std::string filename );

template < typename T >
std::vector<T> get_value( const char* key, std::string filename );

}
