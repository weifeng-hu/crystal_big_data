#include <iostream>

using namespace std;

class base
{

public:
  virtual void x() = 0;

};

class derived : public base
{

public:
  void x()
  {
    this->x_ = 3;
    cout << " x_ = " << x_ << endl;
  }

private:
  int x_;

};

int main( int argc, char* argv[] )
{

//  base* base_ptr = new derived;
//  base_ptr -> x();
   derived* derived_ptr = new derived;
   base* base_ptr = static_cast<derived*>( derived_ptr );
   base_ptr -> x();

}
