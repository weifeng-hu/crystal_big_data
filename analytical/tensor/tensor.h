
double*     tensor( int d1 , double* t );
double**    tensor( int d1, int d2, double** t );
double***   tensor( int d1, int d2, int d3, double*** t );
double****  tensor( int d1, int d2, int d3, int d4, double**** t );
double***** tensor( int d1, int d2, int d3, int d4, int d5, double***** t );

double* tensor_reshape( int d1, double* t, int d, double* newt);
double* tensor_reshape( int d1, int d2, double** t, int d, double* newt);
double* tensor_reshape( int d1, int d2, int d3, double*** t, int d, double* newt);
double* tensor_reshape( int d1, int d2, int d3, int d4, double**** t, int d, double* newt);
double* tensor_reshape( int d1, int d2, int d3, int d4, int d5, double***** t, int d, double* newt);

double** tensor_reshape( int d1, int d2, double** t, int D1, int D2, double** newt );
double** tensor_reshape( int d1, int d2, int d3, double*** t, int D1, int D2, double** newt);
double** tensor_reshape( int d1, int d2, int d3, int d4, double**** t, int D1, int D2, double** newt);
double** tensor_reshape( int d1, int d2, int d3, int d4, int d5, double***** t, int D1, int D2, double** newt);

double** tensor_reshape( int D, double* t, int d1, int d2, double** newt );

double* tensor_copy( int D, double* t1, double* t2 );
