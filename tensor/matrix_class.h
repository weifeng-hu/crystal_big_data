

namespace ithaca { 

template < typename T >
class matrix : public tensor
{
public:
  matrix(){};
  matrix( int d1, int d2 );
  matrix( std::vector<int> dim );
  ~matrix(){};

public:
  operator() ();
  operator=  ();
  operator+  ();
  operator*  ();
  operator|  ();
  operator.  ();

public:
  T element( int i, int j );
  const T element( int i, int j );

public:
  void reset( int i, int j );
  void reset_all();

};

}
