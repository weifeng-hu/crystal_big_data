#include <string>
#include <vector>
#include <iostream>

namespace iquads {

class CommandParser
{
using std::vector;
using std::string;

public:
  CommandParser( int argc, char* argv[] ){
   for( size_t i = 0; i < argc; i++ ){
    const string argument = argv[i];
    this->command_strings_.push_back( argument );
   }
   this->filled_ = true;
  }

public:
  vector<string> command_strings() const 
   { 
     try{
      if( this->filled_ == true ){
       return this->command_strings_; 
      }
      else {
       throw 1;
      }
     } catch ( int code ){
      using std::cout;
      using std::endl;
      cout << "error: commands not initialized " << endl;
      abort();
     }
   }

private:
  vector<string> command_strings_;
  bool filled_;

};

}
