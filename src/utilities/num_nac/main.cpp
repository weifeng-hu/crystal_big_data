#include <command_parser.h>

int main( int argc, char* argv[] )
{

  CommandParser command_parser( argc, argv );
  return iquads::numerical_nonadiabatic_coupling_driver( command_parser.command_strings() );

}
