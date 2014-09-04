#include <iostream>
#include <string>

namespace fci
{

int fci_main( string configfile, string outfile )
{

  fci::config fci_conf( configfile );

  fci::solve( fci_conf );

  if( fci_config.calc_pdm() == true ){
   fci::pdms( fci_conf );
  }

}

}
