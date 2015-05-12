#include <iostream>
#include <utilities/solid_gen/matrix.h>

using namespace std;
using namespace iquads::matrix;

int main( int argc, char* argv[] )
{

  cout << "test matrix_heap interface" << endl;
  cout << "default constructor" << endl;
  DMatrixHeap mat1;
  cout << " nrow = " << mat1.get_nrow() << " ncol = " << mat1.get_ncol() << endl;
  cout << " resize to 10 x 10" << endl;
  mat1.resize( 10, 10 );
  cout << " nrow = " << mat1.get_nrow() << " ncol = " << mat1.get_ncol() << endl;
  mat1( 2, 2 ) = 3.14;

  cout << "test matrix_stack interface" << endl;
  cout << "default constructor" << endl;
  DMatrixStack mat2;
  cout << " nrow = " << mat2.get_nrow() << " ncol = " << mat2.get_ncol() << endl;
  cout << " copy from matrix heap" << endl;
  mat2.copy_from( &mat1 );
  cout << " nrow = " << mat2.get_nrow() << " ncol = " << mat2.get_ncol() << endl;
  cout << mat2( 2, 2 ) << endl;;

}
