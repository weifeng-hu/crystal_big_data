
namespace iqs {

namespace rcm {

iqs::matrix::square_matrix input_matrix( std::string filename, const char type );

void rcm_help();

iqs::matrix::square_matrix calc_fock( const int dim, const int nocc, std::string filename );

}

}
