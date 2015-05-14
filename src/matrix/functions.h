namespace iqs {

namespace matrix {

vector<int> read_vector( string filename );

int A_x_B_x_C( bool transpose_A,  bool transpose_B, bool transpose_C, general_matrix& A, general_matrix& B, general_matrix& C, general_matrix& D );

} // end of matrix

} // end of iqs
