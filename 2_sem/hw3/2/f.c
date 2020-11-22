#include "f.h"

double f(int n, double x0, double *x, double *y){
  int i, j;
  double p=1, s=y[0];

  for(i=1;i<n;i++)
    for(j=n-1;j>=i;j--)
      y[j]=(y[j]-y[j-1])/(x[j]-x[j-i]);

  for(i=n-1; i>0; i--){
      s+=y[i];
      s*=(x0-x[i-1]);
    }
  return s+y[0];
}


