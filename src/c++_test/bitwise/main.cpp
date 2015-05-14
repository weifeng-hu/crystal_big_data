#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class test
{
public:
  test( const int value )
  {
    this->store_ = value;
  }

public:
  int& store()
  {
    cout << " non-const verion;  store = " << store_ << endl;
    return store_;
  }
  const int& store() const 
  {
    cout << " const version;  store = " << store_ << endl;
    return store_;
  }
  void change_store( const int x ) const 
  {
    cout << " change store const version " << endl;
  }
  void change_store( const int x = 3 )
  {
    cout << " change store non const version " << endl;
    store_ = x ;
  }
  void sth( const int x = 3, const double y = 0.6,  const string str = "notset" )
  {
    cout << " x = " << x << " str = " << str << endl;
  }

private:
  int store_;

};

int main( int argc, char* argv[] )
{

  test test_nc(3);
  test const test_c(0);

  const int a = test_nc.store();
  int b = test_nc.store();
  int c = test_c.store();
  const int d = test_c.store();
  test_c.change_store(10);
  test_nc.change_store(7);
  test_nc.sth( 5, 0.3 , "weifeng");

  unsigned int hexint = 0x0a;
  cout << hex << hexint << endl;
  unsigned int moved = hexint<<4;
  cout << hex << moved << endl;
  unsigned int newint = moved | hexint;
  cout << hex << newint << endl;

}
