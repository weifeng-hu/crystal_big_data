#include <array>

using namespace std;

namespace fci{

struct op
{
public:
  op(){};
  ~op(){};

public:
  array<double, 16> store_d;
  const array<int, 4> store_p = { 0, 1, 1, 2 };
  const array<int, 4> store_sz = { 0, 1, -1, 0 };


};

}
