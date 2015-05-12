#include <iostream>
#include <utilities/solid_gen/interaction.h>

using namespace std;
using namespace iquads::crystal;

int main( int argc, char* argv[] ){

  cout << "test interaction object" << endl;
  {
   cout << "default constructor" << endl;
   interaction interact;
   cout << "print_fragment_groups()" << endl;
   interact.print_fragment_groups();
  }

}
