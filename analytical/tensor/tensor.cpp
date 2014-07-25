#include "tensor.h"

double* tensor( int d1 , double* t)
{
  t = new double [d1];

  for( int i = 0; i < d1; i++ ){
   t[i] = 0.0;
  }

  return t;
}

double** tensor( int d1, int d2, double** t)
{
  t = new double* [d1];
  for( int i = 0; i < d1; i++ ){
   t[i] = new double [d2];
  }

  for( int i = 0; i < d1; i++ ){
   for( int j = 0; j < d2; j++ ){
    t[i][j] = 0.0;
   }
  }

  return t;
}

double*** tensor( int d1, int d2, int d3, double*** t )
{
  t = new double** [d1];
  for( int i = 0; i < d1; i++ ){
   t[i] = new double* [d2];
   for( int j = 0; j < d2; j++ ){
    t[i][j] = new double [d3];
   }
  }

  for( int i = 0; i < d1; i++ ){
   for( int j = 0; j < d2; j++ ){
    for( int k = 0; k < d3; k++ ){
      t[i][j][k] = 0.0;
    }
   }
  }

  return t;
}

double**** tensor( int d1, int d2, int d3, int d4, double**** t)
{
  t = new double*** [d1];
  for( int i = 0; i < d1; i++ ){
   t[i] = new double** [d2];
   for( int j = 0; j < d2; j++ ){
    t[i][j] = new double* [d3];
    for( int k = 0; k < d3; k++ ){
     t[i][j][k] = new double [d4];
    }
   }
  }

  for( int i = 0; i < d1; i++ ){
   for( int j = 0; j < d2; j++ ){
    for( int k = 0; k < d3; k++ ){
     for( int l = 0; l < d4; l++ ){
       t[i][j][k][l] = 0.0;
     }
    }
   }
  }

  return t;
}

double***** tensor( int d1, int d2, int d3, int d4, int d5, double***** t)
{
  t = new double**** [d1];
  for( int i = 0; i < d1; i++ ){
   t[i] = new double*** [d2];
   for( int j = 0; j < d2; j++ ){
    t[i][j] = new double** [d3];
    for( int k = 0; k < d3; k++ ){
     t[i][j][k] = new double* [d4];
     for( int l = 0; l < d4; l++ ){
      t[i][j][k][l] = new double [d5];
     }
    }
   }
  }

  for( int i = 0; i < d1; i++ ){
   for( int j = 0; j < d2; j++ ){
    for( int k = 0; k < d3; k++ ){
     for( int l = 0; l < d4; l++ ){
      for( int m = 0; m < d5; m++ ){
       t[i][j][k][l][m] = 0.0;
      }
     }
    }
   }
  }

  return t;
}

double* tensor_reshape( int d1, double* t, int d, double* newt)
{

/*  d = d1; 
  newt = new double [d];
  for( int i = 0; i < d1; i++ )
  {
    newt[i] = t[i];
  } 
  return newt; */

  return t;
}

double* tensor_reshape( int d1, int d2, double** t, int d, double* newt)
{
  d = d1 * d2;
  newt = new double [d];
  for( int j = 0; j < d1; j++ ){
   for( int i = 0; i < d2; i++ ){
     newt[ j * d2 + i ] = t[j][i];
   }
  }
  return newt;
}

double* tensor_reshape( int d1, int d2, int d3, double*** t, int d, double* newt)
{
  return newt;
}

double* tensor_reshape( int d1, int d2, int d3, int d4, double**** t, int d, double* newt)
{
  d = d1 * d2 * d3 * d4;
  newt  = new double [d];
  for( int l = 0; l < d4; l++ ){
   for( int k = 0; k < d3; k++ ){
    for( int j = 0; j < d2; j++ ){
     for( int i = 0; i < d1; i++ ){
       newt[ l * d3 * d2 * d1 + k * d2 * d1 + j * d1 + i ] = t[i][j][k][l];
     }
    }
   }
  }
  return newt;
}

double* tensor_reshape( int d1, int d2, int d3, int d4, int d5, double***** t, int d, double* newt)
{
  return newt;
}

double** tensor_reshape( int d1, int d2, double** t, int D1, int D2, double** newt )
{
  return t;
}

double** tensor_reshape( int d1, int d2, int d3, double*** t, int D1, int D2, double** newt)
{
  D1 = d1; 
  D2 = d2 * d3;

  newt = new double* [D1];
  for( int i = 0; i < D1; i++ ){
    newt[i] = new double [D2];
  }

  for( int i = 0; i < d1; i++ ){
   for( int j = 0; j < d2; j++ ){
    for( int k = 0; k < d3; k++ ){
     newt[i][ j * d3 + k ] = t[i][j][k];
    }
   }
  }

  return newt;
}

double** tensor_reshape( int d1, int d2, int d3, int d4, int d5, double***** t, int D1, int D2, double** newt)
{
  D1 = d1;
  D2 = d2 * d3 * d4 * d5;

  newt = new double* [D1];
  for( int i = 0; i < D1; i++ ){
    newt[i] = new double [D2];
  }

  for( int i = 0; i < d1; i++ ){
   for( int j = 0; j < d2; j++ ){
    for( int k = 0; k < d3; k++ ){
     for( int l = 0; l < d4; l++ ){
      for( int m = 0; m < d5; m++ ){
       newt[i][ j * d3 * d4 * d5 + k * d4 * d5 + l * d5 + m ] = t[i][j][k][l][m];
      }
     }
    }
   }
  }

  return newt;
}

double** tensor_reshape( int D, double* t, int d1, int d2, double** newt )
{
  newt = new double* [d1];
  for( int i = 0; i < d2; i++ ){
   newt[i] = new double [d2];
  }

  for( int i = 0; i < d1; i++ ){
   for( int j = 0; j < d2; j++ ){
     newt[i][j] = t[ i * d2 + j ];
   }
  }
  return newt;
}

double* tensor_copy( int D, double* t1, double* t2)
{
  t2 = new double [D];
  for( int i = 0; i < D; i++ ){
   t2[i] = t1[i];
  }
  return t2;

}
