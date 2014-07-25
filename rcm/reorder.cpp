#include <vector>
#include "../matrix/square_matrix.h"
#include "star_matrix.h"
#include "rcm.h"

using namespace std;

namespace iqs {

namespace rcm {

vector<int> star_matrix::reorder( vector<int>& xadjv, vector<int>& adjv )
{

   int n = this->get_dim0();
   int* xadj = new int [ xadjv.size() ]; for( int i = 0; i < xadjv.size(); i++ ){ xadj[i] = xadjv.at(i); }
   int* adj = new int [ adjv.size() ]; for( int i = 0; i < adjv.size(); i++ ){ adj[i] = adjv.at(i); }
   int flags = 0;
   int* perm = new int [n];
   signed char* mask = new signed char [ n ]; for( int i = 0; i < n; i++ ){ mask[i] = 0; }
   int* deg = new int [n];
   RCM_FUNC(genrcmi)( n, flags, xadj, adj, perm, mask, deg );

   vector<int> new_order;
   for( int i = 0; i < n; i++ ){ new_order.push_back( perm[i] ); }

   return new_order;

}

} // end of rcm

} // end of iqs
